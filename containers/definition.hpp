#ifndef __FT_CONTAINERS__DEFINITION__
#define __FT_CONTAINERS__DEFINITION__

#define __LIBFT_CONTAINERS_START__ namespace ft {
#define __LIBFT_CONTAINERS_END__ }

/*
* Error Message Defined as...
* std::__error_function__(__ERRMSG_C_SPECIFIER__)
*/
#define __ERRMSG_VECTOR_SPECIFIER__ "vector"
#define __ERRMSG_MAP_SPECIFIER__ "vector"

#define PUBLIC_API __attribute__((visibility("default")))
#define PRIVATE_API __attribute__((visibility("hidden")))

#define _NOEXCEPT throw() // deprected in c++98
#  define _NOEXCEPT_(x) throw(x)

#endif // __FT_CONTAINERS__DEFINITION__