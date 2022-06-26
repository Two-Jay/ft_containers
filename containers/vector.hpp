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

template <class T, class _Alloc>
class _vector_base : protected __vector_base_common {
    
};

template <class T, class _Allocator>
class vector : private _vector_base <T, _Allocator> {
    public:
        typedef _Allocator                          allocator_type;
        typedef allocator_traits<allocator_type>    __alloc_traits;
        typedef size_t                              size_type;
    protected :
        typedef T                                   value_type;
        typedef std::allocator<value_type>          allocator_type;
        typedef allocator_type::reference           reference;
        typedef allocator_type::const_reference     const_reference;
        typedef allocator_type::pointer             pointer;
        typedef allocator_type::const_pointer       const_pointer;
        typedef ptrdiff_t                           difference_type;

    private :
    
};

__LIBFT_CONTAINERS_END__

#endif // __FT_CONTAINERS_VECTOR__