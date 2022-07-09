#ifndef __FT_CONTAINERS_VECTOR__
#define __FT_CONTAINERS_VECTOR__

#include "./definition.hpp"

__LIBFT_CONTAINERS_START__

class __vector_base_common {
    protected :
        __vector_base_common() {};
        __vector_base_common(const __vector_base_common&) {};
        __vector_base_common& operator=(const __vector_base_common&) {};
        ~__vector_base_common() {};
        
        void __throw_length_error() const {
            throw std::length_error("exception from [ft::vector] : length error");
        }

        void __throw_out_of_range() const {
            throw std::out_of_range("exception from [ft::vector] : out of range");
        }
};

template <class T, class _Allocator>
class _vector_base : protected __vector_base_common {
    public:
        typedef _Allocator                                  allocator_type;
        typedef allocator_traits<allocator_type>            __alloc_traits;
        typedef typename __alloc_traits::size_type          size_type;
    protected :
        typedef T                                           value_type;
        typedef std::allocator<value_type>                  allocator_type;
        typedef value_type&                                 reference;
        typedef const value_type&                           const_reference;
        typedef typename __alloc_traits::pointer            pointer;
        typedef typename __alloc_traits::const_pointer      const_pointer;
        typedef typename __alloc_traits::difference_type    difference_type;
        typedef pointer                                     iterator;
        typedef const_pointer                               const_iterator;

        pointer                                             __begin_;
        pointer                                             __end_;
        ft::__conpressed_pair<pointer, allocator_type>      __end_cap_;
        
};

template <class T, class _Allocator>
class vector : private _vector_base <T, _Allocator> {

    private :
    
};

__LIBFT_CONTAINERS_END__

#endif // __FT_CONTAINERS_VECTOR__