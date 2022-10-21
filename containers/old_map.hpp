#ifndef __FT_CONTAINERS__MAP__
#define __FT_CONTAINERS__MAP__

#include "./rbt_tree.hpp"
#include "./map_iterator.hpp"
#include "./rbt_node.hpp"
#include "./pair.hpp"
#include <memory>


namespace ft
{
    template <
            class Key,
            class T,
            class _Compare = std::less<Key>,
            class _Alloc = std::allocator<ft::pair<Key, T> >
    >
    class map {
        public :
            typedef Key                                                     key_type;
            typedef T                                                       mapped_type;
            typedef ft::pair<Key, T>                                        value_type;
            typedef _Compare                                                key_compare;
            typedef _Alloc                                                  allocator_type;
            typedef typename allocator_type::reference                      reference;
            typedef typename allocator_type::const_reference                const_reference;
            typedef typename allocator_type::pointer                        pointer;
            typedef typename allocator_type::const_pointer                  const_pointer;
            typedef typename allocator_type::size_type                      size_type;
            typedef typename allocator_type::difference_type                difference_type;

            typedef ft::map_iterator<key_type, T, value_type*>              iterator;
            typedef ft::map_iterator<key_type, T, const value_type*>        const_iterator;
            typedef ft::reverse_iterator<iterator>                          reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;


        private :
            typedef ft::rbt_tree<key_type, value_type, _Compare, _Alloc>    _tree_type;

        protected :
			class value_compare : public std::binary_function<value_type, value_type, bool> {
				protected:
					key_compare comp;
				public:
					value_compare() {}
                    value_compare(key_compare _c): comp(_c) {}
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

            typedef ft::map<Key, T, _Compare, _Alloc>     _self_type;


            _tree_type                  _tree;
            allocator_type              _alloc;
            key_compare                 _key_comp;


        public:
            explicit map (const key_compare& _comp = key_compare(),
                        const allocator_type& _alloc = allocator_type())
                : _tree(), _alloc(_alloc), _key_comp(_comp) {}

            template <class InputIterator>
            map (InputIterator _first,
                    InputIterator _last,
                    const key_compare& _comp = key_compare(),
                    const allocator_type& _alloc = allocator_type())
                : _tree(), _alloc(_alloc), _key_comp(_comp) {
                insert(_first, _last);
            }

            map (const map& other) { *this = other; }

            ~map() {}

            map&
            operator=(const map& other) {
                if (this != &other) {
                    this->_tree = other._tree;
                    this->_alloc = other._alloc;
                    this->_key_comp = other._key_comp;
                }
                return *this;
            }

            allocator_type
            get_allocator() const {
                return this->_alloc;
            }


            //     /*
            //     *   Element access
            //     */

            mapped_type&
            at (const key_type& _k) {
                iterator it = this->find(_k);
                if (it == this->end())
                    this->_throw_out_of_range();
                return it->second;
            }

            const mapped_type&
            at (const key_type& _k) const {
                const_iterator it = this->find(_k);
                if (it == this->end())
                    this->_throw_out_of_range();
                return it->second;
            }
            
            mapped_type&
            operator[] (const key_type& _k) {
                ft::pair<iterator, bool> ret = this->insert(ft::make_pair(_k, _tree.find(_k)->_value->second));
                return ret.first->second;
            }

            //     /*
            //     *   Iterators
            //     */

            iterator
            begin() {
                return iterator(_tree.begin());
            }

            const_iterator
            begin() const {
                return const_iterator(_tree.begin());
            }

            iterator
            end() {
                return iterator(_tree.end());
            }

            const_iterator
            end() const {
                return const_iterator(_tree.end());
            }

            reverse_iterator
            rbegin() {
                return reverse_iterator(_tree.end());
            }

            const_reverse_iterator
            rbegin() const {
                return const_reverse_iterator(_tree.end());
            }

            reverse_iterator
            rend() {
                return reverse_iterator(_tree.begin());
            }

            const_reverse_iterator
            rend() const {
                return const_reverse_iterator(_tree.begin());
            }
            
            //     /*
            //     *   Capacity
            //     */

            bool
            empty() const {
                return _tree.size() == 0 ? true : false;
            }

            size_type
            size() const {
                return _tree.size();
            }

            size_type
            max_size() const {
                return _tree.max_size();
            }

            //     /*
            //     *   Modifiers
            //     */

            void
            clear() {
                _tree.clear();
            }

            ft::pair<iterator, bool>
            insert(const value_type& _val) {
                return _tree.insert(_val);
            }

            iterator insert(iterator _pos, const value_type& _val)
            {
                (void) _pos;
                return _tree.insert(_val).first;
            }

            template<class InputIterator>
            void insert(InputIterator _first, InputIterator _last)
            {
                for (;_first != _last; _first++)
                    _tree.insert(value_type(_first->first, _first->second));
            }

            void
            erase(iterator _pos) {
                _tree.erase(_pos->first);
            }

            size_type
            erase(const key_type& _key) {
                return _tree.erase(_key) ? 1 : 0;
            }

            void
            erase(iterator _first, iterator _last) {
                key_type key;
                for (; _first != _last; _first++) {
                    key = _first->first;
                    _tree.erase(key);
                }
            }

            void
            swap(map& other) {
                _tree.swap(other._tree);

                allocator_type tmp_alloc = _alloc;
                key_compare tmp_comp = _key_comp;

                _alloc = other._alloc;
                _key_comp = other._key_comp;

                other._alloc = tmp_alloc;
                other._key_comp = tmp_comp;
            }

            //     /*
            //     *   Lookup
            //     */

            size_type
            count(const key_type& _key) const {
                return _tree.count(_key) != _tree.end() ? 1 : 0;
            }

            iterator
            find(const key_type& _key) {
                return iterator(_tree.find(_key));
            }

            const_iterator
            find(const key_type& _key) const {
                return const_iterator(_tree.find(_key));
            }

            ft::pair<iterator, iterator>
            equal_range(const key_type& _key) {
                return ft::pair<iterator, iterator>(this->lower_bound(_key), this->upper_bound(_key));
            }

            ft::pair<const_iterator, const_iterator>
            equal_range(const key_type& _key) const {
                return ft::pair<const_iterator, const_iterator>(this->lower_bound(_key), this->upper_bound(_key));
            }

            iterator
            lower_bound(const key_type& _key) {
                return iterator(_tree.lower_bound(_key));
            }

            const_iterator
            lower_bound(const key_type& _key) const {
                return const_iterator(_tree.lower_bound(_key));
            }

            iterator
            upper_bound(const key_type& _key) {
                return iterator(_tree.upper_bound(_key));
            }

            const_iterator
            upper_bound(const key_type& _key) const {
                return const_iterator(_tree.upper_bound(_key));
            }

            //     /*
            //     *   Observers
            //     */

            key_compare
            key_comp() const {
                return _key_comp;
            }

            value_compare
            value_comp() const {
                return value_compare(_Compare());
            }

        private :
            void
            print_tree() {
                _tree.print();
            }

            void    _throw_out_of_range() const {
                throw std::out_of_range("map");
            }

            void    _throw_length_error() const {
                throw std::length_error("map");
            }
    };

    template <class _Key, class _T, class _Compare, class _Alloc>
    bool
    operator==(const map<_Key, _T, _Compare, _Alloc>& __x,
            const map<_Key, _T, _Compare, _Alloc>& __y) {
        return __x.size() == __y.size() && ft::equal(__x.begin(), __x.end(), __y.begin());
    }

    template <class _Key, class _T, class _Compare, class _Alloc>
    bool
    operator!=(const map<_Key, _T, _Compare, _Alloc>& __x,
            const map<_Key, _T, _Compare, _Alloc>& __y) {
        return !(__x == __y);
    }

    template <class _Key, class _T, class _Compare, class _Alloc>
    bool
    operator<(const map<_Key, _T, _Compare, _Alloc>& __x,
            const map<_Key, _T, _Compare, _Alloc>& __y) {
        return ft::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
    }

    template <class _Key, class _T, class _Compare, class _Alloc>
    bool
    operator>(const map<_Key, _T, _Compare, _Alloc>& __x,
            const map<_Key, _T, _Compare, _Alloc>& __y) {
        return __y < __x;
    }

    template <class _Key, class _T, class _Compare, class _Alloc>
    bool
    operator<=(const map<_Key, _T, _Compare, _Alloc>& __x,
            const map<_Key, _T, _Compare, _Alloc>& __y) {
        return !(__y < __x);
    }

    template <class _Key, class _T, class _Compare, class _Alloc>
    bool
    operator>=(const map<_Key, _T, _Compare, _Alloc>& __x,
            const map<_Key, _T, _Compare, _Alloc>& __y) {
        return !(__x < __y);
    }

    template <class _Key, class _T, class _Compare, class _Alloc>
    void
    swap(map<_Key, _T, _Compare, _Alloc>& __x,
            map<_Key, _T, _Compare, _Alloc>& __y) {
        __x.swap(__y);
    }


}

#endif // __FT_CONTAINERS__MAP__
