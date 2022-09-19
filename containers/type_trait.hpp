#ifndef __FT_CONTAINERS__TYPE_TRAIT__
#define __FT_CONTAINERS__TYPE_TRAIT__

#include "definition.hpp"

__LIBFT_CONTAINERS_START__

template<typename T>
struct is_void { static const bool value = false; }

template<>
struct is_void<void> { static const bool value = true; }


__LIBFT_CONTAINERS_END__

#endif // __FT_CONTAINERS__TYPE_TRAIT__