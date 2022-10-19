#ifndef __FT_CONTAINERS__RB_TREE__
#define __FT_CONTAINERS__RB_TREE__

#include "./pair.hpp"
#include "./iterators.hpp"
#include "./rbtree_node.hpp"
#include "./utils.hpp"
#include <memory>

#define ERROR_ALLOCATE_MEMORY 134

namespace ft {

    template <class Key, class Mapped, class _Alloc>
    class _RBT_base {
        public :
            typedef Key                                                         key_type;
            typedef Mapped                                                      mapped_type;
            typedef ft::pair<const Key, Mapped>                                 value_type;
            typedef size_t                                                      size_type;
            typedef ft::RBT_node<key_type, mapped_type>                         node_type;
            typedef ft::RBT_node<key_type, mapped_type>*                        node_pointer;
            typedef RBT_node_type                                               color_type;
            typedef typename Alloc::template rebind<node_type>::other           allocator_type;

        protected :
            allocator_type                      _allocator;

        public :
            _RBT_base() {};

            explicit _RBT_base(const allocator_type& __a) : _allocator(__a) {};

            node_pointer
            create_node(key_type key, mapped_type value) {
                node_pointer __tmp = this->_allocator.allocate(1);
                try {
                    this->_allocator.construct(__tmp, value_type(key, value, NULL, nil_node));
                }
                catch (...) {
                    this->_put_node(__tmp);
                    exit(ERROR_ALLOCATE_MEMORY);
                }
                return __tmp;
            };

            node_pointer
            create_node(key_type key, mapped_type value, color_type color) {
                node_pointer __tmp = this->_allocator.allocate(1);
                try {
                    this->_allocator.construct(__tmp, value_type(key, value, NULL, color));
                }
                catch (...) {
                    this->_put_node(__tmp);
                    exit(ERROR_ALLOCATE_MEMORY);
                }
                return __tmp;
            };

            void
            destroy_node(node_pointer __p) {
                this->_allocator.destroy(__p);
                this->_allocator.deallocate(__p, 1);
            }            
    };
    
    template <class _Key, class _Mapped, class _Compare, class _Alloc>
    class RB_tree : public _RBT_base<ft::pair<_Key, _Mapped>, _Alloc> {
        private :
            typedef RBT_node<_Key, _Mapped>                                         node_type;
            typedef _RBT_rebalancer<_Key, _Mapped>                                  rebalancer_type;
        
        public :
            typedef _Key                                                            key_type;
            typedef _Mapped                                                         mapped_type;
            typedef _Compare                                                        key_compare;
            typedef typename allocator_type::template rebind<node_type>::other      allocator_type;
            typedef allocator_type::value_type                                      value_type;
            typedef allocator_type::reference                                       reference;
            typedef allocator_type::const_reference                                 const_reference;
            typedef allocator_type::pointer                                         pointer;
            typedef allocator_type::const_pointer                                   const_pointer;
            typedef allocator_type::difference_type                                 difference_type;
            typedef allocator_type::size_type                                       size_type;

        private :
            key_compare                                 _comp;
            size_type                                   _size;
            pointer                                     _root;
            pointer                                     _nil;
            rebalancer_type                             _rebalancer;

        public :

            RB_tree() : _alloc(), _comp(), _size(0), _root(NULL), _nil(NULL), _rebalancer(rebalancer_type()) {
                this->_nil = this->_create_node(key_type(), mapped_type());
                this->_nil->color = RBT_node_type::BLACK;
                this->_root = this->_nil;
            }

            size_type size() const { return _size; }

            size_type max_size() const { return _alloc.max_size(); }


            void clear() {
                clear(_root);
            }
            
            ft::pair<pointer, bool>
            insert(const value_type& __x) {
                pointer __prt = _nil;
                pointer __cur = _root;

                while (__cur != _nil) {
                    if (__x.first == __cur->value.first)
                        return ft::pair<pointer, bool>(__cur, false);
                    __prt = __cur;
                    __cur = _comp(__x.first, __cur->value.first) ? __cur->left : __cur->right;
                }
                pointer __tmp = _create_node(__x.first, __x.second, RED);
                adopt_node_to_parent(__tmp, __prt);
                _rebalancer.rebalance_insert(__tmp, _root);
                _nil->parent = maximum(_root);
                ++_size;
                return ft::pair<pointer, bool>(__tmp, true);
            }

            bool
            erase(key_type key) {
                pointer node = find(_root, key);
                if (node == _nil)
                    return false;
                erase_aux(node);
                --_size;
                return true;
            }

            pointer
            find(key_type key) const {
                return find(_root, key);
            }

            pointer
            lower_bound(key_type key) const {
                if (_root != _nil) {
                    for (pointer node = _root, pointer ret = _root; node != _nil;) {
                        if (key == node->value.first)
                            return node;
                        if (_comp(key, node->value.first)) {
                            ret = node;
                            node = node->left;
                        }
                        else
                            node = node->right;
                    }
                    return _comp(key, ret->value.first) ? ret : _nil;
                }
                return _nil;
            }

            pointer
            upper_bound(key_type key) const {
                if (_root != _nil) {
                    for (pointer node = _root, pointer ret = _root; node != _nil;) {
                        if (_comp(key, node->value.first)) {
                            ret = node;
                            node = node->left;
                        }
                        else
                            node = node->right;
                    }
                    return _comp(key, ret->value.first) ? ret : _nil;
                }
                return _nil;
            }

            void
            swap(RB_tree& x) {
                ft::swap(_comp, x._comp);
                ft::swap(_size, x._size);
                ft::swap(_root, x._root);
                ft::swap(_nil, x._nil);
                ft::swap(_rebalancer, x._rebalancer);
            }

        private :
            
            pointer
            search(pointer __cur, const key_type& __k) const {
                while (__cur != _nil) {
                    if (__k == __cur->value.first)
                        return __cur;
                    else if (_comp(__k, __cur->value.first))
                        __cur = __cur->left;
                    else
                        __cur = __cur->right;
                }
                return 
            }

            pointer
            maximum (pointer __x) const {
                while (__x->_color != NIL && __x->right != _nil)
                    __x = __x->right;
                return __x;
            }

            pointer
            minimum (node_pointer __x) const {
                while (__x->_color != NIL && __x->left != _nil)
                    __x = __x->left;
                return __x;
            }

            pointer
            next(pointer __x) const {
                if (__x->_color == NIL)
                    return __x;
                if (__x->right->_color != NIL)
                    return minimum(__x->right);

                pointer __tmp = __x->_parent;
                while (__tmp != _nil && __x == __tmp->right) {
                    __x = __tmp;
                    __tmp = __tmp->_parent;
                }
                return __tmp;
            }

            pointer
            prev(pointer __x) const {
                if (__x->_color == NIL)
                    return __x->_parent;
                if (__x->_right->_color != NIL)
                    return minimum(__x->_right);

                pointer __tmp = __x->_parent;
                while (__tmp != _nil && __x == __tmp->_left) {
                    __x = __tmp;
                    __tmp = __tmp->_parent;
                }
                return __tmp;
            }

            void
            clear(pointer __x) {
                if (__x == NULL || __x == _nil)
                    return ;
                clear(__x->left);
                clear(__x->right);
                if (__x == _root) {
                    _root = _nil;
                    _nil->parent = _nil;
                    _size = 0;
                }
                destroy_node(__x);
            }

            void
            erase_aux(pointer target) {
                pointer __copy_target, __delete_target;

                if (target != _nil) {
                    __delete_target = (target->left == _nil || target->right == _nil) ? target : next(target);                     
                    __copy_target = __y->left == _nil ? __y->right : __y->left;
                    
                    if (__copy_target == _nil)
                        __copy_target->parent = __delete_target->parent;
                    if (__delete_target->parent == _nil)
                        _root = __copy_target;
                    else {
                        if (__delete_target == __delete_target->parent->left)
                            __delete_target->parent->left = __copy_target;
                        else
                            __delete_target->parent->right = __copy_target;
                    }

                    if (__delete_target != target)
                        reassign_node_data(__delete_target, target);
                        
                    if (__delete_target->_color == BLACK)
                        _rebalancer.rebalance_erase(__copy_target, _root);

                    destroy_node(__delete_target);
                    _nil->parent = maximum(_root);
                }
            }

            void
            adopt_node_to_parent(pointer __p, pointer __parent) {
                __p->parent = __parent;
                if (__parent == this->_nil)
                    this->_root = __p;
                else if (_comp(__p->value.first, __parent->value.first))
                    __parent->left = __p;
                else
                    __parent->right = __p;
            }

            void
            reassign_node_data(pointer __origin, pointer __copied) {
                delete copied->data;
                copied->data = new value_type(origin->data->first, origin->data->second);
            }
    };
}

#endif // __FT_CONTAINERS__RB_TREE__
