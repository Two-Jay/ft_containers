#ifndef __FT_CONTAINERS_COMPRESSED_PAIR__
#define __FT_CONTAINERS_COMPRESSED_PAIR__

#include "definition.hpp"

__LIBFT_CONTAINERS_START__

// Tag used to default initialize one or both of the pair's elements.
struct __default_init_tag {};
struct __value_init_tag {};

template<class _T,
        int _Idx,
        bool _CanBeEmptyBase = is_empty<T>::value && !__libcpp_is_final<T>::value>
struct __compressed_pair_elem {
    typedef _T                  _ParamT;
    typedef _T&                 reference;
    typedef const _T&           const_reference;

    __compressed_pair_elem(__default_init_tag) {}
    __compressed_pair_elem(__value_init_tag) : __value_() {}
    __compressed_pair_elem(__value_init_tag, _ParamT) : __value_(_ParamT) {};

    private:
        _Tp                     __value_;
}


template<class T1, class T2>
class __compressed_pair : 
			public __compressed_pair_elem(__value_init_tag, T1),
			public __compressed_pair_elem(__value_init_tag, T2)
{
    public :
		typedef T1												first_type;
		typedef T2												second_type;
		typedef typename 
}

__LIBFT_CONTAINERS_END__

#endif // __FT_CONTAINERS_COMPRESSED_PAIR__

template <class T1, class T2>
class compressed_pair
{
public:
    typedef T1                                                 first_type;
    typedef T2                                                 second_type;
    typedef typename call_traits<first_type>::param_type       first_param_type;
    typedef typename call_traits<second_type>::param_type      second_param_type;
    typedef typename call_traits<first_type>::reference        first_reference;
    typedef typename call_traits<second_type>::reference       second_reference;
    typedef typename call_traits<first_type>::const_reference  first_const_reference;
    typedef typename call_traits<second_type>::const_reference second_const_reference;

             compressed_pair() : base() {}
             compressed_pair(first_param_type x, second_param_type y);
    explicit compressed_pair(first_param_type x);
    explicit compressed_pair(second_param_type y);

    compressed_pair& operator=(const compressed_pair&);

    first_reference       first();
    first_const_reference first() const;

    second_reference       second();
    second_const_reference second() const;

    void swap(compressed_pair& y);
};