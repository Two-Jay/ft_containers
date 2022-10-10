#ifndef __ALLOC_TRAITS_HPP__
#define __ALLOC_TRAITS_HPP__

#include <limits>

namespace ft {
    template <class _Tp, class _Allocator>
    struct Alloc_traits {
        static const bool _instanceless = false;
        typedef typename _Allocator::template rebind<_Tp>::other allocator_type;
    };

    template <class _Tp, class _Allocator>
    const bool Alloc_traits<_Tp, _Allocator>::_instanceless;

    template <class _Tp, class _Tp1> 
    struct Alloc_traits<_Tp, std::allocator<_Tp1> >{
        static const bool _instanceless = true;
    };
}

#endif // __ALLOC_TRAITS_HPP__
