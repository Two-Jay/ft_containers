#ifndef __FT_CONTAINERS__MAP__
#define __FT_CONTAINERS__MAP__

#include "./rb_tree.hpp"
#include "./pair.hpp"
#include <memory>


namespace ft
{
    template <class _Key, class _T, class _Compare = std::less<_Key>,
            class _Alloc = std::allocator<ft::pair<const _Key, _T> > >
    class map {


        public :
            typedef _Key                                key_type;
            typedef _T                                  mapped_type;
            typedef ft::pair<const _Key, _T>            value_type;
            typedef _Compare                            key_compare;
            typedef _Alloc                              allocator_type;
            typedef value_type&                         reference;
            typedef const value_type&                   const_reference;
            typedef allocator_type::pointer             pointer;
            typedef allocator_type::const_pointer       const_pointer;

        private :
            typedef ft::rb_tree<key_type, _value_type, key_compare, allocator_type> _tree_type;

        public :
            typedef _tree_type::iterator                iterator;
            typedef _tree_type::const_iterator          const_iterator;
            typedef _tree_type::reverse_iterator        reverse_iterator;
            typedef _tree_type::const_reverse_iterator  const_reverse_iterator;
            typedef _tree_type::size_type               size_type;
            typedef _tree_type::difference_type         difference_type;


        protected :
			class value_compare {
				protected:
					key_compare comp;
					value_compare (key_compare _c): comp(_c) {}
				public:

					value_compare() {}
					value_compare(const value_compare& _x): comp(_x.comp) {}
					~value_compare() {}

					value_compare&
					operator=(const value_compare& _x) {
						comp = _x.comp;
						return *this;
					}
					
					bool
					operator() (const value_type& _v1, const value_type& _v2) const {
						return comp(_v1.first, _v2.first);
					}
			};

            typedef ft::map<_Key, _T, _Compare, _Alloc>     _self_type;
            typedef ft::value_compare<_Key, _T, _Compare>   _value_compare;


            _tree                       _tree;
            allocator_type              _alloc;
            _key_compare                _key_comp;
            _value_compare              _value_comp;


        public:
            map() : _tree(key_compare(), allocator_type()), _alloc(allocator_type()), _key_comp(key_compare()) {}

            explicit map(const key_compare& __comp,
                    const allocator_type& __alloc = allocator_type())
                : _tree(__comp, __alloc), _alloc(__alloc), _key_comp(__comp) {}

            template <class _InputIterator>
            map(_InputIterator __first, _InputIterator __last)
                : _tree(key_compare(), allocator_type()), _alloc(allocator_type()), _key_comp(key_compare())
            { _tree.insert(__first, __last); }

            template <class _InputIterator>
            map(_InputIterator __first, _InputIterator __last, const key_compare& __comp,
                    const allocator_type& __alloc = allocator_type())
                : _tree(__comp, __alloc), _alloc(__alloc), _key_comp(__comp)
            { _tree.insert(__first, __last); }

            map(const _self_type& __x) : _tree(__x._tree), _alloc(__x._alloc), _key_comp(__x._key_comp) {}

            _self_type&
            operator=(const _self_type& __x)
            {
                _tree = __x._tree;
                return *this;
            }

            ~map() {}

            key_compare
            key_comp() const {
                return _key_comp;
            }

            value_compare
            value_comp() const {
                return _value_comp;
            }

            allocator_type
            get_allocator() const {
                return _alloc;
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

            mapped_type&
            operator[](const key_type& __k) {
                iterator __i = this->lower_bound(__k);
                if (__i == this->end() || this->key_comp()(__k, (*__i).first))
                    __i = this->insert(__i, value_type(__k, mapped_type()));
                return (*__i).second;
            }

            void
            swap(_self_type& __x) {
                _tree.swap(__x._tree);
            }

            ft::pair<iterator, bool>
            insert(const value_type& __x) {
                return _tree.insert(__x);
            }

            iterator
            insert(iterator __pos, const value_type& __x) {
                return _tree.insert(__pos, __x);
            }

            template <class _InputIterator>
            void
            insert(_InputIterator __first, _InputIterator __last) {
                _tree.insert(__first, __last);
            }
        

            void
            erase(iterator __pos) {
                _tree.erase(__pos);
            }

            size_type
            erase(const key_type& __x) {
                return _tree.erase(__x);
            }

            void
            erase(iterator __first, iterator __last) {
                _tree.erase(__first, __last);
            }

            void
            clear() {
                _tree.clear();
            }

            iterator
            find(const key_type& __x) {
                return _tree.find(__x);
            }

            const_iterator
            find(const key_type& __x) const {
                return _tree.find(__x);
            }

            size_type
            count(const key_type& __x) const {
                return _tree.count(__x);
            }

            iterator
            lower_bound(const key_type& __x) {
                return _tree.lower_bound(__x);
            }

            const_iterator
            lower_bound(const key_type& __x) const {
                return _tree.lower_bound(__x);
            }

            iterator
            upper_bound(const key_type& __x) {
                return _tree.upper_bound(__x);
            }

            const_iterator
            upper_bound(const key_type& __x) const {
                return _tree.upper_bound(__x);
            }

            ft::pair<iterator, iterator>
            equal_range(const key_type& __x) {
                return _tree.equal_range(__x);
            }

            ft::pair<const_iterator, const_iterator>
            equal_range(const key_type& __x) const {
                return _tree.equal_range(__x);
            }
    };

    #define _MAP_OPE_MACRO(OP) \
        __x._tree OP __y._tree

    template <class _Key, class _T, class _Compare, class _Alloc>
    bool
    operator==(const map<_Key, _T, _Compare, _Alloc>& __x,
            const map<_Key, _T, _Compare, _Alloc>& __y) {
        return _MAP_OPE_MACRO(==);
    }

    template <class _Key, class _T, class _Compare, class _Alloc>
    bool
    operator!=(const map<_Key, _T, _Compare, _Alloc>& __x,
            const map<_Key, _T, _Compare, _Alloc>& __y) {
        return _MAP_OPE_MACRO(!=);
    }

    template <class _Key, class _T, class _Compare, class _Alloc>
    bool
    operator<(const map<_Key, _T, _Compare, _Alloc>& __x,
            const map<_Key, _T, _Compare, _Alloc>& __y) {
        return _MAP_OPE_MACRO(<);
    }

    template <class _Key, class _T, class _Compare, class _Alloc>
    bool
    operator>(const map<_Key, _T, _Compare, _Alloc>& __x,
            const map<_Key, _T, _Compare, _Alloc>& __y) {
        return _MAP_OPE_MACRO(>);
    }

    template <class _Key, class _T, class _Compare, class _Alloc>
    bool
    operator<=(const map<_Key, _T, _Compare, _Alloc>& __x,
            const map<_Key, _T, _Compare, _Alloc>& __y) {
        return _MAP_OPE_MACRO(<=);
    }

    template <class _Key, class _T, class _Compare, class _Alloc>
    bool
    operator>=(const map<_Key, _T, _Compare, _Alloc>& __x,
            const map<_Key, _T, _Compare, _Alloc>& __y) {
        return _MAP_OPE_MACRO(>=);
    }

    #undef _MAP_OPE_MACRO

    template <class _Key, class _T, class _Compare, class _Alloc>
    void
    swap(map<_Key, _T, _Compare, _Alloc>& __x,
            map<_Key, _T, _Compare, _Alloc>& __y) {
        __x.swap(__y);
    }
}

#endif // __FT_CONTAINERS__MAP__
