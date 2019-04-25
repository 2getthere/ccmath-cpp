#ifndef _array_storage_HH_
#define _array_storage_HH_

#include <cstring> // memset
#include <new>

template<typename TYPE>
class array_storage
{
public:
    typedef TYPE value;

    constexpr static int INTERNAL_ELEMENTS = (1024/sizeof(TYPE)); // arbitrary 1 kB

    explicit inline array_storage(int n, bool erase = true)
        : _use_external_storage(n > INTERNAL_ELEMENTS)
        , _data(_use_external_storage ? new value[n] : _internal_storage)
    {
        if (erase) {
            memset(_data, 0, n*sizeof(value));
        }
    }

    inline ~array_storage()
    {
        if (_use_external_storage) {
            delete[] _data;
        }
    }

    inline value * array() { return _data; }

private:
    const bool _use_external_storage;
    value * const _data;
    value _internal_storage[INTERNAL_ELEMENTS];
};

#endif // _array_storage_HH_
