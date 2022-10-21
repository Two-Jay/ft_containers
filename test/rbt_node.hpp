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
            typedef ft::pair<T1, T2> value_type;

            rbt_node_type   _color;
            rbt_node*       _parent;
            rbt_node*       _left;
            rbt_node*       _right;
            value_type*     _value;

            rbt_node(T1 key, T2 value, rbt_node* nil = NULL, rbt_node_type color = BLACK)
                : _color(color), _parent(nil), _left(nil), _right(nil), _value(new value_type(key, value)) {}

            rbt_node(rbt_node& __x) {
                *this = __x;
            }

            rbt_node&
            operator=(rbt_node& __x) {
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

            rbt_node*
            _grandparent() const {
                return this->_parent->_parent;
            }

            rbt_node*
            _uncle() const {
                return (this->_parent->is_left()) ? this->_grandparent()->_right : this->_grandparent()->_left;
            }

            rbt_node*
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
    };
}


#endif // __FT_CONTAINERS_RBTREE_NODE_TYPE__
