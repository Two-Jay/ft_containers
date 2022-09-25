#ifndef __FT_CONTAINERS_ITERATOR_TYPE__
#define __FT_CONTAINERS_ITERATOR_TYPE__

#include "./definition.hpp"

__LIBFT_CONTAINERS_START__

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : input_iterator_tag {};
struct bidirectional_iterator_tag : forward_iterator_tag {};
struct random_access_iterator_tag : bidirectional_iterator_tag {};

template <class _Iter>
struct Iterator_traits {
    typedef _Iter::difference_type       difference_type;
    typedef _Iter::value_type            value_type;
    typedef _Iter::pointer               pointer;
    typedef _Iter::reference             reference;
    typedef _Iter::iterator_category     iterator_category;
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

template <class Iter>
typename ft::Iterator_traits<Iter>::difference_type distance(Iter first, Iter last,ft::input_iterator_tag) {
    typename ft::Iterator_traits<Iter>::difference_type result = 0;
    for (; first != last ; ++first) {
        ++result;
    }
    return result;
}

template <class Iter>
typename ft::Iterator_traits<Iter>::difference_type distance(Iter first, Iter last,ft::random_access_iterator_tag) {
    return last - first;
}

template <class Iter>
typename ft::Iterator_traits<Iter>::difference_type distance(Iter first, Iter last) {
    return ft::distance(first, last, typename ft::Iterator_traits<Iter>::iterator_category());
}

__LIBFT_CONTAINERS_END__

#endif // __FT_CONTAINERS_ITERATOR_TYPE__
