#ifndef __FT_CONTAINERS_RBTREE_NODE_TYPE__
#define __FT_CONTAINERS_RBTREE_NODE_TYPE__

#include "pair.hpp"

namespace ft {

    enum RBT_node_type {
        RED,
        BLACK,
        NIL
    };
     
    template <class T1, class T2>
    class RBT_node {
        public :
            typedef ft::pair<const T1, T2>          value_type;
            typedef value_type*                     value_pointer;
            typedef RBT_node<T1, T2>                node_type;
            typedef RBT_node<T1, T2>*               node_pointer;
            typedef RBT_node<T1, T2>&               node_reference;
            typedef RBT_node_type                   node_color;

            node_color      _color;
            node_pointer    _parent;
            node_pointer    _left;
            node_pointer    _right;
            value_pointer   _value;

            RBT_node(T1 key, T2 value, node_pointer nil = NULL, node_color color = BLACK)
                : _color(color), _parent(nil), _left(nil), _right(nil), _value(new value_type(key, value)) {}

            RBT_node(node_reference __x) {
                *this = __x;
            }

            node_reference operator=(node_reference __x) {
                if (this != &__x) {
                    this->_color = __x._color;
                    this->_parent = __x._parent;
                    this->_left = __x._left;
                    this->_right = __x._right;
                    this->_value = new value_type(__x._value->first, __x._value->second);
                }
                return *this;
            }

            ~RBT_node() {
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
                if (this->_parent == this->_grandparent()->_left)
                    return this->_grandparent()->_right;
                else
                    return this->_grandparent()->_left;
            }

            node_pointer
            _sibling() const {
                if (this == this->_parent->_left)
                    return this->_parent->_right;
                else
                    return this->_parent->_left;
            }

            bool
            inline is_left() const {
                return this == this->_parent->_left;
            }

            bool
            inline is_right() const {
                return this == this->_parent->_right;
            }

            bool
            inline is_red_node() const {
                return this->_color == RED;
            }

            bool
            inline is_black_node() const {
                return this->_color == BLACK;
            }

            bool
            inline is_nil_node() const {
                return this->_color == NIL;
            }

            void
            inline change_color(node_color color) {
                this->_color = color;
            }
    };
}


#endif // __FT_CONTAINERS_RBTREE_NODE_TYPE__
