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
    class _vector_alloc_base {
        public :
            typedef _Alloc                                  allocator_type;
            typedef _T                                      value_type;
            typedef _T*                                     pointer;
            typedef size_t                                  size_type;

            allocator_type get_allocate() const { return _data_allocator; };

            _vector_alloc_base(const allocator_type& __a) : _data_allocator(__a),
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
                    _start      = __n ? this->_allocate(__n) : 0;
                    _finish     = __n ? _start : 0;
                    _capacity   = __n ? _start + __n : 0;
                }
                catch (...) {
                    exit(ERROR_ALLOCATE_MEMORY);
                }
                return __n;
            }

            void
            clear_storage(void) {
                if (_start) {
                    _deallocate(_start, get_capacity() * sizeof(value_type));
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
                size_type offset = 0;

                if (this->get_capacity() < __n) {
                    try {
                        size_type __new_size = this->get_capacity() * 2 < __n ? __n : this->get_capacity() * 2;
                        value_type* __tmp = this->get_allocator().allocate(__new_size);
                        offset = __tmp - _start;

                        size_type __i = 0;
                        size_type __size = this->size();
                        while (__i < __size) {
                            *(__tmp + __i) = *(_start + __i);
                            ++__i;
                        }

                        this->get_allocator().deallocate(_start, this->get_capacity());
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
    class _vector_base : public _vector_alloc_base<_T, _Alloc> {
        public :
            typedef _vector_alloc_base<_T, _Alloc>              _base;
            typedef typename _base::allocator_type              allocator_type;
            typedef size_t                                      size_type;

        protected :
            _vector_base(const allocator_type& __a) : _base(__a) {};
            _vector_base(size_type __n, const allocator_type& __a) : _base(__a) {
                this->set_storage(__n);
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
    class vector : public _vector_base<_T, _Alloc> {
        private :
            typedef typename _vector_base<_T, _Alloc>::_base                    _base;
            typedef vector<_T, _Alloc>                                          vector_type;

        public :
            typedef _T                                                          value_type;
            typedef const _T                                                    const_value_type;
            typedef _Alloc                                                      allocator_type;
            typedef std::size_t                                                 size_type;
            typedef std::ptrdiff_t                                              difference_type;
            typedef value_type&                                                 reference;
            typedef const value_type&                                           const_reference;
            typedef value_type*                                                 pointer;
            typedef const_value_type*                                           const_pointer;
            typedef ft::random_access_iterator<pointer, vector_type>            iterator;
            typedef ft::random_access_iterator<const_pointer, vector_type>      const_iterator;
            typedef ft::reverse_iterator<iterator>                              reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>                        const_reverse_iterator;

        protected :
            using _base::_start;
            using _base::_finish;
            using _base::get_capacity;
            using _base::set_storage;
            using _base::clear_storage;
            using _base::size;
            using _base::expand;

        public :

            // constructors
            explicit vector(const allocator_type& __a = allocator_type()) : _vector_base<_T, _Alloc>(__a) {
                this->set_storage(0);
            };
            
            vector(size_type __n, const value_type& __value = value_type(), const allocator_type& __a = allocator_type()) : _vector_base<_T, _Alloc>(__n, __a) {
                this->set_storage(__n);
                while (__n--) { this->push_back(__value); }
            };

            template <class InputIterator>
            vector(InputIterator __first, InputIterator __last, const allocator_type& __a = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) : _vector_base<_T, _Alloc>(__a) {
                difference_type __n = ft::distance(__first, __last);

                this->set_storage(__n);
                while (__n--) { this->push_back(*__first++); }
            };

            // Vector(const Vector& __x) : _vector_base<_T, _Alloc>(__x._data_allocator) {
            //     this->allocate(__x.size());
            //     for (size_type __i = 0; __i < __x.size(); __i++) { this->push_back(__x[__i]); }
            // };

            vector(const vector& __x) { *this = __x; } // which one is better?
            
            vector&
            operator= (const vector& __x) {
                if (this != &__x) {
                    this->clear();
                    this->get_allocator().set_storage(__x.size());
                    for (size_type __i = 0; __i < __x.size(); __i++) { this->push_back(__x[__i]); }
                }
                return *this;
            };
            
            ~vector() {
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

            void
			push_back (const value_type& _val) {
				expand(size() + 1);
				this->get_allocator().construct(_finish, _val);
				++_finish;
			}

			void
			pop_back (void) {
				allocator_type().destroy(const_cast<pointer>(_start + _finish));
				--_finish;
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
                size_t __n = ft::distance(__first, __last);
                size_type __offset          = this->expand(this->size() + __n);
                reverse_iterator from       = this->rbegin();
                reverse_iterator to         = this->rbegin() - __n;

                __pos += __offset;
                while (from.base() != __pos) {
                    *to++ = *from++;
                }
                while (__first != __last) {
                    *__pos++ = *__first++;
                }
                return __pos;
            };

            size_type
            size (void) const {
                return static_cast<size_type>(this->end() - this->begin());
            }

            size_type
            max_size (void) const {
                // size_type(-1) / sizeof(value_type)
                return this->allocator_type().max_size(); 
            }

            size_type
            capacity (void) const {
                return static_cast<size_type>(const_iterator(this->_end_of_storage) - this->begin());
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
