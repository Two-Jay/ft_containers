#ifndef __FT_CONTAINERS__SET__
#define __FT_CONTAINERS__SET__

#include "./rb_tree.hpp"
#include "./pair.hpp"
#include <memory>

namespace ft
{
    template <class _Key, class _Compare = std::less<_Key>, class _Alloc = std::allocator<_Key> >
    class set {


        public :
            typedef _Key                                key_type;
            typedef _Key                                value_type;
            typedef _Compare                            key_compare;
            typedef _Compare                            value_compare;
        private :
            typedef ft::RB_tree<key_type, value_type, key_compare, _Alloc>      _tree_type;
            typedef ft::set<key_type, key_compare, _Alloc>                      _self_type;
        public :
            typedef typename _tree_type::pointer                 pointer;
            typedef typename _tree_type::const_pointer           const_pointer;
            typedef typename _tree_type::reference               reference;
            typedef typename _tree_type::const_reference         const_reference; 
            typedef typename _tree_type::iterator                iterator;
            typedef typename _tree_type::const_iterator          const_iterator;
            typedef typename _tree_type::reverse_iterator        reverse_iterator;
            typedef typename _tree_type::const_reverse_iterator  const_reverse_iterator;
            typedef typename _tree_type::size_type               size_type;
            typedef typename _tree_type::difference_type         difference_type;
            typedef typename _tree_type::allocator_type          allocator_type;

        
        protected :
            _tree_type                                  _tree;

        public :

            set() : _tree(_Compare(), allocator_type()) {}

            explicit set(const key_compare& _comp, const allocator_type& _alloc = allocator_type())
                : _tree(_comp, _alloc) {}

            template <class _InputIterator>
            set(_InputIterator _first, _InputIterator _last)
                : _tree(_Compare(), allocator_type()) {
                _tree.insert(_first, _last);
            }

            template <class _InputIterator>
            set(_InputIterator _first, _InputIterator _last, const key_compare& _comp = key_compare(),
                const allocator_type& _alloc = allocator_type())
                : _tree(_comp, _alloc) {
                _tree.insert(_first, _last);
            }

            set(const _self_type& _x) : _tree(_x._tree) {}

            _self_type&
            operator=(const _self_type& _x) {
                _tree = _x._tree;
                return *this;
            }

            ~set() {}

            key_compare
            key_comp() const {
                return _tree.key_comp();
            }

            value_compare
            value_comp() const {
                return _tree.key_comp();
            }

            allocator_type
            get_allocator() const {
                return _tree.get_allocator();
            }

            iterator
            begin() {
                return _tree.begin();
            }

            const_iterator
            begin() const {
                return _tree.begin();
            }

            iterator
            end() {
                return _tree.end();
            }

            const_iterator
            end() const {
                return _tree.end();
            }

            reverse_iterator
            rbegin() {
                return _tree.rbegin();
            }

            const_reverse_iterator
            rbegin() const {
                return _tree.rbegin();
            }

            reverse_iterator
            rend() {
                return _tree.rend();
            }

            const_reverse_iterator
            rend() const {
                return _tree.rend();
            }

            bool
            empty() const {
                return _tree.empty();
            }

            size_type
            size() const {
                return _tree.size();
            }

            size_type
            max_size() const {
                return _tree.max_size();
            }

            void
            swap(_self_type& _x) {
                _tree.swap(_x._tree);
            }

            // why the contributors of the standard library
            // decided to return a copy of retured iterator from insert() here ?
            // ft::pair<iterator, bool>
            // insert(const value_type& _x) {
            //     pair<typename _Rep_type::iterator, bool> __p = _M_t.insert_unique(__x); 
            //     return pair<iterator, bool>(__p.first, __p.second);                
            // }

            ft::pair<iterator, bool>
            insert(const value_type& _x) {
                return _tree.insert(_x);
            }

            iterator
            insert(iterator _position, const value_type& _x) {
                return _tree.insert(_position, _x);
            }

            template <class _InputIterator>
            void
            insert(_InputIterator _first, _InputIterator _last) {
                _tree.insert(_first, _last);
            }

            void
            erase(iterator _position) {
                _tree.erase(_position);
            }

            size_type
            erase(const key_type& _x) {
                return _tree.erase(_x);
            }

            void
            erase(iterator _first, iterator _last) {
                _tree.erase(_first, _last);
            }

            void
            clear() {
                _tree.clear();
            }

            size_type
            count(const key_type& _x) const {
                return _tree.find(_x) == _tree.end() ? 0 : 1;
            }

            iterator
            find(const key_type& _x) {
                return _tree.find(_x);
            }

            iterator
            lower_bound (const key_type& _x) const {
                return _tree.lower_bound(_x);
            }

            iterator
            upper_bound (const key_type& _x) const {
                return _tree.upper_bound(_x);
            }

            ft::pair<iterator, iterator>
            equal_range (const key_type& _x) const {
                return _tree.equal_range(_x);
            }
    };

    #define _SET_OPE_MACRO(OP) \
        __x._tree OP __y._tree

    template <class _Key, class _Compare, class _Alloc>
    bool
    operator==(const set<_Key, _Compare, _Alloc>& __x, const set<_Key, _Compare, _Alloc>& __y) {
        return _SET_OPE_MACRO(==);
    }

    template <class _Key, class _Compare, class _Alloc>
    bool
    operator<(const set<_Key, _Compare, _Alloc>& __x, const set<_Key, _Compare, _Alloc>& __y) {
        return _SET_OPE_MACRO(<);
    }

    template <class _Key, class _Compare, class _Alloc>
    bool
    operator!=(const set<_Key, _Compare, _Alloc>& __x, const set<_Key, _Compare, _Alloc>& __y) {
        return _SET_OPE_MACRO(!=);
    }

    template <class _Key, class _Compare, class _Alloc>
    bool
    operator>(const set<_Key, _Compare, _Alloc>& __x, const set<_Key, _Compare, _Alloc>& __y) {
        return _SET_OPE_MACRO(>);
    }

    template <class _Key, class _Compare, class _Alloc>
    bool
    operator>=(const set<_Key, _Compare, _Alloc>& __x, const set<_Key, _Compare, _Alloc>& __y) {
        return _SET_OPE_MACRO(>=);
    }

    template <class _Key, class _Compare, class _Alloc>
    bool
    operator<=(const set<_Key, _Compare, _Alloc>& __x, const set<_Key, _Compare, _Alloc>& __y) {
        return _SET_OPE_MACRO(<=);
    }

    #undef _SET_OPE_MACRO

    template <class _Key, class _Compare, class _Alloc>
    void
    swap(set<_Key, _Compare, _Alloc>& __x, set<_Key, _Compare, _Alloc>& __y) {
        __x.swap(__y);
    }
}

#endif // __FT_CONTAINERS__SET__
