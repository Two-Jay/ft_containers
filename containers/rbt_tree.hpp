#ifndef __FT_CONTAINERS__RBT_TREE__
#define __FT_CONTAINERS__RBT_TREE__

#include "./pair.hpp"
#include "./iterators.hpp"
#include "./rbt_node.hpp"
#include "./utils.hpp"
#include <memory>
#include <iostream>
#include <string>

#define ERROR_ALLOCATE_MEMORY 134

namespace ft
{

    template <class Key, class Mapped, class _Compare, class _Alloc>
    class rbt_tree
    {
    private:
    public:
        typedef Key                                                                     key_type;
        typedef Mapped                                                                  mapped_type;
        typedef _Compare                                                                key_compare;
        typedef typename _Alloc::template rebind<ft::rbt_node<Key, Mapped> >::other     allocator_type;
        typedef typename allocator_type::value_type                                     value_type;
        typedef typename allocator_type::reference                                      reference;
        typedef typename allocator_type::const_reference                                const_reference;
        typedef typename allocator_type::pointer                                        pointer;
        typedef typename allocator_type::const_pointer                                  const_pointer;
        typedef typename allocator_type::size_type                                      size_type;
        typedef typename allocator_type::difference_type                                difference_type;

    private:
        typedef ft::rbt_node_type       node_type;
        allocator_type                  _alloc;
        key_compare                     _comp;
        size_type                       _size;
        pointer                         _root;
        pointer                         _nil;

    public:
        rbt_tree() : _alloc(), _comp(key_compare()), _size(0), _root(NULL), _nil(NULL)
        {
            this->_nil = this->create_node(key_type(), mapped_type(), NULL, NIL);
            this->_root = _nil;
        }

        ~rbt_tree()
        {
            this->clear();
            this->destroy_node(_nil);
        }

        rbt_tree &
        operator=(const rbt_tree &__x)
        {
            if (this != &__x)
            {
                this->clear();
                _comp = __x._comp;
                for (pointer __tmp = __x.begin(); __tmp != __x.end(); __tmp = next(__tmp))
                    this->insert(*__tmp->_value);
            }
            return *this;
        }

        pointer
        begin()
        {
            return this->minimum(_root);
        }

        pointer
        begin() const
        {
            return this->minimum(_root);
        }

        pointer
        end()
        {
            return this->_nil;
        }

        pointer
        end() const
        {
            return this->_nil;
        }

        size_type
        size() const
        {
            return this->_size;
        }

        allocator_type
        get_allocator() const
        {
            return this->_alloc;
        }

        size_type
        max_size() const
        {
            return this->get_allocator().max_size();
        }

        void
        clear()
        {
            this->clear_aux(_root);
        }

        ft::pair<pointer, bool>
        insert(ft::pair<const key_type, mapped_type> __x)
        {
            pointer __prt = _nil;
            pointer __cur = _root;

            while (__cur != _nil)
            {
                if (__x.first == __cur->_value->first)
                    return ft::pair<pointer, bool>(__cur, false);
                __prt = __cur;
                __cur = _comp(__x.first, __cur->_value->first) ? __cur->_left : __cur->_right;
            };
            pointer __tmp = this->create_node(__x.first, __x.second, _nil, RED);

            this->adopt_node_to_parent(__tmp, __prt);
            this->rebalance_insert(__tmp);
            _nil->_parent = maximum(_root);
            ++_size;
            return ft::pair<pointer, bool>(__tmp, true);
        }

        bool
        erase(key_type key)
        {
            pointer node = this->search(_root, key);
            if (node == _nil)
                return false;
            erase_aux(node);
            --_size;
            return true;
        }

        pointer
        find(key_type key) const
        {
            return search(_root, key);
        }

        pointer
        lower_bound(const key_type key) const
        {
            if (_root != _nil)
            {
                pointer node, ret;

                for (node = _root, ret = _root; node != _nil;)
                {
                    if (key == node->_value->first)
                        return node;
                    if (_comp(key, node->_value->first))
                    {
                        ret = node;
                        node = node->_left;
                    }
                    else
                        node = node->_right;
                }
                return _comp(key, ret->_value->first) ? ret : _nil;
            }
            return _nil;
        }

        pointer
        upper_bound(const key_type key) const
        {
            if (_root != _nil)
            {
                pointer node, ret;

                for (node = _root, ret = _root; node != _nil;)
                {
                    if (_comp(key, node->_value->first))
                    {
                        ret = node;
                        node = node->_left;
                    }
                    else
                        node = node->_right;
                }
                return _comp(key, ret->_value->first) ? ret : _nil;
            }
            return _nil;
        }

        void
        swap(rbt_tree &x)
        {
            std::swap(_comp, x._comp);
            std::swap(_size, x._size);
            std::swap(_root, x._root);
            std::swap(_nil, x._nil);
        }

        void
        print() const
        {
            print_aux(_root, "", true);
        }

    private:
        void inline _rotate_left(pointer __x)
        {
            pointer __y = __x->_right;

            __x->_right = __y->_left;
            if (__y->_left != NULL)
                __y->_left->_parent = __x;
            __y->_parent = __x->_parent;

            if (__x == _root)
                _root = __y;
            else if (__x == __x->_parent->_left)
                __x->_parent->_left = __y;
            else
                __x->_parent->_right = __y;
            __y->_left = __x;
            __x->_parent = __y;
        }

        void inline _rotate_right(pointer __x)
        {
            pointer __y = __x->_left;

            __x->_left = __y->_right;
            if (__y->_right != NULL)
                __y->_right->_parent = __x;
            __y->_parent = __x->_parent;

            if (__x == _root)
                _root = __y;
            else if (__x == __x->_parent->_right)
                __x->_parent->_right = __y;
            else
                __x->_parent->_left = __y;
            __y->_right = __x;
            __x->_parent = __y;
        }

        void
        rebalance_insert(pointer __x)
        {
            while (__x != _root && __x->_parent->_color == RED)
            {
                if (__x->_parent->is_left())
                {
                    pointer __y = __x->_uncle();

                    if (is_red_node(__y))
                    {
                        __x->_parent->change_color(BLACK);
                        __y->change_color(BLACK);
                        __x->_grandparent()->change_color(RED);
                        __x = __x->_grandparent();
                    }
                    else
                    {
                        if (__x->is_right())
                        {
                            __x = __x->_parent;
                            _rotate_left(__x);
                        }
                        __x->_parent->change_color(BLACK);
                        __x->_grandparent()->change_color(RED);
                        _rotate_right(__x->_grandparent());
                    }
                }
                else
                {
                    pointer __y = __x->_uncle();

                    if (__y && __y->_color == RED)
                    {
                        pointer __xg = __x->_grandparent();

                        __x->_parent->change_color(BLACK);
                        __y->change_color(BLACK);
                        __xg->change_color(RED);
                        __x = __x->_grandparent();
                    }
                    else
                    {
                        if (__x == __x->_parent->_left)
                        {
                            __x = __x->_parent;
                            _rotate_right(__x);
                        }
                        __x->_parent->change_color(BLACK);
                        __x->_grandparent()->change_color(RED);
                        _rotate_left(__x->_grandparent());
                    }
                }
            }
            _root->change_color(BLACK);
        }

        void
        rebalance_erase(pointer __x)
        {
            while (__x != _root && is_black_node(__x))
            {
                if (__x->is_left())
                {
                    pointer __s = __x->_sibling();

                    if (is_red_node(__s))
                    {
                        __s->change_color(BLACK);
                        __x->_parent->change_color(RED);
                        _rotate_left(__x->_parent);
                        __s = __x->_parent->_right;
                    }
                    if (is_black_node(__s->_left) && is_black_node(__s->_right))
                    {
                        __s->change_color(RED);
                        __x = __x->_parent;
                    }
                    else
                    {
                        if (is_black_node(__s->_right))
                        {
                            __s->_left->change_color(BLACK);
                            __s->change_color(RED);
                            _rotate_right(__s);
                            __s = __x->_parent->_right;
                        }
                        __s->_color = __x->_parent->_color;
                        __x->_parent->change_color(BLACK);
                        __s->_right->change_color(BLACK);
                        _rotate_left(__x->_parent);
                        __x = _root;
                    }
                }
                else
                {
                    pointer __s = __x->_sibling();

                    if (is_red_node(__s))
                    {
                        __s->change_color(BLACK);
                        __x->_parent->change_color(RED);
                        _rotate_right(__x->_parent);
                        __s = __x->_parent->_left;
                    }
                    if (is_black_node(__s->_left) && is_black_node(__s->_right))
                    {
                        __s->change_color(RED);
                        __x = __x->_parent;
                    }
                    else
                    {
                        if (is_black_node(__s->_left))
                        {
                            __s->_right->change_color(BLACK);
                            __s->change_color(RED);
                            _rotate_left(__s);
                            __s = __x->_parent->_left;
                        }
                        __s->_color = __x->_parent->_color;
                        __x->_parent->change_color(BLACK);
                        __s->_left->change_color(BLACK);
                        _rotate_right(__x->_parent);
                        __x = _root;
                    }
                }
            }
            if (!is_nil_node(__x))
                __x->change_color(BLACK);
        }

        void
        print_aux(pointer node, std::string indent, bool isLast) const
        {
            if (node != _nil)
            {
                std::cout << indent;
                if (isLast)
                {
                    std::cout << "R----";
                    indent += "   ";
                }
                else
                {
                    std::cout << "L----";
                    indent += "|  ";
                }
                std::string sColor = is_nil_node(node) ? "NIL" : is_red_node(node) ? "RED"
                                                                                   : "BLACK";
                std::string sRoot = node == _root ? "ROOT" : "";
                std::cout << node->_value->first << ":" << sColor << sRoot << std::endl;
                print_aux(node->_left, indent, false);
                print_aux(node->_right, indent, true);
            }
        }

        pointer
        search(pointer __cur, const key_type &__k) const
        {
            while (__cur != _nil)
            {
                if (__k == __cur->_value->first)
                    return __cur;
                __cur = _comp(__k, __cur->_value->first) ? __cur->_left : __cur->_right;
            }
            return _nil;
        }

        pointer
        maximum(pointer __x) const
        {
            while (!is_nil_node(__x) && !is_nil_node(__x->_right))
                __x = __x->_right;
            return __x;
        }

        pointer
        minimum(pointer __x) const
        {
            while (!is_nil_node(__x) && !is_nil_node(__x->_left))
                __x = __x->_left;
            return __x;
        }

        pointer
        next(pointer __x) const
        {
            if (is_nil_node(__x))
                return __x;
            if (!is_nil_node(__x->_right))
                return minimum(__x->_right);

            pointer __tmp = __x->_parent;
            while (!is_nil_node(__tmp) && __x == __tmp->_right)
            {
                __x = __tmp;
                __tmp = __tmp->_parent;
            }
            return __tmp;
        }

        pointer
        prev(pointer __x) const
        {
            if (__x->_color == NIL)
                return __x->_parent;
            if (__x->_right->_color != NIL)
                return minimum(__x->_right);

            pointer __tmp = __x->_parent;
            while (__tmp != _nil && __x == __tmp->_left)
            {
                __x = __tmp;
                __tmp = __tmp->_parent;
            }
            return __tmp;
        }

        void
        clear_aux(pointer __x)
        {
            if (__x == NULL || __x == _nil)
                return;
            clear_aux(__x->_left);
            clear_aux(__x->_right);
            if (__x == _root)
            {
                _root = _nil;
                _nil->_parent = _nil;
                _size = 0;
            }
            this->destroy_node(__x);
        }

        void
        erase_aux(pointer __t)
        {
            pointer __x, __y;

            if (!is_nil_node(__t))
            {
                // 이 부분에서 끌어올릴 노드를 오른쪽 자식의 가장 왼쪽 노드로 설정한다. (삭제할 노드의 큰 값 중 가장 작은 값)
                if (is_nil_node(__t->_left) || is_nil_node(__t->_right))
                    __y = __t;
                else
                {
                    __y = __t->_right;
                    while (!is_nil_node(__y->_left))
                        __y = __y->_left;
                }

                __x = is_nil_node(__y->_left) ? __y->_right : __y->_left;

                if (is_nil_node(__x))
                    __x->_parent = __y->_parent;
                if (is_nil_node(__y->_parent))
                    _root = __x;
                else
                {
                    if (__y->is_left())
                        __y->_parent->_left = __x;
                    else
                        __y->_parent->_right = __x;
                }

                if (__y != __t)
                    reassign_node_data(__y, __t);
                if (is_black_node(__y))
                    rebalance_erase(__x);
                this->destroy_node(__y);
                _nil->_parent = maximum(_root);
            }
        }

        void
        adopt_node_to_parent(pointer __p, pointer __parent)
        {
            __p->_parent = __parent;
            if (__parent == this->_nil)
                this->_root = __p;
            else
            {
                if (_comp(__p->_value->first, __parent->_value->first))
                    __parent->_left = __p;
                else
                    __parent->_right = __p;
            }
        }

        void
        reassign_node_data(pointer __origin, pointer __copied)
        {
            delete __copied->_value;
            __copied->_value = new ft::pair<const Key, mapped_type>(__origin->_value->first, __origin->_value->second);
        }

        pointer
        create_node(key_type key, mapped_type value, pointer ptr, node_type color)
        {
            pointer __tmp = this->get_allocator().allocate(1);
            value_type __node(key, value, ptr, color);
            try
            {
                this->get_allocator().construct(__tmp, __node);
            }
            catch (...)
            {
                this->get_allocator().deallocate(__tmp, 1);
                exit(ERROR_ALLOCATE_MEMORY);
            }
            return __tmp;
        };

        void
        destroy_node(pointer __p)
        {
            this->get_allocator().destroy(__p);
            this->get_allocator().deallocate(__p, 1);
        }

        bool inline is_red_node(pointer __p) const
        {
            return __p && __p->_color == RED ? true : false;
        }

        bool inline is_black_node(pointer __p) const
        {
            return __p && __p->_color == BLACK ? true : false;
        }

        bool inline is_nil_node(pointer __p) const
        {
            return __p && __p->_color == NIL ? true : false;
        }
    };

    template <class Key, class Mapped, class _Compare, class _Alloc>
    bool
    operator==(const rbt_tree<Key, Mapped, _Compare, _Alloc> &__x,
               const rbt_tree<Key, Mapped, _Compare, _Alloc> &__y)
    {
        return __x.size() == __y.size() && ft::equal(__x.begin(), __x.end(), __y.begin());
    }

    template <class Key, class Mapped, class _Compare, class _Alloc>
    bool
    operator!=(const rbt_tree<Key, Mapped, _Compare, _Alloc> &__x,
               const rbt_tree<Key, Mapped, _Compare, _Alloc> &__y)
    {
        return !(__x == __y);
    }

    template <class Key, class Mapped, class _Compare, class _Alloc>
    bool
    operator<(const rbt_tree<Key, Mapped, _Compare, _Alloc> &__x,
              const rbt_tree<Key, Mapped, _Compare, _Alloc> &__y)
    {
        return ft::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
    }

    template <class Key, class Mapped, class _Compare, class _Alloc>
    bool
    operator>(const rbt_tree<Key, Mapped, _Compare, _Alloc> &__x,
              const rbt_tree<Key, Mapped, _Compare, _Alloc> &__y)
    {
        return __y < __x;
    }

    template <class Key, class Mapped, class _Compare, class _Alloc>
    bool
    operator<=(const rbt_tree<Key, Mapped, _Compare, _Alloc> &__x,
               const rbt_tree<Key, Mapped, _Compare, _Alloc> &__y)
    {
        return !(__y < __x);
    }

    template <class Key, class Mapped, class _Compare, class _Alloc>
    bool
    operator>=(const rbt_tree<Key, Mapped, _Compare, _Alloc> &__x,
               const rbt_tree<Key, Mapped, _Compare, _Alloc> &__y)
    {
        return !(__x < __y);
    }

    template <class Key, class Mapped, class _Compare, class _Alloc>
    void
    swap(rbt_tree<Key, Mapped, _Compare, _Alloc> &__x,
         rbt_tree<Key, Mapped, _Compare, _Alloc> &__y)
    {
        __x.swap(__y);
    }

} // end namespace ft here

#endif // __FT_CONTAINERS__RBT_TREE__
