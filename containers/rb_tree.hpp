#ifndef __FT_CONTAINERS__RB_TREE__
#define __FT_CONTAINERS__RB_TREE__

#include "./pair.hpp"
#include "./iterators.hpp"
#include "./rbtree_node.hpp"
#include "./utils.hpp"
#include <memory>

#define ERROR_ALLOCATE_MEMORY 134

namespace ft {

    template <class T1, class T2>
    class _RBT_rebalancer {
        public :
            typedef RBT_node<T1, T2>        node_type;
            typedef RBT_node<T1, T2>*       node_pointer;

            _RBT_rebalancer() {};

            void
            inline _rotate_left(node_pointer __x, node_pointer __root) {
                node_pointer __y = __x->_right;
                
                __x->_right = __y->_left;
                if (__y->_left != NULL)
                    __y->_left->_parent = __x;
                __y->_parent = __x->_parent;
                
                if (__x == __root)
                    __root = __y;
                else if (__x == __x->_parent->_left)
                    __x->_parent->_left = __y;
                else
                    __x->_parent->_right = __y;
                __y->_left = __x;
                __x->_parent = __y;
            }

            void
            inline _rotate_right(node_pointer __x, node_pointer __root) {
                node_pointer __y = __x->_left;

                __x->_left = __y->_right;
                if (__y->_right != NULL)
                    __y->_right->_parent = __x;
                __y->_parent = __x->_parent;

                if (__x == __root)
                    __root = __y;
                else if (__x == __x->_parent->_right)
                    __x->_parent->_right = __y;
                else
                    __x->_parent->_left = __y;
                __y->_right = __x;
                __x->_parent = __y;
            }

            void
            rebalance_insert(node_pointer __x, node_pointer __root) {
                __x->_color = RED;
                while (__x != __root && __x->_parent->_color == RED) {
                    if (__x->_parent == __x->_parent->_parent->_left) {
                        node_pointer __y = __x->_parent->_parent->_right;

                        if (__y && __y->is_red_node()) {
                            __x->_parent->_color = BLACK;
                            __y->_color = BLACK;
                            __x->_grandparent()->_color = RED;
                            __x = __x->_grandparent();
                        } else {
                            if (__x == __x->_parent->_right) {
                                __x = __x->_parent;
                                _rotate_left(__x, __root);
                            }
                            __x->_parent->_color = BLACK;
                            __x->_grandparent()->_color = RED;
                            _rotate_right(__x->_grandparent(), __root);
                        }
                    } else {
                        node_pointer __y = __x->_parent->_parent->_left;
                        
                        if (__y && __y->_color == RED) {
                            node_pointer __xg = __x->_grandparent();

                            __x->_parent->_color = BLACK;
                            __y->_color = BLACK;
                            __xg->_color = RED;
                            __x = __x->_grandparent();
                        } else {
                            if (__x == __x->_parent->_left) {
                                __x = __x->_parent;
                                _rotate_right(__x, __root);
                            }
                            __x->_parent->_color = BLACK;
                            __x->_grandparent()->_color = RED;
                            _rotate_left(__x->_grandparent(), __root);
                        }
                    }
                }
                __root->_color = BLACK;
            }

            void
            rebalance_erase(node_pointer __x, node_pointer __root)
            {
                while (__x != __root && __x->is_black_node()) {
                    if (__x->is_left()) {
                        node_pointer __s = __x->_siblings();

                        if (__s->_color == RED) {
                            __s->change_color(BLACK);
                            __x->_parent->change_color(RED);
                            _rotate_left(__x->_parent, __root);
                            __s = __x->_parent->_right;
                        }
                        if (__s->_left->is_black_node() && __s->_right->is_black_node()) {
                            __s->_color->change_color(RED);
                            __x = __x->_parent;
                        } else {
                            if (__s->_right->is_black_node()) {
                                __s->_left->change_color(BLACK);
                                __s->change_color(RED);
                                _rotate_right(__s, __root);
                                __s = __x->_parent->_right;
                            }
                            __s->change_color(__x->_parent->_color);
                            __x->_parent->change_color(BLACK);
                            __s->_right->change_color(BLACK);
                            _rotate_left(__x->_parent, __root);
                            __x = __root;
                        }
                    } else {
                        node_pointer __s = __x->_siblings();

                        if (__s->is_red_node()) {
                            __s->change_color(BLACK);
                            __x->_parent->change_color(RED);
                            _rotate_right(__x->_parent, __root);
                            __s = __x->_parent->_left;
                        }
                        if (__s->_left->is_black_node() && __s->_right->is_black_node()) {
                            __s->change_color(RED);
                            __x = __x->_parent;
                        } else {
                            if (__s->_left->is_black_node()) {
                                __s->_right->change_color(BLACK);
                                __s->change_color(RED);
                                _rotate_left(__s, __root);
                                __s = __x->_parent->_left;
                            }
                            __s->change_color(__x->_parent->_color);
                            __x->_parent->change_color(BLACK);
                            __s->_left->change_color(BLACK);
                            _rotate_right(__x->_parent, __root);
                            __x = __root;
                        }
                    }
                }
                if (!__x->is_nil_node())
                    __x->change_color(BLACK);
            }
    };

    template <class Key, class Mapped, class _Alloc>
    class _RBT_base {
        public :
            typedef Key                                                         key_type;
            typedef Mapped                                                      mapped_type;
            typedef size_t                                                      size_type;
            typedef ft::RBT_node<key_type, mapped_type>                         node_type;
            typedef ft::RBT_node<key_type, mapped_type>*                        node_pointer;
            typedef RBT_node_type                                               color_type;
            typedef typename _Alloc::template rebind<node_type>::other          allocator_type;
            typedef typename allocator_type::value_type                         value_type;

        protected :
            allocator_type                      _allocator;

        public :
            _RBT_base(const allocator_type& __a) : _allocator(__a) {};

            node_pointer
            create_node(key_type key, mapped_type value) {
                node_pointer __tmp = this->_allocator.allocate(1);
                try {
                    this->_allocator.construct(__tmp, value_type(key, value, NULL, NIL));
                }
                catch (...) {
                    this->_allocator.deallocate(__tmp, 1);
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
                    this->_allocator.deallocate(__tmp, 1);
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
    
    template <class Key, class Mapped, class _Compare, class _Alloc>
    class RB_tree : public _RBT_base<Key, Mapped, _Alloc> {
        private :
            typedef RBT_node<Key, Mapped>                                         node_type;
            typedef _RBT_rebalancer<Key, Mapped>                                  rebalancer_type;
        
        public :
            typedef Key                                                             key_type;
            typedef Mapped                                                          mapped_type;
            typedef _Compare                                                        key_compare;
            typedef typename _Alloc::template rebind<node_type>::other              allocator_type;
            typedef typename allocator_type::value_type                             value_type;
            typedef typename allocator_type::reference                              reference;
            typedef typename allocator_type::const_reference                        const_reference;
            typedef typename allocator_type::pointer                                pointer;
            typedef typename allocator_type::const_pointer                          const_pointer;
            typedef typename allocator_type::difference_type                        difference_type;
            typedef typename allocator_type::size_type                              size_type;

        private :
            key_compare                                 _comp;
            size_type                                   _size;
            pointer                                     _root;
            pointer                                     _nil;
            rebalancer_type                             _rebalancer;

        public :

            RB_tree()
                : _comp(key_compare()), _size(0), _root(),
                _nil(NULL), _rebalancer(rebalancer_type())
            {
                _root = this->create_node(key_type(), mapped_type());
            }

            ~RB_tree() {
                this->clear();
                this->destroy_node(_nil);
            }

            RB_tree&
            operator=(const RB_tree& __x) {
                if (this != &__x) {
                    this->clear();
                    _comp = __x._comp;
                    _rebalancer = __x._rebalancer;
                    for (pointer __tmp = __x.begin(); __tmp != __x.end(); __tmp = next(__tmp))
                        this->insert(*__tmp->_value);
                }
                return *this;
            }

            pointer
            begin() {
                return minimum(_root);
            }

            pointer
            begin() const {
                return minimum(_root);
            }

            pointer
            end() {
                return _nil;
            }

            pointer
            end() const {
                return _nil;
            }

            size_type
            size() const {
                return this->_size;
            }

            size_type
            max_size() const {
                return this->_allocator.max_size();
            }

            void clear() {
                clear(_root);
            }

            ft::pair<pointer, bool>
            insert(ft::pair<key_type, mapped_type> __x) {
                pointer __prt = _nil;
                pointer __cur = _root;

                while (__cur != _nil) {
                    if (__x.get_first() == __cur->_value->get_first())
                        return ft::pair<pointer, bool>(__cur, false);
                    __prt = __cur;
                    __cur = _comp(__x.get_first(), __cur->_value->get_first()) ? __cur->_left : __cur->_right;
                }
                pointer __tmp = this->create_node(__x.get_first(), __x.get_second(), RED);
                adopt_node_to_parent(__tmp, __prt);
                _rebalancer.rebalance_insert(__tmp, _root);
                _nil->_parent = maximum(_root);
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
                return search(_root, key);
            }

            pointer
            lower_bound(const key_type key) const {
                if (_root != _nil) {
                    pointer node, ret;

                    for (node = _root, ret = _root; node != _nil;) {
                        if (key == node->_value->get_first())
                            return node;
                        if (_comp(key, node->_value->get_first())) {
                            ret = node;
                            node = node->_left;
                        }
                        else
                            node = node->_right;
                    }
                    return _comp(key, ret->_value->get_first()) ? ret : _nil;
                }
                return _nil;
            }

            pointer
            upper_bound(const key_type key) const {
                if (_root != _nil) {
                    pointer node, ret;

                    for (node = _root, ret = _root; node != _nil;) {
                        if (_comp(key, node->_value->get_first())) {
                            ret = node;
                            node = node->_left;
                        }
                        else
                            node = node->_right;
                    }
                    return _comp(key, ret->_value->get_first()) ? ret : _nil;
                }
                return _nil;
            }

            void
            swap(RB_tree& x) {
                std::swap(_comp, x._comp);
                std::swap(_size, x._size);
                std::swap(_root, x._root);
                std::swap(_nil, x._nil);
                std::swap(_rebalancer, x._rebalancer);
            }

        private :
            
            pointer
            search(pointer __cur, const key_type& __k) const {
                while (__cur != _nil) {
                    if (__k == __cur->_value->get_first())
                        return __cur;
                    __cur = _comp(__k, __cur->_value->get_first()) ? __cur->_left : __cur->_right;
                }
                return _nil;
            }

            pointer
            maximum (pointer __x) const {
                while (!__x->is_nil_node() && !__x->_right->is_nil_node())
                    __x = __x->_right;
                return __x;
            }

            pointer
            minimum (pointer __x) const {
                while (!__x->is_nil_node() && !__x->_left->is_nil_node())
                    __x = __x->_left;
                return __x;
            }

            pointer
            next(pointer __x) const {
                if (__x->is_nil_node())
                    return __x;
                if (!__x->_right->is_nil_node())
                    return minimum(__x->_right);

                pointer __tmp = __x->_parent;
                while (!__tmp->is_nil_node() && __x == __tmp->_right) {
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
                clear(__x->_left);
                clear(__x->_right);
                if (__x == _root) {
                    _root = _nil;
                    _nil->_parent = _nil;
                    _size = 0;
                }
                this->destroy_node(__x);
            }

            void
            erase_aux(pointer target) {
                pointer __copy_target, __delete_target;

                if (target != _nil) {
                    __delete_target = (target->_left == _nil || target->_right == _nil) ? target : next(target);                     
                    __copy_target = __delete_target->_left == _nil ? __delete_target->_right : __delete_target->_left;
                    
                    if (__copy_target == _nil)
                        __copy_target->parent = __delete_target->parent;
                    if (__delete_target->parent == _nil)
                        _root = __copy_target;
                    else {
                        if (__delete_target == __delete_target->parent->_left)
                            __delete_target->parent->_left = __copy_target;
                        else
                            __delete_target->parent->_right = __copy_target;
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
                __p->_parent = __parent;
                if (__parent == this->_nil)
                    this->_root = __p;
                else if (_comp(__p->_value->get_first(), __parent->_value->get_first()))
                    __parent->_left = __p;
                else
                    __parent->_right = __p;
            }

            void
            reassign_node_data(pointer __origin, pointer __copied) {
                delete __copied->data;
                __copied->data = new value_type(__origin->data->first, __origin->data->second);
            }
    };

    template <class Key, class Mapped, class _Compare, class _Alloc>
    bool
    operator==(const RB_tree<Key, Mapped, _Compare, _Alloc>& __x,
            const RB_tree<Key, Mapped, _Compare, _Alloc>& __y) {
        return __x.size() == __y.size() && ft::equal(__x.begin(), __x.end(), __y.begin());
    }

    template <class Key, class Mapped, class _Compare, class _Alloc>
    bool
    operator!=(const RB_tree<Key, Mapped, _Compare, _Alloc>& __x,
            const RB_tree<Key, Mapped, _Compare, _Alloc>& __y) {
        return !(__x == __y);
    }

    template <class Key, class Mapped, class _Compare, class _Alloc>
    bool
    operator<(const RB_tree<Key, Mapped, _Compare, _Alloc>& __x,
            const RB_tree<Key, Mapped, _Compare, _Alloc>& __y) {
        return ft::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
    }

    template <class Key, class Mapped, class _Compare, class _Alloc>
    bool
    operator>(const RB_tree<Key, Mapped, _Compare, _Alloc>& __x,
            const RB_tree<Key, Mapped, _Compare, _Alloc>& __y) {
        return __y < __x;
    }

    template <class Key, class Mapped, class _Compare, class _Alloc>
    bool
    operator<=(const RB_tree<Key, Mapped, _Compare, _Alloc>& __x,
            const RB_tree<Key, Mapped, _Compare, _Alloc>& __y) {
        return !(__y < __x);
    }

    template <class Key, class Mapped, class _Compare, class _Alloc>
    bool
    operator>=(const RB_tree<Key, Mapped, _Compare, _Alloc>& __x,
            const RB_tree<Key, Mapped, _Compare, _Alloc>& __y) {
        return !(__x < __y);
    }


    template <class Key, class Mapped, class _Compare, class _Alloc>
    void
    swap (RB_tree<Key, Mapped, _Compare, _Alloc>& __x,
            RB_tree<Key, Mapped, _Compare, _Alloc>& __y) {
        __x.swap(__y);
    }



}

#endif // __FT_CONTAINERS__RB_TREE__
