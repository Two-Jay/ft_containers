#ifndef __FT_CONTAINERS__RB_TREE__
#define __FT_CONTAINERS__RB_TREE__

#include "./pair.hpp"
#include "./iterators.hpp"
#include "./utils.hpp"
#include <memory>

#define ERROR_ALLOCATE_MEMORY 134

namespace ft {    
    template <class _Value, class _Alloc = std::allocator<_Value> >
    class _RBT_base {
        public :
            typedef _Value                          value_type;
            typedef _Value*                         value_pointer;
            typedef _Value&                         value_reference;
            typedef size_t                          size_type;
            typedef _RBT_node<_Value>               node_type;
            typedef _RBT_node<_Value>*              node_pointer;
            typedef color_Node_RB_tree              color_type;
            typedef _Alloc                          allocator_type;

        protected :
            allocator_type                      _allocator;
            node_pointer                        _header;

        public :
            _RBT_base() {};

            explicit _RBT_base(const allocator_type& __a) : _allocator(__a), _header(_get_node()) {};

            allocator_type
            inline get_allocator(void) {
                return this->_allocator;
            };

            size_type
            inline get_maxsize(void) {
                return this->_allocator.max_size();
            };

            node_pointer
            inline get_header(void) {
                return this->_header;
            };

            node_pointer
            _get_node(void) {
                return this->_allocator.allocate(1);
            };

            void
            _put_node(node_pointer __p) {
                this->_allocator.deallocate(__p, 1);
            };

            node_pointer
            inline create_node(value_reference __value) {
                node_pointer __node = _get_node();
                try {
                    this->_allocator.construct(&__node->_data, __value);
                } catch (...) {
                    this->_put_node(__node);
                    exit (ERROR_ALLOCATE_MEMORY);
                }
                __node->_color = RED;
                __node->_parent = 0;
                __node->_left_child = 0;
                __node->_right_child = 0;
                return __node;
            };

            void
            inline destroy_node(node_pointer __node) {
                this->_allocator.destroy(&__node->_data);
                this->_put_node(__node);
            };

            node_pointer
            inline clone_node(node_pointer __node) {
                node_pointer __new_node = this->create_node(__node->_data);
                __new_node->_color = __node->_color;
                return __new_node;
            };
    };

    template <class _Key, class _Value, class _Compare, class _Alloc = std::allocator<_Value> >
    class RB_tree : public _RBT_base<_Value, _Alloc> {
        public :
            typedef _Key                            key_type;
            typedef _Value                          value_type;
            typedef _Value*                         value_pointer;
            typedef const _Value*                   const_value_pointer;
            typedef _Value&                         value_reference;
            typedef const _Value&                   const_value_reference;
            typedef _Alloc                          allocator_type;
            typedef std::size_t                     size_type;
            typedef std::ptrdiff_t                  difference_type;
            
            typedef RB_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>                        self_type;
            typedef ft::_RBT_iterator<value_type, value_reference, value_pointer>               iterator;
            typedef ft::_RBT_iterator<value_type, const_value_reference, const_value_pointer>   const_iterator;
            typedef ft::reverse_iterator<iterator>                                              reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>                                        const_reverse_iterator;

            typedef _Value*                         pointer;
            typedef const _Value*                   const_pointer;
            typedef _Value&                         reference;
            typedef const _Value&                   const_reference;

        protected :
            typedef _RBT_base<_Value, _Alloc>               _Base;
            typedef _RBT_node<_Value>                       node_type;
            typedef _RBT_rebalancer<_Value>                 rebalancer_type;
            typedef node_type*                              node_pointer;
            typedef node_type&                              node_reference;
            typedef color_Node_RB_tree                      color_type;

            _RBT_rebalancer<_Value>                         _rebalancer;
            _Compare                                        _key_compare;
            size_type                                       _node_count;



        public :
            RB_tree()
                : _Base(allocator_type()), _rebalancer(rebalancer_type()), _key_compare(), _node_count(0)
            {
                this->_RBT_empty_init();
            };

            RB_tree(const _Compare& __comp)
                : _Base(allocator_type()), _rebalancer(rebalancer_type()), _key_compare(__comp), _node_count(0)
            {
                this->_RBT_empty_init();
            };

            RB_tree(const _Compare& __comp, const allocator_type& __a = allocator_type())
                : _Base(__a), _rebalancer(rebalancer_type()), _key_compare(__comp), _node_count(0)
            {
                this->_RBT_empty_init();
            };

            RB_tree(const RB_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>& __x)
                : _Base(__x.get_allocator()), _rebalancer(_RBT_rebalancer<_Value>()), _key_compare(__x._key_compare), _node_count(0)
            {
                if (__x._root() == NULL)
                    this->_RBT_empty_init();
                else {
                    this->_copy(__x._root(), this->_header);
                    this->_leftmost() = this->_minimum(this->_root());
                    this->_rightmost() = this->_maximum(this->_root());
                    this->_node_count = __x._node_count;
                }
            }

            ~RB_tree() {
                this->clear();
            };

            allocator_type
            get_allocator(void) const {
                return this->_allocator;
            };

            _Compare
            key_comp(void) {
                return _key_compare;
            };

            iterator
            begin(void) {
                return iterator(this->_leftmost());
            };

            const_iterator
            begin(void) const {
                return const_iterator(this->_leftmost());
            };

            iterator
            end(void) {
                return iterator(this->_header);
            };

            const_iterator
            end(void) const {
                return const_iterator(this->_header);
            };

            reverse_iterator
            rbegin(void) {
                return reverse_iterator(this->end());
            };

            const_reverse_iterator
            rbegin(void) const {
                return const_reverse_iterator(this->end());
            };

            reverse_iterator
            rend(void) {
                return reverse_iterator(this->begin());
            };

            const_reverse_iterator
            rend(void) const {
                return const_reverse_iterator(this->begin());
            };

            bool
            empty(void) const {
                return this->_node_count == 0;
            };

            size_type
            size(void) const {
                return this->_node_count;
            };

            size_type
            max_size(void) const {
                return this->_allocator.max_size();
            };

            void swap(self_type& __x) {
                std::swap(this->_header, __x._header);
                std::swap(this->_node_count, __x._node_count);
                std::swap(this->_key_compare, __x._key_compare);
            };

            ft::pair<iterator, bool>
            insert(value_type& __value) {
                node_pointer __y = this->_header;
                node_pointer __x = this->_root();
                bool __comp = true;
                while (__x != NULL) {
                    __y = __x;
                    __comp = this->_key_compare(_KeyOfValue()(__value), _KeyOfValue()(__y));
                    __x = __comp ? __x->_left_child : __x->_right_child;
                }
                iterator __j = iterator(__y);
                if (__comp) {
                    if (__j == begin()) {
                        return ft::pair<iterator, bool>(this->_insert_aux(__x, __y, __value), true);
                    } else {
                        --__j;
                    }
                }
                if (this->_key_compare(_KeyOfValue()(__j._node), _KeyOfValue()(__value)))
                    return ft::pair<iterator, bool>(this->_insert_aux(__x, __y, __value), true);
                return ft::pair<iterator, bool>(__j, false);
            }

            iterator
            insert(iterator __pos, value_type& __x) {
                if (__pos._node == this->_header->_left_child) {
                    if (!this->empty() && _key_compare(_KeyOfValue()(__x), _KeyOfValue()(__pos._node)))
                        return this->_insert_aux(__x, __pos._node, __pos._node);
                    else
                        return this->insert(__x).first;
                } else if (__pos._node == this->_header) {
                    if (_key_compare(_KeyOfValue()(__pos._node->_right_child), _KeyOfValue()(__x)))
                        return this->_insert_aux(__x, __pos._node, __pos._node);
                    else
                        return this->insert(__x).first;
                } else {
                    iterator __before = __pos;
                    --__before;
                    if (_key_compare(_KeyOfValue()(__before._node), _KeyOfValue()(__x)) &&
                        _key_compare(_KeyOfValue()(__x), _KeyOfValue()(__pos._node)))
                        if (__pos._node->_left_child == NULL)
                            return this->_insert_aux(__x, __pos._node, __pos._node);
                        else
                            return this->_insert_aux(__x, __pos._node->_left_child, __pos._node);
                    else
                        return this->insert(__x).first;
                }
            }

            void
            erase(node_pointer __x) {
                while (__x != NULL) {
                    this->_erase(__x->_right_child);
                    node_pointer __y = __x->_left_child;
                    this->destroy_node(__x);
                    __x = __y;
                }
            }

            size_type
            erase(const key_type& __x) {
                ft::pair<iterator, iterator> __p = this->equal_range(__x);
                size_type __n = ft::distance(__p.first, __p.second);
                this->erase(__p.first, __p.second);
                return __n;
            };

            void
            erase(iterator __first, iterator __last) {
                if (__first == begin() && __last == end())
                    this->clear();
                else
                    while (__first != __last) erase(__first++);
            }

            void
            erase(const key_type* __first, const key_type* __last) {
                while (__first != __last) erase(*__first++);
            }

            void
            clear() {
                if (this->_node_count != 0) {
                    this->erase(this->_root());
                    this->_leftmost() = this->_header;
                    this->_root() = NULL;
                    this->_rightmost() = this->_header;
                    this->_node_count = 0;
                }
            };

            iterator
            lower_bound(const _Key& __k)
            {
                node_pointer __y = this->_header;
                node_pointer __x = this->_root();

                while (__x != 0) 
                    if (!_key_compare(_key(__x), __k))
                        __y = __x, __x = _left(__x);
                    else
                        __x = _right(__x);
                return iterator(__y);
            }

            const_iterator
            lower_bound(const _Key& __k) const
            {
                node_pointer __y = this->_header;
                node_pointer __x = this->_root();

                while (__x != 0) 
                    if (!_key_compare(_key(__x), __k))
                        __y = __x, __x = _left(__x);
                    else
                        __x = _right(__x);
                return const_iterator(__y);
            }

            iterator
            upper_bound(const _Key& __k)
            {
                node_pointer __y = this->_header;
                node_pointer __x = this->_root();

                while (__x != 0) 
                    if (_key_compare(__k, _key(__x)))
                    __y = __x, __x = _left(__x);
                    else
                    __x = _right(__x);

                return iterator(__y);
            }

            const_iterator
            upper_bound(const _Key& __k) const
            {
                node_pointer __y = this->_header;
                node_pointer __x = this->_root();

                while (__x != 0) 
                    if (_key_compare(__k, _key(__x)))
                    __y = __x, __x = _left(__x);
                    else
                    __x = _right(__x);

                return const_iterator(__y);
            }

            ft::pair<iterator, iterator>
            equal_range(const _Key& __k)
            {
                return pair<iterator, iterator>(lower_bound(__k), upper_bound(__k));
            }


            ft::pair<const_iterator, const_iterator>
            equal_range(const _Key& __k) const 
            {
                return pair<const_iterator, const_iterator>(lower_bound(__k), upper_bound(__k));
            }


        protected :
            node_pointer&
            _root(void) const {
                return this->_header->_parent;
            };

            node_pointer&
            _leftmost(void) const {
                return this->_header->_left_child;
            };

            node_pointer&
            _rightmost(void) const {
                return this->_header->_right_child;
            };

            node_pointer&
            _left(node_pointer __x) {
                return __x->_left_child;
            };

            node_pointer&
            _right(node_pointer __x) {
                return __x->_right_child;
            };

            node_pointer&
            _parent(node_pointer __x) {
                return __x->_parent;
            };

            value_reference
            _value(node_pointer __x) {
                return __x->_data;
            };

            color_type&
            _color(node_pointer __x) {
                return __x->_color;
            };

            node_pointer
            _minimum(node_pointer __x) {
                while (__x->_left_child != NULL)
                    __x = __x->_left_child;
                return __x;
            }

            node_pointer
            _maximum(node_pointer __x) {
                while (__x->_right_child != NULL)
                    __x = __x->_right_child;
                return __x;
            }

        private :
            iterator
            _insert_aux(node_pointer __xptr, node_pointer __yptr, value_type& __v) {
                node_pointer __x = __xptr;
                node_pointer __y = __yptr;
                node_pointer __z;

                if (__y == this->_header || __x != NULL || this->_key_compare(_KeyOfValue()(__v), _KeyOfValue()(__y))) {
                    __z = this->create_node(__v);
                    __y->_left_child = __z;
                    if (__y == this->_header) {
                        this->_root() = __z;
                        this->_rightmost() = __z;
                    } else if (__y == this->_leftmost()) {
                        this->_leftmost() = __z;
                    }
                } else {
                    __z = this->create_node(__v);
                    __y->_right_child = __z;
                    if (__y == this->_rightmost())
                        this->_rightmost() = __z;
                }
                _parent(__z) = __y;
                _left(__z) = NULL;
                _right(__z) = NULL;
                this->_rebalancer->rebalance(__z, this->_header->_parent);
                ++this->_node_count;
                return iterator(__z);
            }

            node_pointer
            _copy(node_pointer __x, node_pointer __p) {
                node_pointer __top = this->clone_node(__x);
                __top->_parent = __p;

                try {
                    if (__x->_right_child)
                        __top->_right_child = this->_copy(__x->_right_child, __top);
                    __p = __top;
                    __x = __x->_left_child;

                    while (__x != NULL) {
                        node_pointer __y = this->clone_node(__x);
                        __p->_left_child = __y;
                        __y->_parent = __p;
                        if (__x->_right_child)
                            __y->_right_child = this->_copy(__x->_right_child, __y);
                        __p = __y;
                        __x = __x->_left_child;
                    }
                }
                catch (...) {
                    this->_erase(__top);
                    throw;
                }
            }

            void
            _RBT_empty_init() {
                this->_color(this->_header) = BLACK;
                this->_root() = NULL;
                this->_leftmost() = this->_header;
                this->_rightmost() = this->_header;
            }

            iterator
            _insert_aux(node_pointer __x, node_pointer __p, const value_type& __v) {
                return iterator(this->_insert_aux(__x, __p, __v));    
            }
    };

    template <class _Key, class _Value, class _KeyOfValue, 
            class _Compare, class _Alloc>
    inline bool 
    operator==(const RB_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
            const RB_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y)
    {
        return __x.size() == __y.size() && ft::equal(__x.begin(), __x.end(), __y.begin());
    }

    template <class _Key, class _Value, class _KeyOfValue, 
            class _Compare, class _Alloc>
    inline bool 
    operator<(const RB_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
            const RB_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y)
    {
        return ft::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
    }

    template <class _Key, class _Value, class _KeyOfValue, 
            class _Compare, class _Alloc>
    inline bool 
    operator!=(const RB_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
            const RB_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y)
    {
        return !(__x == __y);
    }

    template <class _Key, class _Value, class _KeyOfValue, 
            class _Compare, class _Alloc>
    inline bool 
    operator>(const RB_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
            const RB_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y)
    {
        return __y < __x;
    }

    template <class _Key, class _Value, class _KeyOfValue, 
            class _Compare, class _Alloc>
    inline bool 
    operator<=(const RB_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
            const RB_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y)
    {
        return !(__y < __x);
    }

    template <class _Key, class _Value, class _KeyOfValue, 
            class _Compare, class _Alloc>
    inline bool 
    operator>=(const RB_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
            const RB_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y)
    {
        return !(__x < __y);
    }

    template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
    inline void 
    swap(RB_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
        RB_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y)
    {
        __x.swap(__y);
    }


}

#endif // __FT_CONTAINERS__RB_TREE__
