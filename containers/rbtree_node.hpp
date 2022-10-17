#ifndef __FT_CONTAINERS_RBTREE_NODE_TYPE__
#define __FT_CONTAINERS_RBTREE_NODE_TYPE__

#include "./iterators.hpp"

namespace ft {

    enum color_Node_RB_tree {
        RED,
        BLACK
    };

    enum rotate_direction {
        LEFT,
        RIGHT
    };

    template <class _Value> 
    class _RBT_node {
        public :
            typedef color_Node_RB_tree      color_type;
            typedef _RBT_node<_Value>       node_type;
            typedef _RBT_node<_Value>*      node_pointer;
            typedef _Value                  value_type;
            typedef _Value*                 pointer;
            typedef _Value&                 reference;


            color_type          _color;
            node_pointer        _parent;
            node_pointer        _left_child;
            node_pointer        _right_child;

            value_type          _data;


            reference
            inline data() {
                return _data;
            }

            node_pointer
            inline left_child() {
                return this->_left_child;
            }

            node_pointer
            inline right_child() {
                return this->_right_child;
            }

            node_pointer
            inline parent() {
                return this->_parent;
            }

            node_pointer
            inline grandparent() {
                return this->_parent->_parent;
            }

            node_pointer
            inline uncle() {
                if (this->_parent == this->_grandparent()->_left_child)
                    return this->_grandparent()->_right_child;
                else
                    return this->_grandparent()->_left_child;
            }
    };

    template <class _Value>
    class _RBT_rebalancer {
        public :
            typedef _RBT_node<_Value>       node_type;
            typedef _RBT_node<_Value>*      node_pointer;
            typedef _Value                  value_type;
            typedef _Value*                 pointer;
            typedef _Value&                 reference;

            _RBT_rebalancer() {};

            void rotate(node_pointer __x, node_pointer __root, rotate_direction __dir) {
                switch (__dir) {
                    case LEFT:
                        _RB_tree_rotate_left(__x, __root);
                        break;
                    case RIGHT:
                        _RB_tree_rotate_right(__x, __root);
                        break;
                    default:
                        break;
                }
            }

            void
            inline _rotate_left(node_pointer __x, node_pointer __root) {
                node_pointer __y = __x->_right_child;
                
                __x->_right_child = __y->_left_child;
                if (__y->_left_child != NULL)
                    __y->_left_child->_parent = __x;
                __y->_parent = __x->_parent;
                
                if (__x == __root)
                    __root = __y;
                else if (__x == __x->_parent->_left_child)
                    __x->_parent->_left_child = __y;
                else
                    __x->_parent->_right_child = __y;
                __y->_left_child = __x;
                __x->_parent = __y;
            }

            void
            inline _rotate_right(node_pointer __x, node_pointer __root) {
                node_pointer __y = __x->_left_child;

                __x->_left_child = __y->_right_child;
                if (__y->_right_child != NULL)
                    __y->_right_child->_parent = __x;
                __y->_parent = __x->_parent;

                if (__x == __root)
                    __root = __y;
                else if (__x == __x->_parent->_right_child)
                    __x->_parent->_right_child = __y;
                else
                    __x->_parent->_left_child = __y;
                __y->_right_child = __x;
                __x->_parent = __y;
            }

            void
            inline rebalance(node_pointer __x, node_pointer __root) {
                __x->_color = RED;
                while (__x != __root && __x->_parent->_color == RED) {
                    if (__x->_parent == __x->_parent->_parent->_left_child) {
                        node_pointer __y = __x->_parent->_parent->_right_child;

                        if (__y && __y->_color == RED) {
                            __x->_parent->_color = BLACK;
                            __y->_color = BLACK;
                            __x->grandparent()->_color = RED;
                            __x = __x->grandparent();
                        } else {
                            if (__x == __x->_parent->_right_child) {
                                __x = __x->_parent;
                                rotate(__x, __root, LEFT);
                            }
                            __x->_parent->_color = BLACK;
                            __x->grandparent()->_color = RED;
                            rotate(__x->grandparent(), __root, RIGHT);
                        }
                    } else {
                        node_pointer __y = __x->_parent->_parent->_left_child;
                        
                        if (__y && __y->_color == RED) {
                            __x->_parent->_color = BLACK;
                            __y->_color = BLACK;
                            __x->grandparent()->_color = RED;
                            __x = __x->grandparent();
                        } else {
                            if (__x == __x->_parent->_left_child) {
                                __x = __x->_parent;
                                rotate(__x, __root, RIGHT);
                            }
                            __x->_parent->_color = BLACK;
                            __x->grandparent()->_color = RED;
                            rotate(__x->grandparent(), __root, LEFT);
                        }
                    }
                }
                __root->_color = BLACK;
            }

            inline _Rb_tree_node_base*
            _Rb_tree_rebalance_for_erase(_Rb_tree_node_base* __z,
                                        _Rb_tree_node_base*& __root,
                                        _Rb_tree_node_base*& __leftmost,
                                        _Rb_tree_node_base*& __rightmost)
            {
            _Rb_tree_node_base* __y = __z;
            _Rb_tree_node_base* __x = 0;
            _Rb_tree_node_base* __x_parent = 0;
            if (__y->_M_left == 0)     // __z has at most one non-null child. y == z.
                __x = __y->_M_right;     // __x might be null.
            else
                if (__y->_M_right == 0)  // __z has exactly one non-null child. y == z.
                __x = __y->_M_left;    // __x is not null.
                else {                   // __z has two non-null children.  Set __y to
                __y = __y->_M_right;   //   __z's successor.  __x might be null.
                while (__y->_M_left != 0)
                    __y = __y->_M_left;
                __x = __y->_M_right;
                }
            if (__y != __z) {          // relink y in place of z.  y is z's successor
                __z->_M_left->_M_parent = __y; 
                __y->_M_left = __z->_M_left;
                if (__y != __z->_M_right) {
                __x_parent = __y->_M_parent;
                if (__x) __x->_M_parent = __y->_M_parent;
                __y->_M_parent->_M_left = __x;      // __y must be a child of _M_left
                __y->_M_right = __z->_M_right;
                __z->_M_right->_M_parent = __y;
                }
                else
                __x_parent = __y;  
                if (__root == __z)
                __root = __y;
                else if (__z->_M_parent->_M_left == __z)
                __z->_M_parent->_M_left = __y;
                else 
                __z->_M_parent->_M_right = __y;
                __y->_M_parent = __z->_M_parent;
                std::swap(__y->_M_color, __z->_M_color);
                __y = __z;
                // __y now points to node to be actually deleted
            }
            else {                        // __y == __z
                __x_parent = __y->_M_parent;
                if (__x) __x->_M_parent = __y->_M_parent;   
                if (__root == __z)
                __root = __x;
                else 
                if (__z->_M_parent->_M_left == __z)
                    __z->_M_parent->_M_left = __x;
                else
                    __z->_M_parent->_M_right = __x;
                if (__leftmost == __z) 
                if (__z->_M_right == 0)        // __z->_M_left must be null also
                    __leftmost = __z->_M_parent;
                // makes __leftmost == _M_header if __z == __root
                else
                    __leftmost = _Rb_tree_node_base::_S_minimum(__x);
                if (__rightmost == __z)  
                if (__z->_M_left == 0)         // __z->_M_right must be null also
                    __rightmost = __z->_M_parent;  
                // makes __rightmost == _M_header if __z == __root
                else                      // __x == __z->_M_left
                    __rightmost = _Rb_tree_node_base::_S_maximum(__x);
            }
            if (__y->_M_color != _S_rb_tree_red) { 
                while (__x != __root && (__x == 0 || __x->_M_color == _S_rb_tree_black))
                if (__x == __x_parent->_M_left) {
                    _Rb_tree_node_base* __w = __x_parent->_M_right;
                    if (__w->_M_color == _S_rb_tree_red) {
                    __w->_M_color = _S_rb_tree_black;
                    __x_parent->_M_color = _S_rb_tree_red;
                    _Rb_tree_rotate_left(__x_parent, __root);
                    __w = __x_parent->_M_right;
                    }
                    if ((__w->_M_left == 0 || 
                        __w->_M_left->_M_color == _S_rb_tree_black) &&
                        (__w->_M_right == 0 || 
                        __w->_M_right->_M_color == _S_rb_tree_black)) {
                    __w->_M_color = _S_rb_tree_red;
                    __x = __x_parent;
                    __x_parent = __x_parent->_M_parent;
                    } else {
                    if (__w->_M_right == 0 || 
                        __w->_M_right->_M_color == _S_rb_tree_black) {
                        if (__w->_M_left) __w->_M_left->_M_color = _S_rb_tree_black;
                        __w->_M_color = _S_rb_tree_red;
                        _Rb_tree_rotate_right(__w, __root);
                        __w = __x_parent->_M_right;
                    }
                    __w->_M_color = __x_parent->_M_color;
                    __x_parent->_M_color = _S_rb_tree_black;
                    if (__w->_M_right) __w->_M_right->_M_color = _S_rb_tree_black;
                    _Rb_tree_rotate_left(__x_parent, __root);
                    break;
                    }
                } else {                  // same as above, with _M_right <-> _M_left.
                    _Rb_tree_node_base* __w = __x_parent->_M_left;
                    if (__w->_M_color == _S_rb_tree_red) {
                    __w->_M_color = _S_rb_tree_black;
                    __x_parent->_M_color = _S_rb_tree_red;
                    _Rb_tree_rotate_right(__x_parent, __root);
                    __w = __x_parent->_M_left;
                    }
                    if ((__w->_M_right == 0 || 
                        __w->_M_right->_M_color == _S_rb_tree_black) &&
                        (__w->_M_left == 0 || 
                        __w->_M_left->_M_color == _S_rb_tree_black)) {
                    __w->_M_color = _S_rb_tree_red;
                    __x = __x_parent;
                    __x_parent = __x_parent->_M_parent;
                    } else {
                    if (__w->_M_left == 0 || 
                        __w->_M_left->_M_color == _S_rb_tree_black) {
                        if (__w->_M_right) __w->_M_right->_M_color = _S_rb_tree_black;
                        __w->_M_color = _S_rb_tree_red;
                        _Rb_tree_rotate_left(__w, __root);
                        __w = __x_parent->_M_left;
                    }
                    __w->_M_color = __x_parent->_M_color;
                    __x_parent->_M_color = _S_rb_tree_black;
                    if (__w->_M_left) __w->_M_left->_M_color = _S_rb_tree_black;
                    _Rb_tree_rotate_right(__x_parent, __root);
                    break;
                    }
                }
                if (__x) __x->_M_color = _S_rb_tree_black;
            }
            return __y;
            }
    };


}


#endif // __FT_CONTAINERS_RBTREE_NODE_TYPE__
