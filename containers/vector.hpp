#ifndef __FT_CONTAINERS_VECTOR__
#define __FT_CONTAINERS_VECTOR__

#include "./iterators.hpp"
#include "./null_ptr.hpp"
#include <exception>
#include <memory>

#define ERROR_ALLOCATE_MEMORY 134

namespace ft {
    // this class deals with error exception and alloc / dealloc logic
    template <typename _T, typename _Alloc, typename _IsStatic>
    class _Vector_alloc_base {
        typedef _Alloc                                  allocator_type;
        typedef _T                                      value_type;
        typedef _T*                                     pointer;
        typedef size_t                                  size_type;

        allocator_type get_allocate() const { return _data_allocator; };

        protected :
            allocator_type   _data_allocator;
            pointer         _start;
            pointer         _finish;
            pointer         _end_of_storage;

            _Vector_alloc_base(const allocator_type& __a) : _data_allocator(__a),
                                                            _start(ft::nullptr_t),
                                                            _finish(ft::nullptr_t),
                                                            _end_of_storage(ft::nullptr_t)
            {};

            pointer _allocate(size_type __n) {
                return _data_allocator.allocate(__n);
            }

            void    _deallocate(pointer __p, size_type __n) {
                if (__p) _data_allocator.deallocate(__p, __n);
            }
    };

    template <typename _T, typename _Alloc>
    class _Vector_alloc_base<_T, _Alloc, true> {
        typedef _Alloc                                  allocator_type;
        typedef _T                                      value_type;
        typedef _T*                                     pointer;
        typedef size_t                                  size_type;

        allocator_type get_allocate() const { return allocator_type(); };

        protected :
            pointer         _start;
            pointer         _finish;
            pointer         _end_of_storage;

            _Vector_alloc_base(const allocator_type& __a) :     _start(ft::nullptr_t),
                                                                _finish(ft::nullptr_t),
                                                                _end_of_storage(ft::nullptr_t)
            {};

            pointer _allocate(size_type __n) {
                return _Alloc.allocate(__n);
            }

            void    _deallocate(pointer __p, size_type __n) {
                if (__p) _Alloc.deallocate(__p, __n);
            }
    };
    

    template <typename _T, typename _Alloc>
    class _vector_base : public _vector_alloc_base<_T, _Alloc, true> {
        public :
            typedef _Alloc                                  allocator_type;
            typedef typename _Alloc::value_type             value_type;
            typedef typename _Alloc::pointer                pointer;
            typedef typename _Alloc::const_pointer          const_pointer;
            typedef typename _Alloc::reference              reference;
            typedef typename _Alloc::const_reference        const_reference;
            typedef typename _Alloc::size_type              size_type;
            typedef typename _Alloc::difference_type        difference_type;

        protected :
            allocator_type   _data_allocator;
            pointer         _C;
            pointer         _end_of_storage;

            void    _throw_out_of_range() const {
                throw std::out_of_range("vector");
            }

            void    _throw_length_error() const {
                throw std::length_error("vector");
            }
    };

    template <typename _T, typename _Alloc = std::allocator<_T> >
    class Vector : public _vector_base<_T, _Alloc> {
        public :
            typedef _T                                                          value_type;
            typedef _Alloc                                                      allocator_type;
            typedef Vector<_T, _Alloc>                                          vector_type;
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


            // constructors
            explicit Vector(const allocator_type& __a = allocator_type()) : _vector_base<_T, _Alloc>(__a) {
                this->allocate(0);
            };

            template <class InputIterator>
            Vector(InputIterator __first, InputIterator __last, const allocator_type& __a = allocator_type()) : _vector_base<_T, _Alloc>(__a) {
                difference_type __n = ft::distance(__first, __last);
                
                this->allocate(__n);
                while (__n--) { this->push_back(*__first++); }
            };

            // Vector(const Vector& __x) : _vector_base<_T, _Alloc>(__x._data_allocator) {
            //     this->allocate(__x.size());
            //     for (size_type __i = 0; __i < __x.size(); __i++) { this->push_back(__x[__i]); }
            // };

            Vector(const Vector& __x) { *this = _x; } // 둘 중에 뭐가 맞을까...
            
            Vector&
            operator= (const Vector& __x) {
                if (this != &__x) {
                    this->clear();
                    this->allocate(__x.size());
                    for (size_type __i = 0; __i < __x.size(); __i++) { this->push_back(__x[__i]); }
                }
                return *this;
            };
            
            ~Vector() {
                this->clear();
                this->allocator_type().deallocate();
            };

        private :
            size_type           _size_;

            size_type
            size (void) const {
                return this->_size_;
            }

            size_type
            max_size (void) const {
                return this->allocator_type().max_size();
            }

            size_type
            allocate(size_type __n, const allocator_type& _Alloc = allocator_type()) {
                try {
                    _C      = __n ? this->allocate(__n) : 0;
                    _size   = 0;
                    _end_of_storage = _start + __n;
                }
                catch (...) {
                    exit(ERROR_ALLOCATE_MEMORY);
                }
            }
    };
} // namespace ft

#endif // __FT_CONTAINERS_VECTOR__