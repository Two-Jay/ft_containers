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
        public :
            typedef _Alloc                                  allocator_type;
            typedef _T                                      value_type;
            typedef _T*                                     pointer;
            typedef size_t                                  size_type;

            allocator_type get_allocate() const { return _data_allocator; };

            _Vector_alloc_base(const allocator_type& __a) : _data_allocator(__a),
                                                            _start(0),
                                                            _finish(0),
                                                            _capacity(0)
            {};

        protected :
            allocator_type   _data_allocator;
            pointer         _start;
            pointer         _finish;
            pointer         _capacity;

            pointer _allocate(size_type __n) {
                return _data_allocator.allocate(__n);
            }

            void    _deallocate(pointer __p, size_type __n) {
                if (__p) _data_allocator.deallocate(__p, __n);
            }

            size_type
            get_capacity() const {
                return _capacity - _start;
            }

            allocator_type get_allocator() const { return _data_allocator; }

            size_type
            set_storage(size_type __n, const allocator_type& __Alloc = allocator_type()) {
                try {
                    _data_allocator = __Alloc;
                    _start      = __n ? _data_allocator.allocate(__n) : 0;
                    _finish     = __n ? _start : 0;
                    _capacity   = __n ? _start + __n : 0;
                }
                catch (...) {
                    exit(ERROR_ALLOCATE_MEMORY);
                }
            }

            void
            clear_storage(void) {
                if (_start) {
                    _data_allocator.deallocate(_start, _capacity);
                    _start = 0;
                    _finish = 0;
                    _capacity = 0;
                }
            }
            
            size_type
            size() const {
                return _finish - _start;
            }

            size_type
            expand(size_type __n) {
                size_type offset;

                if (this->get_capacity() < __n) {
                    try {
                        size_type __new_size = this->get_capacity() * 2 < __n ? __n : this->get_capacity() * 2;
                        value_type* __tmp = _data_allocator.allocate(__new_size);
                        offset = __tmp - _start;

                        size_type __i = 0;
                        size_type __size = this->size();
                        while (__i < __size) {
                            *(__tmp + i) = *(_start + i);
                            ++__i;
                        }

                        this->get_allocate.deallocate(_start, this->get_capacity());
                        _start = __tmp;
                        _finish = __tmp + __size;
                        _capacity = __tmp + __new_size;
                    } catch (...) {
                        exit(ERROR_ALLOCATE_MEMORY);
                    }
                }
                return offset;
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
            using _Vector_alloc_base<_T, _Alloc>::_capacity;


        public :

            // constructors
            explicit Vector(const allocator_type& __a = allocator_type()) : _vector_base<_T, _Alloc>(__a) {
                this->get_allocator().set_storage(0);
            };
            
            Vector(size_type __n, const value_type& __value = value_type(), const allocator_type& __a = allocator_type()) : _vector_base<_T, _Alloc>(__n, __a) {
                this->get_allocator().set_storage(__n);
                while (__n--) { this->push_back(value); }
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


            void assign(size_type __n, const value_type& __u) {
                this->clear();
                this->_start = this->set_storage(__n);
                while (__n--) this->push_back(__u);
            }

            template <class InputIterator>
            void assign(InputIterator __first, InputIterator __last) {
                this->clear();
                for (; __first != __last; __first++) {
                    this->push_back(*__first);
                }
            }

            iterator
            insert(iterator __pos, const value_type& __u) {
                size_type __offset          = this->expand(this->size() + 1);
                reverse_iterator from       = this->rbegin();
                reverse_iterator to         = this->rbegin() - 1;

                __pos += __offset;
                while (from.base() != __pos) {
                    *to++ = *from++;
                }
                *__pos = __u;
                return __pos;
            };
            
            void
            insert(iterator __pos, size_type __n, const value_type& __u) {
                size_type __offset          = this->expand(this->size() + __n);
                reverse_iterator from       = this->rbegin();
                reverse_iterator to         = this->rbegin() - __n;

                __pos += __offset;
                while (from.base() != __pos) {
                    *to++ = *from++;
                }
                while (__n--) {
                    *__pos = __u;
                }
                return __pos;
            };

            template <class InputIterator>
            void insert(iterator __pos, InputIterator __first, InputIterator __last) {
    
            };

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


        //     /*
        //     *   iterators
        //     */

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
