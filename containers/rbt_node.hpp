#ifndef __FT_CONTAINERS_RBTREE_NODE_TYPE__
#define __FT_CONTAINERS_RBTREE_NODE_TYPE__

#include "pair.hpp"
#include <cstdio>

namespace ft {


    enum rbt_node_type {
        NIL,
        RED,
        BLACK
    };
     
    template <class T1, class T2>
    class rbt_node {
        public :
            typedef ft::pair<const T1, T2>  value_type;
            typedef ft::rbt_node<T1, T2>*   node_pointer;
            typedef ft::rbt_node<T1, T2>&   node_reference;

            rbt_node_type   _color;
            node_pointer    _parent;
            node_pointer    _left;
            node_pointer    _right;
            value_type*     _value;

            rbt_node(T1 key, T2 value, node_pointer nil = NULL, rbt_node_type color = BLACK)
                : _color(color), _parent(nil), _left(nil), _right(nil), _value(new value_type(key, value)) {}

            rbt_node(node_reference __x) {
                *this = __x;
            }

            node_reference
            operator=(node_reference __x) {
                if (this != &__x) {
                    this->_color = __x._color;
                    this->_parent = __x._parent;
                    this->_left = __x._left;
                    this->_right = __x._right;
                    this->_value = new value_type(__x._value->first, __x._value->second);
                }
                return *this;
            }

            ~rbt_node() {
                if (this->_value)
                    delete this->_value;
                    this->_value = NULL;
            }

            node_pointer
            _grandparent() const {
                return this->_parent->_parent;
            }

            node_pointer
            _uncle() const {
                return (this->_parent->is_left()) ? this->_grandparent()->_right : this->_grandparent()->_left;
            }

            node_pointer
            _sibling() const {
                return (this->is_left()) ? this->_parent->_right : this->_parent->_left;
            }

            bool
            inline is_left() const {
                return this == this->_parent->_left;
            }

            bool
            inline is_right() const {
                return this == this->_parent->_right;
            }

            void
            inline change_color(rbt_node_type color) {
                this->_color = color;
            }

            bool
            inline _is_(node_pointer __p) {
                return this == __p;
            }

            bool
            inline _is_not_(node_pointer __p) {
                return this != __p;
            }
    };
}


#endif // __FT_CONTAINERS_RBTREE_NODE_TYPE__
