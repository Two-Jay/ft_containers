#ifndef __FT_CONTAINERS_COMPRESSED_PAIR__
#define __FT_CONTAINERS_COMPRESSED_PAIR__

#include "definition.hpp"

__LIBFT_CONTAINERS_START__

// Tag used to default initialize one or both of the pair's elements.
struct __default_init_tag {};
struct __value_init_tag {};

template<class _T,
        int _Idx,
        bool _CanBeEmptyBase = is_empty<T>::value && !__libcpp_is_final<T>::value>
struct __compressed_pair_elem {
    typedef _T                  _ParamT;
    typedef _T&                 reference;
    typedef const _T&           const_reference;

    __compressed_pair_elem(__default_init_tag) {}
    __compressed_pair_elem(__value_init_tag) : __value_() {}

    private:
        _Tp                     __value_;
}


template<class T1, class T2>
class __compressed_pair : private 

__LIBFT_CONTAINERS_END__

#endif // __FT_CONTAINERS_COMPRESSED_PAIR__