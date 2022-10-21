#ifndef __FT_CONTAINERS__MAP_ITERATOR__
#define __FT_CONTAINERS__MAP_ITERATOR__

#include "rbt_node.hpp"
#include "iterator_base.hpp"


namespace ft {
    template <class T1, class T2, class _Iter>
    class map_iterator {
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
            map_iterator(node_pointer __p = NULL) : _nptr(__p) {};

            template <class _U>
            map_iterator(const map_iterator<T1, T2, _U>& __x) : _nptr(__x.base()) {};

            map_iterator&
            operator=(const map_iterator& __x) {
                if (this != &__x) {
                    this->_nptr = __x.base();
                }
                return *this;
            }

            ~map_iterator() {};

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

            map_iterator&
            operator++() {
                this->_nptr = next(this->_nptr);
                return *this;
            }

            map_iterator
            operator++(int) {
                map_iterator __tmp(*this);
                this->_nptr = next(this->_nptr);
                return __tmp;
            }

            map_iterator&
            operator--() {
                this->_nptr = prev(this->_nptr);
                return *this;
            }

            map_iterator
            operator--(int) {
                map_iterator __tmp(*this);
                this->_nptr = prev(this->_nptr);
                return __tmp;
            }

            bool
            operator==(const map_iterator& __x) const {
                return this->_nptr == __x.base();
            }

            bool
            operator!=(const map_iterator& __x) const {
                return this->_nptr != __x.base();
            }

        private :

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
    };
}

#endif // __FT_CONTAINERS__MAP_ITERATOR__
