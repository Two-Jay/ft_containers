#ifndef __FT_CONTAINERS_VECTOR__
#define __FT_CONTAINERS_VECTOR__

#include "./definition.hpp"
// #include <vector>
#include <exception>
#include <memory>

__LIBFT_CONTAINERS_START__

class __vector_base_common {
    protected :
        __vector_base_common() {};
        __vector_base_common(const __vector_base_common&) {};
        __vector_base_common& operator=(const __vector_base_common&) {};
        ~__vector_base_common() {};
  
        void __throw_length_error() const {
            throw std::length_error(__ERRMSG_VECTOR_SPECIFIER__);
        };
      
        void __throw_range_error() const {
            throw std::range_error(__ERRMSG_VECTOR_SPECIFIER__);
        };
};

template <class _Tp, class _Allocator>
class _vector_base {
    public:
        typedef _Allocator                                  allocator_type;
        typedef allocator_traits<allocator_type>            __alloc_traits;
        typedef typename __alloc_traits::size_type          size_type;

    protected :
        typedef _Tp                                         value_type;
        typedef value_type&                                 reference;
        typedef const value_type&                           const_reference;
        typedef std::allocator<value_type>                  allocator_type;
        typedef typename __alloc_traits::pointer            pointer;
        typedef typename __alloc_traits::const_pointer      const_pointer;
        typedef typename __alloc_traits::difference_type    difference_type;
        typedef pointer                                     iterator;
        typedef const_pointer                               const_iterator;

        pointer                                             __begin_;
        pointer                                             __end_;
        ft::pair<pointer, allocator_type>                   __end_cap_;
        
        allocator_type& __alloc() _noexcept {
            return __end_cap_.second();
        }

        const allocator_type& __alloc() const _noexcept {
            return __end_cap_.second();
        }

        pointer& __end_cap() _noexcept {
            return __end_cap_.first();
        }
        
        const pointer& __end_cap() const _noexcept {
            return __end_cap_.first();
        }

        _vector_base() {
            
        }
};

template <class T, class _Allocator>
class vector : private _vector_base <T, _Allocator> {

    private :
    
};

__LIBFT_CONTAINERS_END__

#endif // __FT_CONTAINERS_VECTOR__