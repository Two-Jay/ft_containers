#ifndef __FT_CONTAINERS_ITERATOR_TYPE__
#define __FT_CONTAINERS_ITERATOR_TYPE__

#include "./iterator_base.hpp"
#include "./concept_check.hpp"
#include "./type_traits.hpp"

namespace ft
{
    template <class _Iter>
    class reverse_iterator {
    public:
        typedef _Iter                                                   iterator_type;
        typedef typename ft::iterator_traits<_Iter>::difference_type    difference_type;
        typedef typename ft::iterator_traits<_Iter>::value_type         value_type;
        typedef typename ft::iterator_traits<_Iter>::pointer            pointer;
        typedef typename ft::iterator_traits<_Iter>::reference          reference;
        typedef typename ft::iterator_traits<_Iter>::iterator_category  iterator_category;

    protected:
        iterator_type _current;

    public:
        reverse_iterator() : _current(iterator_type()) {}

        explicit
        reverse_iterator(iterator_type _x) : _current(_x){}
    
        template<typename _U>
        reverse_iterator(const reverse_iterator<_U>& _it) : _current(_it.base()) {}

        template <class _it>
        reverse_iterator&
        operator=(const reverse_iterator<_it> &__x) {
            _current = __x.base();
            return *this;
        };
        
        iterator_type
        base() const {
            return _current;
        };

        reference
        operator* () const { 
            iterator_type __tmp = _current;
            return *--__tmp;
        };

        pointer
        operator-> () const {
            return &operator*();
        };

        reverse_iterator&
        operator++ () {
            --_current;
            return *this;
        };

        reverse_iterator
        operator++ (int) {
            reverse_iterator __tmp(*this);
            --_current;
            return __tmp;
        };

        reverse_iterator&
        operator-- () {
            ++_current;
            return *this;
        };

        reverse_iterator
        operator-- (int) {
            reverse_iterator __tmp(*this);
            ++_current;
            return __tmp;
        };

        reverse_iterator
        operator- (difference_type __n) const {
            return reverse_iterator(_current + __n);
        };

        reverse_iterator
        operator+ (difference_type __n) const {
            return reverse_iterator(_current - __n);
        };

        reverse_iterator&
        operator-= (difference_type __n) {
            _current += __n;
            return *this;
        };

        reverse_iterator&
        operator+= (difference_type __n) {
            _current -= __n;
            return *this;
        };

        reference
        operator[] (difference_type __n) const {
            return *(*this + __n);
        };
    };

    #define REVERSE_RELOPE_MACRO(OP) \
        __x.base() OP __y.base()
    #define REVERSE_CALOPE_MACRO(OP) \
        __y.base() OP __x.base()

    template <class _Iter1, class _Iter2>
    inline bool operator==(const reverse_iterator<_Iter1> &__x,
        const reverse_iterator<_Iter2> &__y)
    {
        return REVERSE_RELOPE_MACRO(==);
    }

    template <class _Iter1, class _Iter2>
    inline bool operator!=(const reverse_iterator<_Iter1> &__x,
        const reverse_iterator<_Iter2> &__y)
    {
        return REVERSE_RELOPE_MACRO(!=);
    }

    template <class _Iter1, class _Iter2>
    inline bool operator<(const reverse_iterator<_Iter1> &__x,
        const reverse_iterator<_Iter2> &__y)
    {
        return REVERSE_RELOPE_MACRO(>);
    }

    template <class _Iter1, class _Iter2>
    inline bool operator>(const reverse_iterator<_Iter1> &__x,
        const reverse_iterator<_Iter2> &__y)
    {
        return REVERSE_RELOPE_MACRO(<);
    }

    template <class _Iter1, class _Iter2>
    inline bool operator<=(const reverse_iterator<_Iter1> &__x,
        const reverse_iterator<_Iter2> &__y)
    {
        return REVERSE_RELOPE_MACRO(>=);
    }

    template <class _Iter1, class _Iter2>
    inline bool operator>=(const reverse_iterator<_Iter1> &__x,
        const reverse_iterator<_Iter2> &__y)
    {
        return REVERSE_RELOPE_MACRO(<=);
    }

    template <typename _Iter1, typename _Iter2>
    inline typename reverse_iterator<_Iter1>::difference_type
    operator-(const reverse_iterator<_Iter1> &__x,
                    const reverse_iterator<_Iter2> &__y)
    {
        return __y.base() - __x.base();
    }

    template <typename _Iter1, typename _Iter2>
    inline typename reverse_iterator<_Iter1>::difference_type
    operator+(const reverse_iterator<_Iter1> &__x,
                    const reverse_iterator<_Iter2> &__y)
    {
        return REVERSE_CALOPE_MACRO(-);
    }

    #undef REVERSE_RELOPE_MACRO
    #undef REVERSE_CALOPE_MACRO

    template <class _Iter>
    inline reverse_iterator<_Iter>
    operator+(typename ft::iterator_traits<_Iter>::difference_type __n,
        const reverse_iterator<_Iter> &__x)
    {
        return reverse_iterator<_Iter>(__x.base() - __n);
    }



    template <class _Iter>
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
        typedef _Iter                                                   iterator_type;
        typedef typename ft::iterator_traits<_Iter>::difference_type    difference_type;
        typedef typename ft::iterator_traits<_Iter>::value_type         value_type;
        typedef typename ft::iterator_traits<_Iter>::reference          reference;
        typedef typename ft::iterator_traits<_Iter>::pointer            pointer;

        random_access_iterator() : _current(_Iter()){};

        explicit
        random_access_iterator(iterator_type __i) : _current(__i){};

        template <typename _U>
        inline random_access_iterator(const random_access_iterator<_U>& __i
            , typename ft::enable_if<!ft::is_integral<_U>::value>::type* = 0)
            : _current(__i.base()){};

        template <typename _U>
        random_access_iterator&
        operator=(const random_access_iterator<_U> &_it) {
            _current = _it.base();
            return *this;
        };

        reference
        operator*() const {
            return *_current;
        };

        pointer
        operator->() const {
            return _current;
        };

        random_access_iterator&
        operator++() {
            ++_current;
            return *this;
        };

        random_access_iterator
        operator++(int) {
            random_access_iterator temp(*this);
            ++_current;
            return temp;
        };

        random_access_iterator&
        operator--() {
            --_current;
            return *this;
        };

        random_access_iterator
        operator--(int) {
            random_access_iterator temp(*this);
            --_current;
            return temp;
        };

        random_access_iterator
        operator+=(difference_type __n) {
            _current += __n;
            return *this;
        };

        random_access_iterator
        operator-=(difference_type __n) {
            _current -= __n;
            return *this;
        };

        random_access_iterator
        operator-(difference_type __n) const {
            random_access_iterator temp(*this);
            temp -= __n;
            return temp;
        };

        random_access_iterator
        operator+(difference_type __n) const {
            random_access_iterator temp(*this);
            temp += __n;
            return temp;
        };

        reference
        operator[](const difference_type &__n) {
            return _current[__n];
        };

        iterator_type
        base() const {
            return this->_current;
        };
    };

    #define RANDITER_OPE_MACRO(OP) \
        __x.base() OP __y.base()

    template <typename _Iter1, typename _Iter2>
    bool operator==(const random_access_iterator<_Iter1> &__x,
                    const random_access_iterator<_Iter2> &__y)
    {
        return RANDITER_OPE_MACRO(==);
    }

    template <typename _Iter1, typename _Iter2>
    bool operator!=(const random_access_iterator<_Iter1> &__x,
                    const random_access_iterator<_Iter2> &__y)
    {
        return RANDITER_OPE_MACRO(!=);
    }

    template <typename _Iter1, typename _Iter2>
    bool operator<(const random_access_iterator<_Iter1> &__x,
                   const random_access_iterator<_Iter2> &__y)
    {
        return RANDITER_OPE_MACRO(<);
    }

    template <typename _Iter1, typename _Iter2>
    bool operator>(const random_access_iterator<_Iter1> &__x,
                   const random_access_iterator<_Iter2> &__y)
    {
        return RANDITER_OPE_MACRO(>);
    }

    template <typename _Iter1, typename _Iter2>
    bool operator<=(const random_access_iterator<_Iter1> &__x,
                    const random_access_iterator<_Iter2> &__y)
    {
        return RANDITER_OPE_MACRO(<=);
    }

    template <typename _Iter1, typename _Iter2>
    bool operator>=(const random_access_iterator<_Iter1> &__x,
                    const random_access_iterator<_Iter2> &__y)
    {
        return RANDITER_OPE_MACRO(>=);
    }

    template <typename _T>
    bool operator==(const random_access_iterator<_T> &__x,
                    const random_access_iterator<_T> &__y)
    {
        return RANDITER_OPE_MACRO(==);
    }

    template <typename _T>
    bool operator!=(const random_access_iterator<_T> &__x,
                    const random_access_iterator<_T> &__y)
    {
        return RANDITER_OPE_MACRO(!=);
    }

    template <typename _T>
    bool operator<(const random_access_iterator<_T> &__x,
                   const random_access_iterator<_T> &__y)
    {
        return RANDITER_OPE_MACRO(<);
    }

    template <typename _T>
    bool operator>(const random_access_iterator<_T> &__x,
                   const random_access_iterator<_T> &__y)
    {
        return RANDITER_OPE_MACRO(>);
    }

    template <typename _T>
    bool operator<=(const random_access_iterator<_T> &__x,
                    const random_access_iterator<_T> &__y)
    {
        return RANDITER_OPE_MACRO(<=);
    }

    template <typename _T>
    bool operator>=(const random_access_iterator<_T> &__x,
                    const random_access_iterator<_T> &__y)
    {
        return RANDITER_OPE_MACRO(>=);
    }

    template <typename _Iter1, typename _Iter2>
    inline typename random_access_iterator<_Iter1>::difference_type
    operator-(const random_access_iterator<_Iter1> &__x,
                    const random_access_iterator<_Iter2> &__y)
    {
        return RANDITER_OPE_MACRO(-);
    }

    template <typename _Iter1, typename _Iter2>
    inline typename random_access_iterator<_Iter1>::difference_type
    operator+(const random_access_iterator<_Iter1> &__x,
                    const random_access_iterator<_Iter2> &__y)
    {
        return RANDITER_OPE_MACRO(+);
    }

    #undef RANDITER_OPE_MACRO

    template <typename _Iter>
    inline random_access_iterator<_Iter>
    operator+(typename random_access_iterator<_Iter>::difference_type __n,
              const random_access_iterator<_Iter> &__it)
    {
        return random_access_iterator<_Iter>(__it.base() + __n);
    }

}

#endif // __FT_CONTAINERS_ITERATOR_TYPE__
