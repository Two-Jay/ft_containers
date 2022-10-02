#ifndef __FT_CONTAINERS_ITERATOR_BASE__
#define __FT_CONTAINERS_ITERATOR_BASE__

#include <cstddef> // for ptrdiff_t

namespace ft {
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : input_iterator_tag {};
    struct bidirectional_iterator_tag : forward_iterator_tag {};
    struct random_access_iterator_tag : bidirectional_iterator_tag {};

    template <class _Iter>
    struct Iterator_traits {
        typedef typename _Iter::difference_type       difference_type;
        typedef typename _Iter::value_type            value_type;
        typedef typename _Iter::pointer               pointer;
        typedef typename _Iter::reference             reference;
        typedef typename _Iter::iterator_category     iterator_category;
    };

    template <class _Tp>
    struct Iterator_traits<_Tp*> {
        typedef std::ptrdiff_t                  difference_type;
        typedef ft::random_access_iterator_tag  iterator_category;
        typedef _Tp                             value_type;
        typedef _Tp*                            pointer;
        typedef _Tp&                            reference;
    };

    template <class _Tp>
    struct Iterator_traits<const _Tp*> {
        typedef std::ptrdiff_t                  difference_type;
        typedef ft::random_access_iterator_tag  iterator_category;
        typedef _Tp                             value_type;
        typedef const _Tp*                      pointer;
        typedef const _Tp&                      reference;
    };

    template <
        class _Category,
        class _T,
        class _Distance = std::ptrdiff_t,
        class _Pointer = _T*,
        class _Reference = _T&
    >
    struct Iterator {
        typedef _Category                        iterator_category;
        typedef _T                               value_type;
        typedef _Distance                        difference_type;
        typedef _Pointer                         pointer;
        typedef _Reference                       reference;
    };

    template <class _Iter>
    typename ft::Iterator_traits<_Iter>::iterator_category _iterator_category(const _Iter&) {
        return ft::Iterator_traits<_Iter>::iterator_category();
    }

    template <class _Iter>
    typename ft::Iterator_traits<_Iter>::difference_type _difference_type(const _Iter&) {
        return ft::Iterator_traits<_Iter>::difference_type();
    }

    template <class _Iter>
    typename ft::Iterator_traits<_Iter>::difference_type _distance(_Iter __first, _Iter __last, ft::input_iterator_tag) {
        typename ft::Iterator_traits<_Iter>::difference_type result = 0;
        for (; __first != __last ; ++__first) {
            ++result;
        }
        return result;
    }

    template <class _Iter>
    typename ft::Iterator_traits<_Iter>::difference_type _distance(_Iter __first, _Iter __last, ft::random_access_iterator_tag) {
        return __last - __first;
    }

    template <class _Iter>
    typename ft::Iterator_traits<_Iter>::difference_type distance(_Iter __first, _Iter __last) {
        return ft::_distance(__first, __last, _iterator_category(__first));
    }

    template <class _Iter>
    void _advance(_Iter iter, typename ft::Iterator_traits<_Iter>::difference_type n, ft::input_iterator_tag) {
        for (; n > 0; --n) {
            ++iter;
        }
    }

    template <class _Iter>
    void _advance(_Iter __iter, typename ft::Iterator_traits<_Iter>::difference_type n, ft::bidirectional_iterator_tag) {
        if (n < 0) {
            for (; n < 0; ++n) {
                --__iter;
            }
        } else {
            for (; n > 0; --n) {
                ++__iter;
            }
        }
    }

    template <class _Iter>
    void _advance(_Iter __iter, typename ft::Iterator_traits<_Iter>::difference_type n, ft::random_access_iterator_tag) {
        __iter += n;
    }

    template <class _Iter, class Distance>
    void advance(_Iter __iter, Distance __n) {
        ft::_advance(__iter, __n, _iterator_category(__iter));
    }
}

#endif // __FT_CONTAINERS_ITERATOR_T YPE__
