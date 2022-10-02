#ifndef __FT_CONTAINERS_VECTOR__
#define __FT_CONTAINERS_VECTOR__

#include "./definition.hpp"
#include <vector>
#include <exception>
#include <memory>

__LIBFT_CONTAINERS_START__

template <typename _T, typename _Alloc>
class _vector_base {
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
        pointer         _start;
        pointer         _finish;
        pointer         _end_of_storage;


    private :

    public :
        _vector_base() : _start(NULL), _finish(NULL), _end_of_storage(NULL)
        {};

        

};

template <typename _T, typename _Alloc = std::allocator<_T>>
class Vector : public _vector_base {
    public :
        typedef _T                                              value_type;
        typedef _Alloc                                          allocator_type;
        typedef std::size_t                                     size_type;
        typedef std::ptrdiff_t                                  difference_type;
        typedef value_type&                                     reference;
        typedef const value_type&                               const_reference;
        typedef allocator_type::pointer                         pointer;
        typedef allocator_type::const_pointer                   const_pointer;
        typedef ft::Random_access_iterator<value_type>          iterator;
        typedef ft::Random_access_iterator<const value_type>    const_iterator;
        typedef ft::Reverse_iterator<iterator>                  reverse_iterator;
        typedef ft::Reverse_iterator<const_iterator>            const_reverse_iterator;

    protected :

    private :


    public :

}

__LIBFT_CONTAINERS_END__

#endif // __FT_CONTAINERS_VECTOR__