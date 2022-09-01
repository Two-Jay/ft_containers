/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:27:05 by jekim             #+#    #+#             */
/*   Updated: 2022/07/09 20:00:00 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_CONTAINERS_VECTOR__
#define __FT_CONTAINERS_VECTOR__

template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T> >
> class map
{
    // member_variable

    // key_type	Key
    // mapped_type	T
    // value_type	std::pair<const Key, T>
    // size_type	Unsigned integer type (usually std::size_t)
    // difference_type	Signed integer type (usually std::ptrdiff_t)
    // key_compare	Compare
    // allocator_type	Allocator
    // reference	value_type&
    // const_reference	const value_type&
    // pointer    Allocator::pointer
    // const_pointer    Allocator::const_pointer
    // iterator	LegacyBidirectionalIterator to value_type
    // const_iterator	LegacyBidirectionalIterator to const value_type
    // reverse_iterator	std::reverse_iterator<iterator>
    // const_reverse_iterator	std::reverse_iterator<const_iterator>

    explicit map map();
    explicit map(const Compare& comp);
    explicit map(const map& x);
    map& operator=(const map& x);
    ~map();

    // member_function
    size_type size() const;
    size_type max_size() const;
    bool empty() const;
    allocator_type get_allocator() const;


    // iterator
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    
    // Modified member functions
    std::pair<iterator, bool> insert(const value_type& value);
    template< class InputIt >
    void insert( InputIt first, InputIt last );
    size_type erase(const key_type& k);
    void erase(iterator position);
    void erase(iterator first, iterator last);
    void clear();
    void swap(map& x);

    // lookup
    iterator find(const key_type& k);
    const_iterator find(const key_type& k) const;
    size_type count(const key_type& k) const;
    std::pair<iterator, iterator> equal_range(const key_type& k);
    std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const;
    iterator lower_bound(const key_type& k);
    const_iterator lower_bound(const key_type& k) const;
    iterator upper_bound(const key_type& k);
    const_iterator upper_bound(const key_type& k) const;

    std::map<Key,T,Compare,Allocator>::key_compare key_comp() const;
    std::map<Key,T,Compare,Allocator>::value_compare value_comp() const;
};
#endif //__FT_CONTAINERS_VECTOR__