#ifndef __FT_CONTAINERS_ITERATOR_TYPE__
#define __FT_CONTAINERS_ITERATOR_TYPE__

#include "./definition.hpp"
#include <vector>

__LIBFT_CONTAINERS_START__

template<class _Iter, class _Container>
class Random_access_iterator
    : public ft::Iterator <typename ft::Iterator_traits<_Iter>::iterator_category
                        typename ft::Iterator_traits<_Iter>::value_type,
                        typename ft::Iterator_traits<_Iter>::difference_type,
                        typename ft::Iterator_traits<_Iter>::pointer,
                        typename ft::Iterator_traits<_Iter>::reference>
{
    protected :
        Iterator _mock_iter

    public :
        typedef typename ft::Iterator_traits<_Iter>::difference_type    difference_type;
        typedef typename ft::Iterator_traits<_Iter>::reference          reference;
        typedef typename ft::Iterator_traits<_Iter>::pointer            pointer;

    Random_access_iterator() : _mock_iter(ft::Iterator()) {};

    Random_access_iterator(const Iter& __i) : _mock_iter(__i) {};

    template<typename _Iter>
    Random_access_iterator(const Random_access_iterator<_Iter, _Container>& __i) : _mock_iter(__i.base()){};

    ~Random_access_iterator() {};
    
    
    reference
    operator*() const { return *_mock_iter; };
    
    pointer
    operator->() const { return _mock_iter; };

    Random_access_iterator&
    operator++() const { ++_mock_iter; return *this; };
    
    Random_access_iterator
    operator++(int) const { return Random_access_iterator(_mock_iter++); };

    Random_access_iterator&
    operator--() const { --_mock_iter; return *this; };
    
    Random_access_iterator
    operator--(int) const { return Random_access_iterator(_mock_iter--); };

    Random_access_iterator&
    operator+= (const difference_type& __n) { _mock_iter += __n; return *this; };
    
    Random_access_iterator
    operator+ (const difference_type& __n) const { return Random_access_iterator(_mock_iter + __n); };

    Random_access_iterator&
    operator-= (const difference_type& __n) { _mock_iter -= __n; return *this; };

    Random_access_iterator
    operator- (const difference_type& __n) const { return Random_access_iterator(_mock_iter + __n); };

    difference_type
    operator+ (const Random_access_iterator& __it) { return this->_mock_iter + __it.base(); };

    difference_type
    operator- (const Random_access_iterator& __it) { return this->_mock_iter - __it.base(); };

    reference
    operator[] (const difference_type& __n) { return _mock_iter[__n]; };

    const Iter&
    base() const { return this->_mock_iter; };
};

template<typename _Iter1, typename _Iter2, typename _Container>
bool operator== (const ft::Random_access_iterator<_Iter1, _Container>& __lhs, 
                const ft::Random_access_iterator<_Iter2, _Container>& __rhs)
{
    return (__lhs.base() == __rhs.base());
};

template<typename _Iter1, typename _Iter2, typename _Container>
bool operator!= (const ft::Random_access_iterator<_Iter1, _Container>& __lhs, 
                const ft::Random_access_iterator<_Iter2, _Container>& __rhs)
{
    return !(__lhs == __rhs);
};

template<typename _Iter1, typename _Iter2, typename _Container>
bool operator< (const ft::Random_access_iterator<_Iter1, _Container>& lhs, 
                const ft::Random_access_iterator<_Iter2, _Container>& __rhs)
{
    return __lhs.base() < __rhs.base();
};

template<typename _Iter1, typename _Iter2, typename _Container>
bool operator> (const ft::Random_access_iterator<_Iter1, _Container>& lhs, 
                const ft::Random_access_iterator<_Iter2, _Container>& __rhs)
{
    return __lhs.base() > __rhs.base();
};

template<typename _Iter1, typename _Iter2, typename _Container>
bool operator<= (const ft::Random_access_iterator<_Iter1, _Container>& lhs, 
                const ft::Random_access_iterator<_Iter2, _Container>& __rhs)
{
    return !(__lhs.base() > __rhs.base());
};

template<typename _Iter1, typename _Iter2, typename _Container>
bool operator>= (const ft::Random_access_iterator<_Iter1, _Container>& lhs, 
                const ft::Random_access_iterator<_Iter2, _Container>& __rhs)
{
    return !(__lhs.base() < __rhs.base());
};

template<typename _Iter, typename _Container>
Random_access_iterator<_Iter, _Container>
operator+ (typename Random_access_iterator<_Iter, _Container>::difference_type __n,
            const Random_access_iterator<_Iter, _Container>& __it)
{
    return Random_access_iterator<_Iter, _Container>(__it.base() + __n);
}

template<class _Iter, class _Container>
class Bidirectional_iterator : public Random_access_iterator<_Iter, _Container> {

}


__LIBFT_CONTAINERS_END__

#endif // __FT_CONTAINERS_ITERATOR_TYPE__