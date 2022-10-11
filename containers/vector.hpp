#ifndef __FT_CONTAINERS_VECTOR__
#define __FT_CONTAINERS_VECTOR__

#include "./iterators.hpp"
#include "./null_ptr.hpp"
#include "./utils.hpp"
#include "./concept_check.hpp"
#include "./alloc_traits.hpp"
#include <iostream>
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

            virtual ~_vector_alloc_base () {};

            pointer _allocate(size_type __n) {
                return _data_allocator.allocate(__n);
            }

            void    _deallocate(pointer __p, size_type __n) {
                if (__p) _data_allocator.deallocate(__p, __n);
            }

            size_type
            inline get_capacity() const {
                return static_cast<size_type>(_capacity - _start);
            }

            size_type
            inline get_assigned_elements_count () const {
                return static_cast<size_type>(_finish - _start);
            }

            allocator_type get_allocator() const { return _data_allocator; }

            size_type
            set_storage(size_type __n, const allocator_type& __Alloc = allocator_type()) {
                try {
                    if (_start) this->expand(__n);
                    else {
                        _data_allocator = __Alloc;
                        _start      = __n ? this->_allocate(__n) : 0;
                        _finish     = __n ? _start : 0;
                        _capacity   = __n ? _start + __n : 0;
                    }
                }
                catch (...) {
                    exit(ERROR_ALLOCATE_MEMORY);
                }
                return __n;
            }

            void
            clear_storage(void) {
                if (_start) {
                    _deallocate(_start, this->get_capacity());
                    _start = 0;
                    _finish = 0;
                    _capacity = 0;
                }
            }
            
            size_type
            size() const {
                return _finish - _start;
            }

            void
            expand(size_type __n) {
                if (this->get_capacity() < __n) {
                    size_type __newCapa = this->capacity_expand_condition(__n);
                    size_type i = 0;
                    try {
                        pointer __tmp = this->_allocate(__newCapa);
                        while (i < this->get_assigned_elements_count()) {
                            *(__tmp + i) = *(this->_start + i);
                            i++;
                        }
                        this->_deallocate(this->_start, this->get_capacity());
                        this->_start = __tmp;
                        this->_capacity = __tmp + __newCapa;
                        this->_finish = __tmp + i;
                    } catch (...) {
                        this->_deallocate(this->_start, __newCapa);
                    }
                }
            }

            void
            init_storage_by_param_from_scratch(size_type __n) {
                try {
                    pointer __tmp = this->_allocate(__n);
                    this->_start = __tmp;
                    this->_capacity = __n;
                    this->_start = __tmp;
                } catch (...) {
                    this->_deallocate(this->_start, __n);
                }
            }

            void
            shrink(size_type __n) {
                size_type i = 0;
                try {
                    pointer __tmp = this->_allocate(__n);
                    while (i < __n) {
                        *(__tmp + i) = *(this->_start + i);
                        i++;
                    }
                    this->_deallocate(this->_start, this->get_capacity());
                    this->_start = __tmp;
                    this->_capacity = __n;
                    this->_finish = __tmp + i;
                } catch (...) {
                    this->_deallocate(this->_start, __n);
                }
            }

            template <bool _isAllowedShrink>
            void
            resize_alloc(size_type __n) {
                if (this->_capacity == 0) {
                    init_storage_by_param_from_scratch(__n);
                } if (this->get_capacity() < __n) {
                    expand(__n);
                }
            }

            template<>
            void
            resize_alloc<true> (size_type __n) {
                if (this->_capacity == 0) {
                    init_storage_by_param_from_scratch(__n);
                } else if (this->get_capacity() < __n) {
                    expand(__n);
                } else {
                    shrink(__n);
                }
            }

        private :
            size_type
            capacity_expand_condition (size_type __n) {
                size_type old_capa = this->get_capacity();
                if (old_capa == 0) {
                    return 1;
                } else if (__n + this->get_assigned_elements_count() < old_capa) {
                    return old_capa;
                } else {
                    return old_capa * 2;
                }
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
                if (!this->_start) this->set_storage(__n, __a);
            }

            ~_vector_base() {
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
            typedef ft::random_access_iterator<pointer>                         iterator;
            typedef ft::random_access_iterator<const_pointer>                   const_iterator;
            typedef ft::reverse_iterator<iterator>                              reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>                        const_reverse_iterator;

        protected :
            using _base::_start;
            using _base::_finish;
            using _base::get_capacity;
            using _base::get_allocator;
            using _base::set_storage;
            using _base::clear_storage;
            using _base::expand;

        public :

            // constructors
            explicit vector(const allocator_type& __a = allocator_type()) : _vector_base<_T, _Alloc>(__a) {
                if (!this->_start) this->set_storage(0, __a);
            };
            
            vector(size_type __n, const value_type& __value = value_type(), const allocator_type& __a = allocator_type()) : _vector_base<_T, _Alloc>(__n, __a) {
                if (!this->_start) this->set_storage(__n, __a);
                while (__n--) { this->push_back(__value); }
            };

            template <class InputIterator>
            vector(InputIterator __first, InputIterator __last, const allocator_type& __a = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) : _vector_base<_T, _Alloc>(__a) {
                difference_type __n = ft::distance(__first, __last);

                if (!this->_start) this->set_storage(__n, __a);
                while (__n--) { this->push_back(*__first++); }
            };

            vector(const vector& __x) : _vector_base<_T, _Alloc>(__x) { *this = __x; }
            
            vector&
            operator= (const vector& __x) {
                if (this != &__x) {
                    this->clear_storage();
                    this->set_storage(__x.size());
                    for (size_type __i = 0; __i < __x.size(); __i++) { this->push_back(__x[__i]); }
                }
                return *this;
            };

            ~vector() {};

            void
            clear(void) {
                this->clear_storage();
            }

            void assign(size_type __n, const value_type& __u) {
                this->clear();
                this->set_storage(__n);
                while (__n--) this->push_back(__u);
            }

            template <class InputIterator>
            void assign(InputIterator __first, InputIterator __last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
                this->clear();
                while (__first != __last) { this->push_back(*__first++); }
            }

            void
			push_back (const value_type& _val) {
                if (this->size() == this->get_capacity()) { this->expand(this->size() + 1); }
                this->get_allocator().construct(this->_finish++, _val);
            }

			void
			pop_back (void) {
				this->get_allocator().destroy(this->_finish--);
            }

            iterator
            insert (const_iterator __pos, const_reference __value) {
                this->expand(this->size() + 1);
                reverse_iterator __first = this->rbegin();
                reverse_iterator __rpos = reverse_iterator(const_iterator(__pos));

                while (__first != __rpos) {
                    *__first = *(__first + 1);
                    ++__first;
                }
                *__rpos = __value;
                return iterator(__rpos);
            }

            // should recode this methods
            // iterator
            // insert (const_iterator __pos, size_type __count, const_reference __value) {
            //     this->expand(this->size() + __count);
            //     reverse_iterator __first = this->rbegin();
            //     reverse_iterator __rpos = reverse_iterator(const_iterator(__pos));

            //     while (__first != __rpos) {
            //         *__first = *(__first + __count);
            //         ++__first;
            //     }
            //     while (__count--) { *__rpos = __value; ++__rpos; }
            //     return iterator(__rpos);
            // }

            // template<class _InputIterator>
            // iterator
            // insert (const_iterator __pos, _InputIterator __first, _InputIterator __last) {
            //     difference_type dif = ft::distance(__first, __last);
            //     this->expand(this->size() + dif);
            //     reverse_iterator __rfirst = this->rbegin();
            //     reverse_iterator __rpos = reverse_iterator(const_iterator(__pos));

            //     while (__rfirst != __rpos) {
            //         *__rfirst = *(__rfirst + dif);
            //         ++__rfirst;
            //     }
            //     while (__first != __last) { *__rpos = *__first; ++__rfirst; ++__first; }
            //     return iterator(__rpos);
            // }

            size_type
            size (void) const {
                return static_cast<size_type>(this->_finish - this->_start);
            }

            size_type
            max_size (void) const {
                return this->get_allocator().max_size();; 
            }

            size_type
            capacity (void) const {
                return this->get_capacity();
            }

            bool
            empty (void) const {
                return (begin() == end());
            }

            void
            resize(size_type __n, value_type __v = value_type()) {
            	this->expand (__n);
				while (this->size() < __n) {
					this->push_back (__v);
				}
				while (__n < this->size()) {
					this->pop_back ();
				}
            }

            void
            reserve(size_type __n) {
                this->expand(__n);
            }

            void
            swap(vector& _x) {
                allocator_type      tmp_data_allocator = _x.get_allocator();
                pointer             tmp_start = _x._start;
                pointer             tmp_finish = _x._finish;
                pointer             tmp_capacity = _x._capacity;

                _x._data_allocator = this->get_allocator();
                _x._start = this->_start;
                _x._finish = this->_finish;
                _x._capacity = this->_capacity;

                this->get_allocator() = tmp_data_allocator;
                this->_start = tmp_start;
                this->_finish = tmp_finish;
                this->_capacity = tmp_capacity;
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
                _range_check(__n);
                return (*this)[__n];
            }

            const_reference
            at (size_type __n) const {
                _range_check(__n);
                return (*this)[__n];
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
                return *(this->end() - 1);
            }

            const_reference
            back (void) const {
                return *(this->end() - 1);
            }


        private :
            void
            _range_check(size_type __n) const {
                if (__n >= this->size()) this->_throw_out_of_range();
            }
    };

    template <class T, class Alloc>
    bool
    operator== (const vector<T,Alloc>& __x, const vector<T,Alloc>& __y) {
        return __x.size() == __y.size() && ft::equal(__x.begin(), __x.end(), __y.begin());
    }

    template <class T, class Alloc>
    bool
    operator!= (const vector<T,Alloc>& __x, const vector<T,Alloc>& __y) {
        return !(__x == __y);
    }

    template <class T, class Alloc>
    bool
    operator<  (const vector<T,Alloc>& __x, const vector<T,Alloc>& __y) {
        return ft::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
    }

    template <class T, class Alloc>
    bool
    operator>  (const vector<T,Alloc>& __x, const vector<T,Alloc>& __y) {
        return ft::lexicographical_compare(__y.begin(), __y.end(), __x.begin(), __x.end());
    }

    template <class T, class Alloc>
    bool
    operator<= (const vector<T,Alloc>& __x, const vector<T,Alloc>& __y) {
        return !(__y < __x);
    }

    template <class T, class Alloc>
    bool
    operator>= (const vector<T,Alloc>& __x, const vector<T,Alloc>& __y) {
        return !(__x < __y);
    }

    template <class T, class Alloc>
    void
    swap (vector<T, Alloc>& __x, vector<T, Alloc>& __y) {
        __x.swap(__y);
    }


} // namespace ft

#endif // __FT_CONTAINERS_VECTOR__
