#ifndef __FT_CONTAINERS_IS_INTEGRAL__
#define __FT_CONTAINERS_IS_INTEGRAL__

#include "./definition.hpp"

#define SHOW(...) std::cout << std::setw(29) << #__VA_ARGS__ << " == " << __VA_ARGS__ << '\n'

__LIBFT_CONTAINERS_START__

template<class T>
const bool is_integral<T>::value

__LIBFT_CONTAINERS_END__


#endif // __FT_CONTAINERS_IS_INTEGRAL__