cmake_minimum_required(VERSION 3.6)

project(ccmath-cpp)

include(GNUInstallDirs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic")

# assume the target platform is the same as the host
if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "i[36]86")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=atom -mfpmath=sse")
endif(${CMAKE_SYSTEM_PROCESSOR} MATCHES "i[36]86")

add_library(ccmath-cpp SHARED mattr.cc minv.cc psinv.cc qrbdi.cc rmmult.cc svdval.cc trnm.cc vmul.cc eigen.cc eigval.cc house.cc housev.cc qreval.cc qrevec.cc)

set(CCMATH_VERSION "2.2.1") # fixed ccmath version
set(CPP_VERSION "3") # increase with each new package release
set(SO_MAJOR "1") # increase with each backwards incompatible change (and reset SO_MINOR to 0)
set(SO_MINOR "2") # increase with each backwards compatible change

set_target_properties(ccmath-cpp PROPERTIES VERSION "${SO_MAJOR}.${SO_MINOR}.0" SOVERSION ${SO_MAJOR})

install(TARGETS ccmath-cpp LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT runtime NAMELINK_SKIP)
install(TARGETS ccmath-cpp LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT dev NAMELINK_ONLY)
install(FILES ccmath.hh DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT dev)
install(FILES README lgpl.license DESTINATION ${CMAKE_INSTALL_DOCDIR} COMPONENT runtime)

set(CPACK_COMPONENT_DEV_DEPENDS runtime)
set(CPACK_COMPONENTS_ALL dev runtime)

set(CPACK_PACKAGE_NAME libccmath-cpp)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Selection of CCMATH functions, adapted for C++")
set(CPACK_PACKAGE_CONTACT "Roel van de Kraats <roel@2getthere.eu>")
set(CPACK_PACKAGE_VENDOR "2getthere b.v. (https://www.2getthere.eu)")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README")

set(CPACK_COMPONENT_DEV_DISPLAY_NAME "${CPACK_PACKAGE_NAME}-dev")
set(CPACK_COMPONENT_RUNTIME_DISPLAY_NAME "${CPACK_PACKAGE_NAME}")

# Try to find distro id
execute_process(COMMAND sh -c "grep '^ID=' /etc/os-release | sed -e 's/^.*=//g' -e 's/\"//g'" ERROR_QUIET OUTPUT_VARIABLE OS_ID)
string(STRIP "${OS_ID}" OS_ID)

# For Debian-based distros we want to create DEB packages.
if("${OS_ID}" MATCHES "ubuntu|debian")

    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEB_COMPONENT_INSTALL "ON")
    set(CPACK_PACKAGE_VERSION "${CCMATH_VERSION}-${CPP_VERSION}")
    set(CPACK_DEBIAN_PACKAGE_SECTION "misc")
    set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/2getthere/ccmath-cpp")
    set(CPACK_DEBIAN_DEV_PACKAGE_DEPENDS "${CPACK_PACKAGE_NAME} (= ${CPACK_PACKAGE_VERSION})")
    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
    string(TOLOWER "${CPACK_PACKAGE_NAME}-dev" CPACK_DEBIAN_DEV_PACKAGE_NAME)
    string(TOLOWER "${CPACK_PACKAGE_NAME}" CPACK_DEBIAN_RUNTIME_PACKAGE_NAME)
    execute_process(COMMAND sh -c "(grep DISTRIB_CODENAME /etc/lsb-release 2>/dev/null || grep VERSION_CODENAME /etc/os-release) | sed 's/^.*=//g'" OUTPUT_VARIABLE OS_CODENAME)
    string(STRIP "${OS_CODENAME}" OS_CODENAME)
    execute_process(COMMAND dpkg --print-architecture OUTPUT_VARIABLE CPACK_PACKAGE_ARCHITECTURE)
    string(STRIP "${CPACK_PACKAGE_ARCHITECTURE}" CPACK_PACKAGE_ARCHITECTURE)
    set(FULL_VERSION "${CPACK_PACKAGE_VERSION}~${OS_CODENAME}_${CPACK_PACKAGE_ARCHITECTURE}")
    string(TOLOWER "${CPACK_DEBIAN_DEV_PACKAGE_NAME}_${FULL_VERSION}.deb" CPACK_DEBIAN_DEV_FILE_NAME)
    string(TOLOWER "${CPACK_DEBIAN_RUNTIME_PACKAGE_NAME}_${FULL_VERSION}.deb" CPACK_DEBIAN_RUNTIME_FILE_NAME)

# For Red Hat-based distros we want to create RPM packages.
elseif("${OS_ID}" MATCHES "fedora|centos|rhel")
    set(CPACK_GENERATOR "RPM")
    set(CPACK_RPM_COMPONENT_INSTALL "ON")
    set(CPACK_PACKAGE_VERSION "${CCMATH_VERSION}-${CPP_VERSION}")
    set(CPACK_RPM_PACKAGE_VERSION "${CCMATH_VERSION}")
    set(CPACK_RPM_PACKAGE_RELEASE "${CPP_VERSION}")
    set(CPACK_RPM_PACKAGE_URL "https://github.com/2getthere/ccmath-cpp")
    set(CPACK_RPM_PACKAGE_LICENSE "LGPL")
    set(CPACK_RPM_PACKAGE_DESCRIPTION "${CPACK_PACKAGE_DESCRIPTION_SUMMARY}")
    # Find dist tag
    execute_process(COMMAND sh -c "grep ^VERSION_ID= /etc/os-release | sed -e 's/^.*=//g' -e 's/\"//g'" OUTPUT_VARIABLE OS_VERSION)
    string(STRIP "${OS_VERSION}" OS_VERSION)
    if("${OS_ID}" MATCHES "fedora")
        set(CPACK_RPM_PACKAGE_RELEASE_DIST "fc${OS_VERSION}")
    else()
        set(CPACK_RPM_PACKAGE_RELEASE_DIST "el${OS_VERSION}")
    endif()
    # Find architecture
    execute_process(COMMAND rpm --eval "%{_arch}" OUTPUT_VARIABLE CPACK_PACKAGE_ARCHITECTURE)
    string(STRIP "${CPACK_PACKAGE_ARCHITECTURE}" CPACK_PACKAGE_ARCHITECTURE)
    set(CPACK_RPM_PACKAGE_AUTOREQ ON)
    set(VERSION_WITH_DIST "${CPACK_RPM_PACKAGE_VERSION}-${CPACK_RPM_PACKAGE_RELEASE}.${CPACK_RPM_PACKAGE_RELEASE_DIST}")
    set(CPACK_RPM_DEV_PACKAGE_REQUIRES "${CPACK_PACKAGE_NAME} = ${VERSION_WITH_DIST}")
    string(TOLOWER "${CPACK_PACKAGE_NAME}-dev" CPACK_RPM_DEV_PACKAGE_NAME)
    string(TOLOWER "${CPACK_PACKAGE_NAME}" CPACK_RPM_RUNTIME_PACKAGE_NAME)
    set(FULL_VERSION "${VERSION_WITH_DIST}.${CPACK_PACKAGE_ARCHITECTURE}")
    string(TOLOWER "${CPACK_PACKAGE_NAME}-dev-${FULL_VERSION}.rpm" CPACK_RPM_DEV_FILE_NAME)
    string(TOLOWER "${CPACK_PACKAGE_NAME}-${FULL_VERSION}.rpm" CPACK_RPM_RUNTIME_FILE_NAME)

else()
    message(WARNING "Could not determine type of package to create")
endif()

include(CPack)
