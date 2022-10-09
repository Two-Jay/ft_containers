#ifndef __FT_CONTAINERS_VECTOR__
#define __FT_CONTAINERS_VECTOR__

#include <memory>
#include <cstddef>
#include "iterators.hpp"

namespace ft {
    template <class _Tp, class _Alloc>
    class _vector_alloc_base {
        public :
            typedef _Alloc                                  allocator_type;
            typedef _Tp*                                    pointer;
            typedef std::size_t                             size_type;

            _vector_alloc_base ()
                : _alloc(_Alloc), _start(0), _end_elements(0), _end_storage(0)
            {}

            _vector_alloc_base (const allocator_type& __a)
                : _alloc(__a), _start(0), _end_elements(0), _end_storage(0)
            {}

            allocator_type
            get_allocator() const {
                return this->_alloc;
            }
        
        protected :
            allocator_type                                  _alloc;
            pointer                                         _start;
            pointer                                         _end_elements;
            pointer                                         _end_storage;

            pointer
            _allocate(size_type __n) {
                return _alloc.allocate(__n);
            }
            
            void
            _deallocate(pointer __p, size_type __n) {
                if (__p) _alloc.deallocate(__p, __n);
            }
            
            size_type
            _get_capcity(void) {
                return (_start && _end_storage) ? static_cast<size_type>(_end_storage - _start) : 0; 
            }
    };

    template <class _Tp, class _Alloc>
    class _vector_base : public _vector_alloc_base<_Tp, _Alloc> {
        protected :
            typedef _vector_alloc_base<_Tp, _Alloc>         _Base;
            typedef typename _Base::allocator_type          allocator_type;
            typedef typename _Base::size_type               size_type;

            _vector_base() : _Base() {};
            _vector_base(const allocator_type& __a) : _Base(__a) {};
            _vector_base(size_type __n, const allocator_type& __a) : _Base(__a) {
                this->_start = this->_allocate(__n);
                this->_end_elements = this->_start;
                this->_end_storage = this->_start + __n;
            };

            ~_vector_base() {
                this->_deallocate(this->_start, this->_get_capacity());
            }

            void
            _throw_out_of_range() const {
                throw std::out_of_range("vector");
            }

            void
            _throw_length_error() const {
                throw std::length_error("vector");
            }
            
            void
            _range_check(size_type __n) const {
                if (__n >= this->size()) this->_throw_out_of_range();
            }

            void
            _length_check(size_type __n) const {
                if (__n > this->_get_capcity()) this->_throw_length_error();
            }
    };

    template <class _Tp, class _Alloc>
    class vector : protected _vector_base<_Tp, _Alloc> {
        private :
            typedef _vector_base<_Tp, _Alloc>                                   _Base;
            typedef vector<_Tp, _Alloc>                                         vector_type;

        public :    
            typedef _Tp                                                         value_type;
            typedef _Tp*                                                        pointer;
            typedef const _Tp*                                                  const_pointer;
            typedef _Tp&                                                        reference;
            typedef const _Tp&                                                  const_reference;
            typedef std::ptrdiff_t                                              difference_type;

            typedef typename _Base::size_type                                   size_type;
            typedef typename _Base::allocator_type                              allocator_type;
            typedef ft::random_access_iterator<pointer, vector_type>            iterator;
            typedef ft::random_access_iterator<const_pointer, vector_type>      const_iterator;
            typedef ft::reverse_iterator<iterator>                              reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>                        const_reverse_iterator;

        protected :
            using _Base::_allocate;
            using _Base::_deallocate;
            using _Base::_start;
            using _Base::_end_elements;
            using _Base::_end_storage;

        public :

            vector() : _Base() {}

            explicit vector (const allocator_type& __a = allocator_type()) : _Base(__a) {}

            vector(size_type __n, const_reference __value, const allocator_type& __a = allocator_type()) : _Base(__n, __a) {
                _end_elements = std::uninitialized_fill_n(_start, __n, __value);
            }

            vector (const vector<_Tp, _Alloc>& __v) : _Base(__v.size(), __v.get_allocator()) {
                _end_elements = std::uninitialized_copy(__v.begin(), __v.end(), _start);
            }

            template <class _InputIterator>
            vector (_InputIterator __first, _InputIterator __last, const allocator_type& __a = allocator_type()) : _Base(__a) {
                typedef typename ft::is_integral<_InputIterator>::value        _isInteger;
                _initialize_aux(__first, __last, _isInteger());
            }

            ~vector() {
                this->_deallocate(_start, _end_storage);
            }

            vector_type&
            operator= (const vector_type& __v) {
                if (this != &__v) {
                    const size_type __size = __v.size();
                    if ()
                }                
            }

            allocator_type
            get_allocator() const {
                return _Base::get_allocator();
            }

            /*
            ** element access
            **      : at, operator[], front, back, data;
            */

            reference
            at (size_type __n) {
                this->_range_check(__n);
                return (*this)[__n];                
            }

            const_reference
            at (size_type __n) const {
                this->_range_check(__n);
                return (*this)[__n];
            }

            reference
            operator[] (size_type __n) {
                return *(this->begin() + __n);
            }

            const_reference
            operator[] (size_type __n) const {
                return *(this->begin() + __n);
            }

            reference
            front () {
                return *(this->begin());
            }

            const_reference
            front () const {
                return *(this->begin());
            }

            reference
            back () {
                return *(this->end() - 1);
            }

            const_reference
            back () const {
                return *(this->end() - 1);
            }

            pointer
            data () {
                return this->_start;
            }

            const_pointer
            data () const {
                return this->_start;
            }

            /*
            ** iterators
            **      : begin, end, rbegin, rend
            */

            iterator
            begin() {
                return iterator(_start);
            }
            
            const_iterator
            begin() const {
                return const_iterator(_start);
            }

            iterator
            end() {
                return iterator(_end_elements);
            }
            
            const_iterator
            end() const {
                return const_iterator(_end_elements);
            }

            reverse_iterator
            rbegin() {
                reverse_iterator(this->end());
            }
            
            const_reverse_iterator
            rbegin() const {
                return const_reverse_iterator(this->end());
            }

            reverse_iterator
            rend() {
                return reverse_iterator(this->begin());
            }
            
            const_reverse_iterator
            rend() const {
                return const_reverse_iterator(this->begin());
            }

            /*
            ** capacity
            **      : empty, size, max_size, reserve, capacity
            */

            bool
            empty() const {
                return (this->begin() == this->end());
            }

            size_type
            size() const {
                return static_cast<size_type>(this->end() - this->begin());
            }

            size_type
            max_size() const {
                return this->get_allocator().max_size();
            }
            
            size_type
            capacity() const {
                return _Base::_get_capcity();
            }

            /*
            ** modifiers
            */




        private :
            

            /*
            ** auxiliary functions for vector constructor with iterator parameters;
            */
            template <class _Integer>
            void _initialize_aux(_Integer __n, _Integer __value, true) {
                _start = this->_allocate(__n);
                _end_elements = std::uninitialized_fill_n(_start, __n, __value);
                _end_storage = _start + __n;
            }
            
            template <class _InputIterator>
            void _initialize_aux(_InputIterator __first, _InputIterator __last, false) {
                typedef typename ft::iterator<_InputIterator>::iterator_category    _InputIterCategory;
                _range_initialize(__first, __last, _InputIterCategory());
            }

            template <class _InputIterator>
            void _range_initialize(_InputIterator __first, _InputIterator __last, ft::input_iterator_tag) {
                for (; __first != __last ; __first++) this->push_back(*__first);
            }

            template <class _InputIterator>
            void _range_initialize(_InputIterator __first, _InputIterator __last, ft::forward_iterator_tag) {
                size_type   __dist = ft::distance(__first, __last);
                
                _start = this->_allocate(__n);
                _end_elements = std::uninitialized_copy(__first, __last, _start);
                _end_storage = _start + __n;
            }
            
    };
}


#endif // __FT_CONTAINERS_VECTOR__
