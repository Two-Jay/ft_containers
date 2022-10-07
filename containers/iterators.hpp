#ifndef __FT_CONTAINERS_ITERATOR_TYPE__
#define __FT_CONTAINERS_ITERATOR_TYPE__

#include "./iterator_base.hpp"
#include "./type_traits.hpp"

namespace ft
{
    template <class _Iter>
    class reverse_iterator
        : public ft::iterator<typename ft::iterator_traits<_Iter>::iterator_category,
                              typename ft::iterator_traits<_Iter>::value_type,
                              typename ft::iterator_traits<_Iter>::difference_type,
                              typename ft::iterator_traits<_Iter>::pointer,
                              typename ft::iterator_traits<_Iter>::reference>
    {
    public:
        typedef typename ft::iterator_traits<_Iter>::difference_type difference_type;
        typedef typename ft::iterator_traits<_Iter>::value_type value_type;
        typedef typename ft::iterator_traits<_Iter>::pointer pointer;
        typedef typename ft::iterator_traits<_Iter>::reference reference;
        typedef typename ft::iterator_traits<_Iter>::iterator_category iterator_category;

    protected:
        _Iter _current;

    public:
        reverse_iterator() : _current(_Iter()){};

        explicit reverse_iterator(_Iter __x) : _current(__x){};

        template <class _U>
        reverse_iterator(const reverse_iterator<_U> &__x) : _current(__x.base()){};

        template <class _U>
        reverse_iterator &operator=(const reverse_iterator<_U> &__x)
        {
            _current = __x.base();
            return *this;
        };

        ~reverse_iterator(){};

        reference operator*() const { return *(_current - 1); };

        pointer operator->(void) const { return &(operator*()); };

        reverse_iterator &operator++(void)
        {
            --_current;
            return *this;
        };

        reverse_iterator operator++(int)
        {
            reverse_iterator tmp(--_current);
            return tmp;
        };

        reverse_iterator &operator--(void)
        {
            ++_current;
            return *this;
        };

        reverse_iterator operator--(int)
        {
            reverse_iterator tmp(++_current);
            return tmp;
        };

        reverse_iterator operator+(const difference_type &__n) const { return reverse_iterator(_current + __n); };

        reverse_iterator &operator+=(const difference_type &__n)
        {
            _current += __n;
            return *this;
        };

        reverse_iterator operator-(const difference_type &__n) const { return reverse_iterator(_current - __n); };

        reverse_iterator &operator-=(difference_type __n)
        {
            _current -= __n;
            return *this;
        };

        reference operator[](difference_type __n) const { return *(*this + __n); };

        _Iter base(void) const { return _current; };
    };

    template <class _Iter>
    bool operator==(const reverse_iterator<_Iter> &__x, const reverse_iterator<_Iter> &__y)
    {
        return __x.base() == __y.base();
    }

    template <class _Iter>
    bool operator!=(const reverse_iterator<_Iter> &__x, const reverse_iterator<_Iter> &__y)
    {
        return !(__x.base() == __y.base());
    }

    template <class _Iter>
    bool operator<(const reverse_iterator<_Iter> &__x, const reverse_iterator<_Iter> &__y)
    {
        return __y.base() < __x.base();
    }

    template <class _Iter>
    bool operator>(const reverse_iterator<_Iter> &__x, const reverse_iterator<_Iter> &__y)
    {
        return __y.base() > __x.base();
    }

    template <class _Iter>
    bool operator<=(const reverse_iterator<_Iter> &__x, const reverse_iterator<_Iter> &__y)
    {
        return !(__y.base() > __x.base());
    }

    template <class _Iter>
    bool operator>=(const reverse_iterator<_Iter> &__x, const reverse_iterator<_Iter> &__y)
    {
        return !(__y.base() < __x.base());
    }

    template <class _Iter1, class _Iter2>
    typename ft::iterator_traits<_Iter1>::difference_type
    operator-(const reverse_iterator<_Iter1> &__x, const reverse_iterator<_Iter2> &__y)
    {
        return __y.base() - __x.base();
    }

    template <class _Iter>
    reverse_iterator<_Iter>
    operator+(typename ft::iterator_traits<_Iter>::difference_type __n, const reverse_iterator<_Iter> &__x)
    {
        return reverse_iterator<_Iter>(__x.base() - __n);
    }

    template <class _Iter, class _Container>
    class random_access_iterator
        : public ft::iterator<typename ft::iterator_traits<_Iter>::iterator_category,
                              typename ft::iterator_traits<_Iter>::value_type,
                              typename ft::iterator_traits<_Iter>::difference_type,
                              typename ft::iterator_traits<_Iter>::pointer,
                              typename ft::iterator_traits<_Iter>::reference>
    {
    protected:
        _Iter _current;

    public:
        typedef _Container                                              container_type;
        typedef typename ft::iterator_traits<_Iter>::difference_type    difference_type;
        typedef typename ft::iterator_traits<_Iter>::reference          reference;
        typedef typename ft::iterator_traits<_Iter>::pointer            pointer;

        random_access_iterator() : _current(_Iter()){};

        explicit
        random_access_iterator(const _Iter& __i) : _current(__i){};

        template <typename _It>
        inline random_access_iterator(const random_access_iterator<_It, _Container>& __i)
            : _current(__i.base()){};

        template <typename _U>
        random_access_iterator &operator=(const ft::random_access_iterator<_U, _Container> &_it)
        {
            _current = _it.base();
            return *this;
        };

        ~random_access_iterator(){};

        reference
        operator*(void) const { return *_current; };

        pointer
        operator->(void) const { return _current; };

        random_access_iterator&
        operator++() {
            ++_current;
            return *this;
        };

        random_access_iterator
        operator++(int) {
            random_access_iterator tmp(*this);
            ++_current;

            return tmp;
        };

        random_access_iterator &
        operator--() {
            _current--;
            return *this;
        };

        random_access_iterator
        operator--(int) {
            random_access_iterator tmp(*this);
            --_current;

            return tmp;
        };

        random_access_iterator &
        operator+=(const difference_type &__n)
        {
            _current += __n;
            return *this;
        };

        random_access_iterator &
        operator-=(const difference_type &__n)
        {
            _current -= __n;
            return *this;
        };

        random_access_iterator
        operator+(const difference_type &__n) const { return random_access_iterator(_current + __n); };

        random_access_iterator
        operator-(const difference_type &__n) const { return random_access_iterator(_current + __n); };

        difference_type
        operator+(const random_access_iterator &__it) { return this->_current + __it.base(); };

        difference_type
        operator-(const random_access_iterator &__it) { return this->_current - __it.base(); };

        reference
        operator[](const difference_type &__n) { return _current[__n]; };

        _Iter
        base() const { return this->_current; };
    };

    template <typename _Iter1, typename _Iter2, typename _Container>
    bool operator==(const ft::random_access_iterator<_Iter1, _Container> &__lhs,
                    const ft::random_access_iterator<_Iter2, _Container> &__rhs)
    {
        return (__lhs.base() == __rhs.base());
    }

    template <typename _Iter1, typename _Iter2, typename _Container>
    bool operator!=(const ft::random_access_iterator<_Iter1, _Container> &__lhs,
                    const ft::random_access_iterator<_Iter2, _Container> &__rhs)
    {
        return !(__lhs == __rhs);
    }

    template <typename _Iter1, typename _Iter2, typename _Container>
    bool operator<(const ft::random_access_iterator<_Iter1, _Container> &__lhs,
                   const ft::random_access_iterator<_Iter2, _Container> &__rhs)
    {
        return __lhs.base() < __rhs.base();
    }

    template <typename _Iter1, typename _Iter2, typename _Container>
    bool operator>(const ft::random_access_iterator<_Iter1, _Container> &__lhs,
                   const ft::random_access_iterator<_Iter2, _Container> &__rhs)
    {
        return __lhs.base() > __rhs.base();
    }

    template <typename _Iter1, typename _Iter2, typename _Container>
    bool operator<=(const ft::random_access_iterator<_Iter1, _Container> &__lhs,
                    const ft::random_access_iterator<_Iter2, _Container> &__rhs)
    {
        return !(__lhs.base() > __rhs.base());
    }

    template <typename _Iter1, typename _Iter2, typename _Container>
    bool operator>=(const ft::random_access_iterator<_Iter1, _Container> &__lhs,
                    const ft::random_access_iterator<_Iter2, _Container> &__rhs)
    {
        return !(__lhs.base() < __rhs.base());
    }

    template <typename _Iter, typename _Container>
    random_access_iterator<_Iter, _Container>
    operator+(typename random_access_iterator<_Iter, _Container>::difference_type __n,
              const random_access_iterator<_Iter, _Container> &__it)
    {
        return random_access_iterator<_Iter, _Container>(__it.base() + __n);
    }

}

#endif // __FT_CONTAINERS_ITERATOR_TYPE__
