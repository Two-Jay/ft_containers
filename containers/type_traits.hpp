#ifndef __FT_CONTAINERS__TYPE_TRAIT__
#define __FT_CONTAINERS__TYPE_TRAIT__

#include "definition.hpp"

__LIBFT_CONTAINERS_START__

/*
*   ****        primary_categories      composite_categories
*               void                    -
*   funda-      ft::null_ptr            -
*   mental      integral                arith-
*               floating_point          metic
*   ----------------------------------------------
*               pointer                 -
*   compound    member_object_pointer   member-
*               member_function_pointer pointer
*               enum                    -
*               union                   -
*               class                   -
*               array                   -
*               l-value reference       refe-
*               r-value reference       rence
*               function                -
*
*/ 


/*
*   is_void
*/

template<typename T>
struct is_void { static const bool value = false; }

template<>
struct is_void<void> { static const bool value = true; }

/*
*   is_integral
*/

template<typename T>
struct is_integral<> { static const bool value = false; }

template<>
struct is_integral<bool> { static const bool value = true; }

template<>
struct is_integral<char> { static const bool value = true; }

template<>
struct is_integral<wchar_t> { static const bool value = true; }

template<>
struct is_integral<signed char> { static const bool value = true; }

template<>
struct is_integral<short int> { static const bool value = true; }

template<>
struct is_integral<int> { static const bool value = true; }

template<>
struct is_integral<long int> { static const bool value = true; }

template<>
struct is_integral<long long int> { static const bool value = true; }

template<>
struct is_integral<unsigned char> { static const bool value = true; }

template<>
struct is_integral<unsigned short int> { static const bool value = true; }

template<>
struct is_integral<unsigned int> { static const bool value = true; }

template<>
struct is_integral<unsigned long int> { static const bool value = true; }

template<>
struct is_integral<unsigned long long int> { static const bool value = true; }

/*
*   is_floating_point
*/

template<typename T>
struct is_floating_point { static const bool value = false; }

template<>
struct is_floating_point<float> { static const bool value = true; }

template<>
struct is_floating_point<double> { static const bool value = true; }

template<>
struct is_floating_point<long double> { static const bool value = true; }


__LIBFT_CONTAINERS_END__

#endif // __FT_CONTAINERS__TYPE_TRAIT__