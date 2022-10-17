#ifndef __FT_CONTAINERS_RBTREE_ITERATOR_TYPE__
#define __FT_CONTAINERS_RBTREE_ITERATOR_TYPE__

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
    class RBT_node {
        public :
            typedef color_Node_RB_tree      color_type;
            typedef RBT_node<_Value>       node_type;
            typedef RBT_node<_Value>*      node_pointer;
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
            typedef RBT_node<_Value>       node_type;
            typedef RBT_node<_Value>*      node_pointer;
            
            void
            inline rebalance(node_pointer __x, node_pointer __root) {
                __x->_color = RED;
                while (!insert_case1(__x, __root) && !insert_case2(__x)) {
                    node_pointer __u = __x->uncle();
                    if (__u && __u->_color == RED) {
                        insert_case3(__x, __u);
                    }
                    bool isRightChild = __x == __x->_parent->_right_child ? true : false;
                    insert_case4(__x, isRightChild);
                    insert_case5(__x, root, isRightChild);
                }
                __root->_color = BLACK;
            }

        private :
            
            bool
            insert_case1(node_pointer __x, node_pointer __root) {
                return (__x == __root);
            }

            bool
            insert_case2(node_pointer __x) {
                return (__x->_parent->_color == BLACK);
            }

            void
            inline insert_case3(node_pointer __x, node_pointer __u) {
                __x->_parent->_color = BLACK;
                __u->_color = BLACK;
                __x->grandparent()->_color = RED;
                __x = __x->grandparent();
            }

            void
            insert_case4(node_pointer __x, bool isXnodeRightChild) {
                node_pointer __g = __x->grandparent();

                if (isXnodeRightChild && __x->_parent == __g->_left_child) {
                    _rotate_left(__x->_parent);
                    __x = __x->_left_child;
                } else if (!isXnodeRightChild && __x->_parent == __g->_right_child) {
                    _rotate_right(__x->_parent);
                    __x = __x->_right_child;
                }
            }

            void
            insert_case5(node_pointer __x, node_pointer __root, bool isXnodeRightChild) {
                node_pointer __g = __x->grandparent();
                
                __x->_parent->_color = BLACK;
                __g->_color = RED;
                if (isXnodeRightChild) {
                    _rotate_left(__g, __root);
                } else {
                    _rotate_right(__g, __root);
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

    };


    template <class _Value, class _Ref, class _Ptr>
    class _RBT_iterator {
        public :
            typedef _Value                                  value_type;
            typedef _Ref                                    reference;
            typedef _Ptr                                    pointer;
            typedef std::ptrdiff_t                          difference_type;
            typedef ft::bidirectional_iterator_tag          iterator_category;


            typedef RBT_node<_Value>*                                      node_pointer;
            typedef ft::_RBT_iterator<_Value, _Value&, _Value*>             iterator;
            typedef ft::_RBT_iterator<_Value, const _Value&, const _Value*> const_iterator;
            typedef ft::_RBT_iterator<_Value, _Ref, _Ptr>                   iterator_self;
            typedef ft::RBT_node<_Value>*                                  link_type;

            node_pointer   _node;

        public :
            _RBT_iterator() {};
            _RBT_iterator(link_type __x) : _node(__x) {};
            _RBT_iterator(const iterator& __x) : _node(__x._node) {};

            reference operator*() const { return this->_node->_data(); }
            pointer operator->() const { return &(operator*()); }

            iterator_self&
            operator++() {
                _increment();
                return *this;
            }

            iterator_self
            operator++(int) {
                iterator_self __tmp = *this;
                _increment();
                return __tmp;
            }

            iterator_self&
            operator--() {
                _decrement();
                return *this;
            }

            iterator_self
            operator--(int) {
                iterator_self __tmp = *this;
                _decrement();
                return __tmp;
            }

            void
            _increment() {
                if (_node->_right_child != NULL) {
                    _node = _node->_right_child;
                    _node = _minimum_from(_node);
                } else { // Find ancester 
                    _node = _find_ancester(RIGHT);
                }
            }

            void
            _decrement() {
                if (_node->_color == RED && _node->_parent->_parent == _node)
                    _node = _node->_right_child;
                else if (_node->_left_child != NULL) {
                    node_pointer __y = _node->_left_child;
                    __y = _maximum_from(__y);
                    _node = __y;
                }
                else { // Find ancester
                    _node = _find_ancester(LEFT);
                }
            }

        private :
            node_pointer
            _minimum_from(node_pointer __x) {
                while (__x->_left_child != NULL)
                    __x = __x->_left_child;
                return __x;
            }

            node_pointer
            _maximum_from(node_pointer __x) {
                while (__x->_right_child != NULL)
                    __x = __x->_right_child;
                return __x;
            }

            node_pointer
            _find_ancester(rotate_direction __dir) {
                return __dir == LEFT ? _find_ancester_aux_left() : _find_ancester_aux_right();
            }

            node_pointer
            _find_ancester_aux_left() {
                node_pointer __x = this->_node;
                node_pointer __y = __x->_parent;
                while (__x == __y->_left_child) {
                    __x = __y;
                    __y = __y->_parent;
                }
                return __y;
            }

            node_pointer
            _find_ancester_aux_right() {
                node_pointer __x = this->_node;
                node_pointer __y = __x->_parent;
                while (__x == __y->_right_child) {
                    __x = __y;
                    __y = __y->_parent;
                }
                return __x->_right_child != __y ? __y->_parent : __y;
            }
    };


    #define RBTREEITER_OPE_MACRO(OP) \
        __x.node OP __y.node;

    template <class _Value, class _Ref, class _Ptr>
    inline bool
    operator==(const _RBT_iterator<_Value, _Ref, _Ptr>& __x,
               const _RBT_iterator<_Value, _Ref, _Ptr>& __y) {
        return RBTREEITER_OPE_MACRO(==)
    }

    template <class _Value, class _Ref, class _Ptr>
    inline bool
    operator==(const _RBT_iterator<_Value, const _Value&, const _Value*>& __x,
               const _RBT_iterator<_Value, _Value&, _Value*>& __y) {
        return RBTREEITER_OPE_MACRO(==)
    }

    template <class _Value, class _Ref, class _Ptr>
    inline bool
    operator==(const _RBT_iterator<_Value, _Value&, _Value*>& __x,
               const _RBT_iterator<_Value, const _Value&, const _Value*>& __y) {
        return RBTREEITER_OPE_MACRO(==)
    }

    template <class _Value, class _Ref, class _Ptr>
    inline bool operator!=(const _RBT_iterator<_Value, _Ref, _Ptr>& __x,
                const _RBT_iterator<_Value, _Ref, _Ptr>& __y) {
        return RBTREEITER_OPE_MACRO(!=)
    }

    template <class _Value>
    inline bool operator!=(const _RBT_iterator<_Value, const _Value&, const _Value*>& __x,
                const _RBT_iterator<_Value, _Value&, _Value*>& __y) {
        return RBTREEITER_OPE_MACRO(!=)
    }

    template <class _Value>
    inline bool operator!=(const _RBT_iterator<_Value, _Value&, _Value*>& __x,
                const _RBT_iterator<_Value, const _Value&, const _Value*>& __y) {
        return RBTREEITER_OPE_MACRO(!=)
    }

    #undef RBTREEITER_OPE_MACRO
}


#endif // __FT_CONTAINERS_RBTREE_ITERATOR_TYPE__
