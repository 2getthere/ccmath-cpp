#!/bin/sh
set -e
rm -rf build
mkdir build
cd build
export CMAKE_INSTALL_PREFIX=/usr    # to let Debian use lib/<multiarch-tuple>
cmake -DCMAKE_BUILD_TYPE=Release ..
make
cpack
