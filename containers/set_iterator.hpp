#ifndef __FT_CONTAINERS__SET_ITERATOR__
#define __FT_CONTAINERS__SET_ITERATOR__

#include "iterator_base.hpp"
#include "rbt_node.hpp"


namespace ft
{
    template <class T1, class T2, class _Iter>
    class const_set_iterator;

    template <class T1, class T2, class _Iter>
    class set_iterator {
        public :
            typedef _Iter                                                           iterator_type;
            typedef ft::bidirectional_iterator_tag                                  iterator_category;
            typedef typename ft::iterator_traits<iterator_type>::value_type         value_type;
            typedef typename ft::iterator_traits<iterator_type>::difference_type    difference_type;
            typedef typename ft::iterator_traits<iterator_type>::reference          reference;
            typedef typename ft::iterator_traits<iterator_type>::pointer            pointer;
            
        private :
            typedef ft::rbt_node<T1, T2>*                                           node_pointer;     
            node_pointer   _nptr;

        public :
			set_iterator() {}

			set_iterator(const node_pointer& __p, typename ft::enable_if<!ft::is_same<node_pointer, set_iterator>::value>::type* = 0) : _nptr(__p) {}

			set_iterator(const set_iterator& __iter) : _nptr(__iter.base()) {};

            set_iterator&
            operator=(const set_iterator& __x) {
                if (this != &__x) {
                    this->_nptr = __x.base();
                }
                return *this;
            }

            ~set_iterator() {};

            node_pointer
            base() const {
                return this->_nptr;
            }

            reference
            operator*() const {
                return this->_nptr->_value->first;
            }

            pointer
            operator->() const {
                return &(this->_nptr->_value->first);
            }

            set_iterator&
            operator++() {
                this->_nptr = next(this->_nptr);
                return *this;
            }

            set_iterator
            operator++(int) {
                set_iterator __tmp(*this);
                this->_nptr = next(this->_nptr);
                return __tmp;
            }

            set_iterator&
            operator--() {
                this->_nptr = prev(this->_nptr);
                return *this;
            }

            set_iterator
            operator--(int) {
                set_iterator __tmp(*this);
                this->_nptr = prev(this->_nptr);
                return __tmp;
            }

        protected :

            node_pointer
            next(node_pointer __nptr) {
                if (__nptr->_color == NIL) return __nptr;
                if (__nptr->_right->_color != NIL)
                    return _minimum_from(__nptr->_right);
                return _find_ancester_right(__nptr);
            }

            node_pointer
            prev(node_pointer __nptr) {
                if (__nptr->_color == NIL) return __nptr->_parent;
                if (__nptr->_color != NIL && __nptr->_left->_color != NIL)
                    return _maximum_from(__nptr->_left);
                return _find_ancester_left(__nptr);
            }
            

            node_pointer
            _minimum_from(node_pointer __x) {
                while (__x->_left->_color != NIL)
                    __x = __x->_left;
                return __x;
            }

            node_pointer
            _maximum_from(node_pointer __x) {
                while (__x->_right->_color != NIL)
                    __x = __x->_right;
                return __x;
            }

            node_pointer
            _find_ancester_right(node_pointer __x) {
                node_pointer __y = __x->_parent;
                while (__y->_color != NIL && __x == __y->_right) {
                    __x = __y;
                    __y = __y->_parent;
                }
                return __y;
            }

            node_pointer
            _find_ancester_left(node_pointer __x) {
                node_pointer __y = __x->_parent;
                while (__y->_color != NIL && __x == __y->_left) {
                    __x = __y;
                    __y = __y->_parent;
                }
                return __y->_color != NIL ? __y : __x;
            }

        private :

            template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2> friend bool operator==(const set_iterator<T11, T12, _Iter1>&, const set_iterator<T21, T22, _Iter2>&);
            template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2> friend bool operator==(const set_iterator<T11, T12, _Iter1>&, const const_set_iterator<T21, T22, _Iter2>&);
            template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2> friend bool operator==(const const_set_iterator<T11, T12, _Iter1>&, const set_iterator<T21, T22, _Iter2>&);

            template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2> friend bool operator<(const set_iterator<T11, T12, _Iter1>&, const set_iterator<T21, T22, _Iter2>&);
            template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2> friend bool operator<(const set_iterator<T11, T12, _Iter1>&, const const_set_iterator<T21, T22, _Iter2>&);
            template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2> friend bool operator<(const const_set_iterator<T11, T12, _Iter1>&, const set_iterator<T21, T22, _Iter2>&);

            template<class, class, class, class> friend class rbt_tree;
			template<class, class, class, class> friend class map;
            template<class, class, class> friend class const_set_iterator;
    };

    template <class T1, class T2, class _Iter>
    class const_set_iterator {
        public :
            typedef _Iter                                                           iterator_type;
            typedef ft::bidirectional_iterator_tag                                  iterator_category;
            typedef typename ft::iterator_traits<iterator_type>::value_type         value_type;
            typedef typename ft::iterator_traits<iterator_type>::difference_type    difference_type;
            typedef typename ft::iterator_traits<iterator_type>::reference          reference;
            typedef typename ft::iterator_traits<iterator_type>::pointer            pointer;
            
        private :
            typedef ft::rbt_node<T1, T2>*                                           node_pointer;     
            node_pointer   _nptr;

        public :
			const_set_iterator() {}

			const_set_iterator(const node_pointer& __p, typename ft::enable_if<!ft::is_same<node_pointer, const_set_iterator>::value>::type* = 0) : _nptr(__p) {}

            const_set_iterator(const set_iterator<T1, T2, _Iter>& __x) : _nptr(__x.base()) {}

			const_set_iterator(const const_set_iterator& __iter) : _nptr(__iter.base()) {};

            const_set_iterator&
            operator=(const const_set_iterator& __x) {
                if (this != &__x) {
                    this->_nptr = __x.base();
                }
                return *this;
            }

            const_set_iterator&
            operator=(const set_iterator<T1, T2, _Iter>& __x) {
                this->_nptr = __x.base();
                return *this;
            }

            ~const_set_iterator() {};

            node_pointer
            base() const {
                return this->_nptr;
            }

            reference
            operator*() const {
                return *(this->_nptr->_value);
            }

            pointer
            operator->() const {
                return this->_nptr->_value;
            }

            const_set_iterator&
            operator++() {
                this->_nptr = next(this->_nptr);
                return *this;
            }

            const_set_iterator
            operator++(int) {
                const_set_iterator __tmp(*this);
                this->_nptr = next(this->_nptr);
                return __tmp;
            }

            const_set_iterator&
            operator--() {
                this->_nptr = prev(this->_nptr);
                return *this;
            }

            const_set_iterator
            operator--(int) {
                const_set_iterator __tmp(*this);
                this->_nptr = prev(this->_nptr);
                return __tmp;
            }

        protected :

            node_pointer
            next(node_pointer __nptr) {
                if (__nptr->_color == NIL) return __nptr;
                if (__nptr->_right->_color != NIL)
                    return _minimum_from(__nptr->_right);
                return _find_ancester_right(__nptr);
            }

            node_pointer
            prev(node_pointer __nptr) {
                if (__nptr->_color == NIL) return __nptr->_parent;
                if (__nptr->_color != NIL && __nptr->_left->_color != NIL)
                    return _maximum_from(__nptr->_left);
                return _find_ancester_left(__nptr);
            }
            

            node_pointer
            _minimum_from(node_pointer __x) {
                while (__x->_left->_color != NIL)
                    __x = __x->_left;
                return __x;
            }

            node_pointer
            _maximum_from(node_pointer __x) {
                while (__x->_right->_color != NIL)
                    __x = __x->_right;
                return __x;
            }

            node_pointer
            _find_ancester_right(node_pointer __x) {
                node_pointer __y = __x->_parent;
                while (__y->_color != NIL && __x == __y->_right) {
                    __x = __y;
                    __y = __y->_parent;
                }
                return __y;
            }

            node_pointer
            _find_ancester_left(node_pointer __x) {
                node_pointer __y = __x->_parent;
                while (__y->_color != NIL && __x == __y->_left) {
                    __x = __y;
                    __y = __y->_parent;
                }
                return __y->_color != NIL ? __y : __x;
            }

        private :

            template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2> friend bool operator==(const const_set_iterator<T11, T12, _Iter1>&, const const_set_iterator<T21, T22, _Iter2>&);
            template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2> friend bool operator==(const set_iterator<T11, T12, _Iter1>&, const const_set_iterator<T21, T22, _Iter2>&);
            template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2> friend bool operator==(const const_set_iterator<T11, T12, _Iter1>&, const set_iterator<T21, T22, _Iter2>&);

            template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2> friend bool operator<(const const_set_iterator<T11, T12, _Iter1>&, const const_set_iterator<T21, T22, _Iter2>&);
            template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2> friend bool operator<(const set_iterator<T11, T12, _Iter1>&, const const_set_iterator<T21, T22, _Iter2>&);
            template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2> friend bool operator<(const const_set_iterator<T11, T12, _Iter1>&, const set_iterator<T21, T22, _Iter2>&);

            template<class, class, class, class> friend class rbt_tree;
			template<class, class, class, class> friend class map;
    };

    template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2>
    bool operator==(const set_iterator<T11, T12, _Iter1>& __x, const set_iterator<T21, T22, _Iter2>& __y) {
        return __x.base() == __y.base();
    }

    template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2>
    bool operator==(const const_set_iterator<T11, T12, _Iter1>& __x, const const_set_iterator<T21, T22, _Iter2>& __y) {
        return __x.base() == __y.base();
    }

    template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2>
    bool operator==(const set_iterator<T11, T12, _Iter1>& __x, const const_set_iterator<T21, T22, _Iter2>& __y) {
        return __x.base() == __y.base();
    }

    template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2>
    bool operator==(const const_set_iterator<T11, T12, _Iter1>& __x, const set_iterator<T21, T22, _Iter2>& __y) {
        return __x.base() == __y.base();
    }



    template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2>
    bool operator<(const set_iterator<T11, T12, _Iter1>& __x, const set_iterator<T21, T22, _Iter2>& __y) {
        return __x.base() < __y.base();
    }

    template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2>
    bool operator<(const const_set_iterator<T11, T12, _Iter1>& __x, const const_set_iterator<T21, T22, _Iter2>& __y) {
        return __x.base() < __y.base();
    }

    template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2>
    bool operator<(const set_iterator<T11, T12, _Iter1>& __x, const const_set_iterator<T21, T22, _Iter2>& __y) {
        return __x.base() < __y.base();
    }

    template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2>
    bool operator<(const const_set_iterator<T11, T12, _Iter1>& __x, const set_iterator<T21, T22, _Iter2>& __y) {
        return __x.base() < __y.base();
    }


    template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2>
    bool operator!=(const set_iterator<T11, T12, _Iter1>& __x, const set_iterator<T21, T22, _Iter2>& __y) {
        return !(__x == __y);
    }

    template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2>
    bool operator!=(const const_set_iterator<T11, T12, _Iter1>& __x, const const_set_iterator<T21, T22, _Iter2>& __y) {
        return !(__x == __y);
    }

    template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2>
    bool operator!=(const set_iterator<T11, T12, _Iter1>& __x, const const_set_iterator<T21, T22, _Iter2>& __y) {
        return !(__x == __y);
    }

    template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2>
    bool operator!=(const const_set_iterator<T11, T12, _Iter1>& __x, const set_iterator<T21, T22, _Iter2>& __y) {
        return !(__x == __y);
    }

    template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2>
    bool operator>(const set_iterator<T11, T12, _Iter1>& __x, const set_iterator<T21, T22, _Iter2>& __y) {
        return __y < __x;
    }

    template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2>
    bool operator>(const const_set_iterator<T11, T12, _Iter1>& __x, const const_set_iterator<T21, T22, _Iter2>& __y) {
        return __y < __x;
    }

    template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2>
    bool operator>(const set_iterator<T11, T12, _Iter1>& __x, const const_set_iterator<T21, T22, _Iter2>& __y) {
        return __y < __x;
    }

    template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2>
    bool operator>(const const_set_iterator<T11, T12, _Iter1>& __x, const set_iterator<T21, T22, _Iter2>& __y) {
        return __y < __x;
    }



    template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2>
    bool operator<=(const set_iterator<T11, T12, _Iter1>& __x, const set_iterator<T21, T22, _Iter2>& __y) {
        return !(__y < __x);
    }

    template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2>
    bool operator<=(const const_set_iterator<T11, T12, _Iter1>& __x, const const_set_iterator<T21, T22, _Iter2>& __y) {
        return !(__y < __x);
    }

    template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2>
    bool operator<=(const set_iterator<T11, T12, _Iter1>& __x, const const_set_iterator<T21, T22, _Iter2>& __y) {
        return !(__y < __x);
    }

    template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2>
    bool operator<=(const const_set_iterator<T11, T12, _Iter1>& __x, const set_iterator<T21, T22, _Iter2>& __y) {
        return !(__y < __x);
    }


    template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2>
    bool operator>=(const set_iterator<T11, T12, _Iter1>& __x, const set_iterator<T21, T22, _Iter2>& __y) {
        return !(__x < __y);
    }

    template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2>
    bool operator>=(const const_set_iterator<T11, T12, _Iter1>& __x, const const_set_iterator<T21, T22, _Iter2>& __y) {
        return !(__x < __y);
    }

    template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2>
    bool operator>=(const set_iterator<T11, T12, _Iter1>& __x, const const_set_iterator<T21, T22, _Iter2>& __y) {
        return !(__x < __y);
    }

    template <class T11, class T12, class T21, class T22, class _Iter1, class _Iter2>
    bool operator>=(const const_set_iterator<T11, T12, _Iter1>& __x, const set_iterator<T21, T22, _Iter2>& __y) {
        return !(__x < __y);
    }
}

#endif // __FT_CONTAINERS__SET_ITERATOR__
