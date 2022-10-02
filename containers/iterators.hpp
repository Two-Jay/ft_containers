#ifndef __FT_CONTAINERS_ITERATOR_TYPE__
#define __FT_CONTAINERS_ITERATOR_TYPE__

#include "./definition.hpp"

__LIBFT_CONTAINERS_START__

template<class _Iter>
class Reverse_iterator 
    : public ft::Iterator <typename ft::Iterator_traits<_Iter>::iterator_category
                        typename ft::Iterator_traits<_Iter>::value_type,
                        typename ft::Iterator_traits<_Iter>::difference_type,
                        typename ft::Iterator_traits<_Iter>::pointer,
                        typename ft::Iterator_traits<_Iter>::reference>
{
    public :
        typedef typename ft::Iterator_traits<_Iter>::difference_type    difference_type;
        typedef typename ft::Iterator_traits<_Iter>::value_type         value_type;
        typedef typename ft::Iterator_traits<_Iter>::pointer            pointer;
        typedef typename ft::Iterator_traits<_Iter>::reference          reference;
        typedef typename ft::Iterator_traits<_Iter>::iterator_category  iterator_category;
    protected :
        _Iter   _current;

    public :
        Reverse_iterator() : _current(_Iter()) {};
        
        explicit Reverse_iterator(_Iter __x) : _current(__x) {};

        template <class _U>
        Reverse_iterator(const Reverse_iterator<_U>& __x) : _current(__x.base()) {};

        template <class _U>
        Reverse_iterator& operator=(const Reverse_iterator<_U>& __x) {
            _current = __x.base();
            return *this;
        };

        ~Reverse_iterator() {};

        reference operator*() const { return *(_current - 1);};

        pointer operator->(void) const { return &(operator*()); };

        Reverse_iterator& operator++(void) {
            --_current;
            return *this;
        };

        Reverse_iterator operator++(int) { return Reverse_iterator tmp(--_current); };

        Reverse_iterator& operator--(void) {
            ++_current;
            return *this;
        };

        Reverse_iterator operator--(int) { return Reverse_iterator tmp(++_current); };

        Reverse_iterator operator+(const difference_type& __n) const { return Reverse_iterator(_current + __n);};

        Reverse_iterator& operator+=(const difference_type& __n) {
            _current += __n;
            return *this;
        };

        Reverse_iterator operator-(const difference_type& __n) const { return Reverse_iterator(_current - __n); };

        Reverse_iterator& operator-=(difference_type __n) {
            _current -= __n;
            return *this;
        };

        reference operator[](difference_type __n) const { return *(*this + __n); };

        _Iter base(void) const { return _current; };
};

template <class _Iter>
bool operator==(const Reverse_iterator<_Iter>& __x, const Reverse_iterator<_Iter>& __y) {
    return __x.base() == __y.base();
};

template <class _Iter>
bool operator!=(const Reverse_iterator<_Iter>& __x, const Reverse_iterator<_Iter>& __y) {
    return !(__x.base() == __y.base());
};

template <class _Iter>
bool operator<(const Reverse_iterator<_Iter>& __x, const Reverse_iterator<_Iter>& __y) {
    return __y.base() < __x.base();
};

template <class _Iter>
bool operator>(const Reverse_iterator<_Iter>& __x, const Reverse_iterator<_Iter>& __y) {
    return __y.base() > __x.base();
};

template <class _Iter>
bool operator<=(const Reverse_iterator<_Iter>& __x, const Reverse_iterator<_Iter>& __y) {
    return !(__y.base() > __x.base());
};

template <class _Iter>
bool operator>=(const Reverse_iterator<_Iter>& __x, const Reverse_iterator<_Iter>& __y) {
    return !(__y.base() < __x.base());
};

template <class _Iter1, class _Iter2>
typename ft::Iterator_traits<_Iter1>::difference_type
operator-(const Reverse_iterator<_Iter1>& __x, const Reverse_iterator<_Iter2>& __y) {
    return __y.base() - __x.base();
};

template <class _Iter>
Reverse_iterator<_Iter>
operator+(typename ft::Iterator_traits<_Iter>::difference_type __n, const Reverse_iterator<_Iter>& __x) {
    return Reverse_iterator<_Iter>(__x.base() - __n);
};


template<class _Iter, class _Container>
class Random_access_iterator
    : public ft::Iterator <typename ft::Iterator_traits<_Iter>::iterator_category
                        typename ft::Iterator_traits<_Iter>::value_type,
                        typename ft::Iterator_traits<_Iter>::difference_type,
                        typename ft::Iterator_traits<_Iter>::pointer,
                        typename ft::Iterator_traits<_Iter>::reference>
{
    protected :
        _Iter   _current

    public :
        typedef typename ft::Iterator_traits<_Iter>::difference_type    difference_type;
        typedef typename ft::Iterator_traits<_Iter>::reference          reference;
        typedef typename ft::Iterator_traits<_Iter>::pointer            pointer;

    Random_access_iterator() : _current(ft::Iterator()) {};

    Random_access_iterator(const Iter& __i) : _current(__i) {};

    template<typename _Iter>
    Random_access_iterator(const Random_access_iterator<_Iter, _Container>& __i) : _current(__i.base()){};

    template<typename _U>
    Random_access_iterator(const Random_access_iterator<_U>& _it, typename ft::enable_if<!ft::is_integral<_U>>::value::type* = 0) : _current(_it.base()) {};

    template<typename _U>
    Random_access_iterator& operator=(const Random_access_iterator<_U>& _it) {
        _current = _it.base();
        return *this;
    };

    ~Random_access_iterator() {};
    
    
    reference
    operator*() const { return *_current; };
    
    pointer
    operator->() const { return _current; };

    Random_access_iterator&
    operator++() const { ++_current; return *this; };
    
    Random_access_iterator
    operator++(int) const { return Random_access_iterator(_current++); };

    Random_access_iterator&
    operator--() const { --_current; return *this; };
    
    Random_access_iterator
    operator--(int) const { return Random_access_iterator(_current--); };

    Random_access_iterator&
    operator+= (const difference_type& __n) { _current += __n; return *this; };
    
    Random_access_iterator
    operator+ (const difference_type& __n) const { return Random_access_iterator(_current + __n); };

    Random_access_iterator&
    operator-= (const difference_type& __n) { _current -= __n; return *this; };

    Random_access_iterator
    operator- (const difference_type& __n) const { return Random_access_iterator(_current + __n); };

    difference_type
    operator+ (const Random_access_iterator& __it) { return this->_current + __it.base(); };

    difference_type
    operator- (const Random_access_iterator& __it) { return this->_current - __it.base(); };

    reference
    operator[] (const difference_type& __n) { return _current[__n]; };

    const Iter&
    base() const { return this->_current; };
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


__LIBFT_CONTAINERS_END__

#endif // __FT_CONTAINERS_ITERATOR_TYPE__