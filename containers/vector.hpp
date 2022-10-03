#ifndef __FT_CONTAINERS_VECTOR__
#define __FT_CONTAINERS_VECTOR__

#include "./iterators.hpp"
#include "./null_ptr.hpp"
#include "./alloc_traits.hpp"
#include <exception>
#include <memory>
#include <vector>

#define ERROR_ALLOCATE_MEMORY 134

namespace ft {

    template <typename _T, typename _Alloc>
    class _Vector_alloc_base {
        typedef _Alloc                                  allocator_type;
        typedef _T                                      value_type;
        typedef _T*                                     pointer;
        typedef size_t                                  size_type;

        allocator_type get_allocate() const { return _data_allocator; };

        _Vector_alloc_base(const allocator_type& __a) : _data_allocator(__a),
                                                        _start(0),
                                                        _finish(0),
                                                        _end_of_storage(0)
        {};

        protected :
            allocator_type   _data_allocator;
            pointer         _start;
            pointer         _finish;
            pointer         _end_of_storage;
            size_type       _size;
            size_type       _capacity;

            pointer _allocate(size_type __n) {
                return _data_allocator.allocate(__n);
            }

            void    _deallocate(pointer __p, size_type __n) {
                if (__p) _data_allocator.deallocate(__p, __n);
            }

            allocator_type get_allocator() const { return _data_allocator; }

            size_type
            set_storage(size_type __n, const allocator_type& __Alloc = allocator_type()) {
                try {
                    _start      = __n ? _data_allocator.allocate(__n) : 0;
                    _finish     = __n ? _start + __n : 0;
                    _size       = __n ? __n : 0;
                    _capacity   = __n ? _start + __n : 0;
                }
                catch (...) {
                    exit(ERROR_ALLOCATE_MEMORY);
                }
            }

            void
            clear_storage(void) {
                if (_start) {
                    _data_allocator.deallocate(_start, _size);
                    _start = 0;
                    _finish = 0;
                    _end_of_storage = 0;
                    _size = 0;
                    _capacity = 0;
                }
            }
    };

    template <typename _T, typename _Alloc>
    class _vector_base : public _Vector_alloc_base<_T, _Alloc> {
        public :
            typedef typename _Vector_alloc_base<_T, _Alloc>  _base;
            typedef typename _base::allocator_type           allocator_type;

        protected :
            _vector_base(const allocator_type& __a) : _base(__a) {};
            _vector_base(size_type __n, const allocator_type& __a) : _base(__a) {
                this->_start = this->set_storage(__n);
                this->_finish = this->_start;
                this->_end_of_storage = this->_start + __n;
            };

            ~_vector_base() {
                this->clear_storage();
            };
        
            void    _throw_out_of_range() const {
                throw std::out_of_range("vector");
            }

            void    _throw_length_error() const {
                throw std::length_error("vector");
            }
    };

    template <typename _T, typename _Alloc = std::allocator<_T> >
    class Vector : public _vector_base<_T, _Alloc> {
        private :
            typedef _vector_base<_T, _Alloc>::_base                             _base;
            typedef Vector<_T, _Alloc>                                          vector_type;

        public :
            typedef _T                                                          value_type;
            typedef _Alloc                                                      allocator_type;
            typedef std::size_t                                                 size_type;
            typedef std::ptrdiff_t                                              difference_type;
            typedef value_type&                                                 reference;
            typedef const value_type&                                           const_reference;
            typedef typename allocator_type::pointer                            pointer;
            typedef typename allocator_type::const_pointer                      const_pointer;
            typedef ft::Random_access_iterator<value_type, vector_type>         iterator;
            typedef ft::Random_access_iterator<const value_type, vector_type>   const_iterator;
            typedef ft::Reverse_iterator<iterator>                              reverse_iterator;
            typedef ft::Reverse_iterator<const_iterator>                        const_reverse_iterator;

        protected :
            using _Vector_alloc_base<_T, _Alloc>::_start;
            using _Vector_alloc_base<_T, _Alloc>::_finish;
            using _Vector_alloc_base<_T, _Alloc>::_end_of_storage;
            usign _Vector_alloc_base<_T, _Alloc>::_allocate;
            usign _Vector_alloc_base<_T, _Alloc>::_deallocate;


        public :

            // constructors
            explicit Vector(const allocator_type& __a = allocator_type()) : _vector_base<_T, _Alloc>(__a) {
                this->get_allocator().set_storage(0);
            };

            Vector(size_type __n, const value_type& __value = value_type(), const allocator_type& __a = allocator_type()) : _vector_base<_T, _Alloc>(__n, __a) {
                this->get_allocator().set_storage(__n);
                for (size_type i = 0; i < __n; i++)
                    this->push_back(__value);
            };    

            template <class InputIterator>
            Vector(InputIterator __first, InputIterator __last, const allocator_type& __a = allocator_type()) : _vector_base<_T, _Alloc>(__a) {
                difference_type __n = ft::distance(__first, __last);
                
                this->get_allocator().set_storage(__n);
                while (__n--) { this->push_back(*__first++); }
            };

            // Vector(const Vector& __x) : _vector_base<_T, _Alloc>(__x._data_allocator) {
            //     this->allocate(__x.size());
            //     for (size_type __i = 0; __i < __x.size(); __i++) { this->push_back(__x[__i]); }
            // };

            Vector(const Vector& __x) { *this = __x; } // which one is better?
            
            Vector&
            operator= (const Vector& __x) {
                if (this != &__x) {
                    this->clear();
                    this->get_allocator().set_storage(__x.size());
                    for (size_type __i = 0; __i < __x.size(); __i++) { this->push_back(__x[__i]); }
                }
                return *this;
            };
            
            ~Vector() {
                this->clear();
            };

            void
            clear(void) {
                this->clear_storage();
            }


            size_type
            size (void) const {
                return size_type(this->end() - this->begin());
            }

            size_type
            max_size (void) const {
                // size_type(-1) / sizeof(value_type)
                return this->allocator_type().max_size(); 
            }

            size_type
            capacity (void) const {
                return size_type(const_iterator(this->_end_of_storage) - this->begin());
            }

            bool
            empty (void) const {
                return (begin() == end());
            }

            void
            resize(size_type __n) {
                resize(__n, this->value_type);
            }


            /*
            *   iterators
            */

            iterator
            begin (void) {
                return iterator(this->_start);
            }

            const_iterator
            begin (void) const {
                return const_iterator(this->_start);
            }

            iterator
            end (void) {
                return iterator(this->_finish);
            }

            const_iterator
            end (void) const {
                return const_iterator(this->_finish);
            }

            reverse_iterator
            rbegin (void) {
                return reverse_iterator(end());
            }

            const_reverse_iterator
            rbegin (void) const {
                return const_reverse_iterator(end());
            }

            reverse_iterator
            rend (void) {
                return reverse_iterator(begin());
            }

            const_reverse_iterator
            rend (void) const {
                return const_reverse_iterator(begin());
            }

        //     /*
        //     *   element access
        //     */

            reference
            operator[] (size_type __n) {
                return *(this->begin() + __n);
            }

            const_reference
            operator[] (size_type __n) const {
                return *(this->begin() + __n);
            }

            reference
            at (size_type __n) {
                if (__n >= this->_size_) { this->_throw_out_of_range(); }
                return *(this->begin() + __n);
            }

            const_reference
            at (size_type __n) const {
                if (__n >= this->_size_) { this->_throw_out_of_range(); }
                return *(this->begin() + __n);
            }

            reference
            front (void) {
                return *(this->begin());
            }

            const_reference
            front (void) const {
                return *(this->begin());
            }

            reference
            back (void) {
                return *(this->begin() + this->_size_ - 1);
            }

            const_reference
            back (void) const {
                return *(this->begin() + this->_size_ - 1);
            }
    };
} // namespace ft

#endif // __FT_CONTAINERS_VECTOR__
