#ifndef __FT_CONTAINERS__SET__
#define __FT_CONTAINERS__SET__

#include "set_iterator.hpp"
#include "./rbt_tree.hpp"
#include "./pair.hpp"
#include <memory>

namespace ft
{
    template <class Key, class Compare = std::less<Key>, class Alloc = std::allocator<Key> >
    class set
    {
        public :
            typedef Key                                                     key_type;
            typedef Key                                                     value_type;
            typedef Compare                                                 key_compare;
            typedef Compare                                                 value_compare;
            typedef Alloc                                                   allocator_type;
            typedef typename allocator_type::reference                      reference;
            typedef typename allocator_type::const_reference                const_reference;
            typedef typename allocator_type::pointer                        pointer;
            typedef typename allocator_type::const_pointer                  const_pointer;
            typedef typename allocator_type::size_type                      size_type;
            typedef typename allocator_type::difference_type                difference_type;

            typedef set_iterator<Key, bool, const value_type*>              iterator;
            typedef set_iterator<Key, bool, const value_type*>              const_iterator;
            typedef ft::reverse_iterator<iterator>                          reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;

        protected :
            typedef rbt_tree<key_type, bool, key_compare, allocator_type>       _tree_type;

            _tree_type      _tree;            
            key_compare     _comp;
            allocator_type  _alloc;

        public :

            set() : _tree(), _comp(key_compare()), _alloc(allocator_type()) {}

            set(const Compare& comp, const allocator_type& alloc = allocator_type())
                : _tree(), _comp(comp), _alloc(alloc) {}

            template <class InputIterator>
            set(InputIterator first, InputIterator last, const Compare& comp = Compare(), const allocator_type& alloc = allocator_type())
                : _tree(), _comp(comp), _alloc(alloc)
            {
                this->insert(first, last);
            }

            set(const set& x) { *this = x; }

            ~set() {}

            set&
            operator=(const set& x)
            {
                if (this != &x) {
                    this->_tree = x._tree;
                    this->_comp = x._comp;
                    this->_alloc = x._alloc;
                }
                return *this;
            }

            allocator_type
            get_allocator() const {
                return this->_alloc;
            }

            iterator
            begin() {
                return iterator(this->_tree.begin());
            }

            const_iterator
            begin() const {
                return const_iterator(this->_tree.begin());
            }

            iterator
            end() {
                return iterator(this->_tree.end());
            }

            const_iterator
            end() const {
                return const_iterator(this->_tree.end());
            }

            reverse_iterator
            rbegin() {
                return reverse_iterator(this->_tree.end());
            }

            const_reverse_iterator
            rbegin() const {
                return const_reverse_iterator(this->_tree.end());
            }

            reverse_iterator
            rend() {
                return reverse_iterator(this->_tree.begin());
            }

            const_reverse_iterator
            rend() const {
                return const_reverse_iterator(this->_tree.begin());
            }

            bool
            empty() const {
                return this->_tree.size() == 0;
            }

            size_type
            size() const {
                return this->_tree.size();
            }

            size_type
            max_size() const {
                return this->_alloc.max_size();
            }

            ft::pair<iterator, bool>
            insert(const value_type& val) {
                return _tree.insert(ft::pair<value_type, bool>(val, true));
            }

            iterator
            insert(iterator pos, const value_type& val) {
                (void) pos;
                return this->_tree.insert(ft::pair<value_type, bool>(val, true)).first;
            }

            template <class InputIterator>
            void
            insert(InputIterator first, InputIterator last) {
                while (first != last) {
                    this->_tree.insert(ft::pair<value_type, bool>(*first, true));
                    ++first;
                }
            }

            void
            erase(iterator pos) {
                this->_tree.erase(*pos);
            }

            size_type
            erase(const key_type& key) {
                return this->_tree.erase(key);
            }

            void
            erase(iterator first, iterator last) {
                while (first != last) {
                    key_type key = *first;
                    ++first;
                    this->erase(key);
                }
            }

            void
            swap(set& x) {
                this->_tree.swap(x._tree);

                key_compare tmp_comp = this->_comp;
                allocator_type tmp_alloc = this->_alloc;
                this->_comp = x._comp;
                this->_alloc = x._alloc;
                x._comp = tmp_comp;
                x._alloc = tmp_alloc;
            }

            void
            clear() {
                this->_tree.clear();
            }

            key_compare
            key_comp() const {
                return this->_comp;
            }

            value_compare
            value_comp() const {
                return value_compare(this->_comp);
            }

            iterator
            find(const key_type& key) {
                return iterator(this->_tree.find(key));
            }

            const_iterator
            find(const key_type& key) const {
                return const_iterator(this->_tree.find(key));
            }

            size_type
            count(const key_type& key) const {
                return const_iterator(this->_tree.find(key)) != this->end() ? 1 : 0;
            }

            iterator
            lower_bound(const key_type& key) {
                return iterator(this->_tree.lower_bound(key));
            }

            const_iterator
            lower_bound(const key_type& key) const {
                return const_iterator(this->_tree.lower_bound(key));
            }

            iterator
            upper_bound(const key_type& key) {
                return iterator(this->_tree.upper_bound(key));
            }

            const_iterator
            upper_bound(const key_type& key) const {
                return const_iterator(this->_tree.upper_bound(key));
            }

            ft::pair<iterator, iterator>
            equal_range(const key_type& key) {
                return ft::pair<iterator, iterator>(this->lower_bound(key), this->upper_bound(key));
            }

            ft::pair<const_iterator, const_iterator>
            equal_range(const key_type& key) const {
                return ft::pair<const_iterator, const_iterator>(this->lower_bound(key), this->upper_bound(key));
            }
    };

    template <class Key, class Compare, class Alloc>
    bool
    operator==(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
        return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <class Key, class Compare, class Alloc>
    bool
    operator!=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
        return !(lhs == rhs);
    }

    template <class Key, class Compare, class Alloc>
    bool
    operator<(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class Key, class Compare, class Alloc>
    bool
    operator>(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
        return rhs < lhs;
    }

    template <class Key, class Compare, class Alloc>
    bool
    operator<=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
        return !(rhs < lhs);
    }

    template <class Key, class Compare, class Alloc>
    bool
    operator>=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
        return !(lhs < rhs);
    }
}

#endif // __FT_CONTAINERS__SET__
