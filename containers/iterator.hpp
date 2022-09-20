#ifndef __FT_CONTAINERS_ITERATOR__
#define __FT_CONTAINERS_ITERATOR__

#include "./definition.hpp"

__LIBFT_CONTAINERS_START__


template <class Iter>
struct iterator_traits {

};

template <class T>
struct iterator_traits<T*> {

};

template <class T>
struct iterator_traits <const T*> {
    
}


__LIBFT_CONTAINERS_END__

#endif __FT_CONTAINERS_ITERATOR__
