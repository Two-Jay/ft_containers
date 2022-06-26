#ifndef __FT_CONTAINERS_VECTOR__
#define __FT_CONTAINERS_VECTOR__

#include "./definition.hpp"

__LIBFT_CONTAINERS_START__

template <class T, class Alloc = allocator<T>>
class vector {
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