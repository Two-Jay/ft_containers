#ifndef __FT_CONTAINERS__TYPE_TRAIT__
#define __FT_CONTAINERS__TYPE_TRAIT__

#include "definition.hpp"

namespace ft {

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

    

    template <bool Cond, class T = void>
    struct enable_if {};

    template <class T>
    struct enable_if<true, T> { typedef T type; };

    /*
    *   is_void
    */

    template<typename T>
    struct is_void : __false_type {};

    template<>
    struct is_void<void> : __true_type {};

    struct __true_type {
        static const bool value = true;
        typedef bool value_type;
        typedef __true_type type;
    };

    struct __false_type {
        static const bool value = false;
        typedef bool value_type;
        typedef __true_type type;
    };

    /*
    *   is_integral
    */

    template<typename T>
    struct is_integral : __false_type {};

    template<>
    struct is_integral<bool> : __true_type {};

    template<>
    struct is_integral<char> : __true_type {};

    template<>
    struct is_integral<wchar_t> : __true_type {};

    template<>
    struct is_integral<signed char> : __true_type {};

    template<>
    struct is_integral<short int> : __true_type {};

    template<>
    struct is_integral<int> : __true_type {};

    template<>
    struct is_integral<long int> : __true_type {};

    template<>
    struct is_integral<long long int> : __true_type {};

    template<>
    struct is_integral<unsigned char> : __true_type {};

    template<>
    struct is_integral<unsigned short int> : __true_type {};

    template<>
    struct is_integral<unsigned int> : __true_type {};

    template<>
    struct is_integral<unsigned long int> : __true_type {};

    template<>
    struct is_integral<unsigned long long int> : __true_type {};

    /*
    *   is_floating_point
    */

    template<typename T>
    struct is_floating_point : __false_type {};

    template<>
    struct is_floating_point<float> : __true_type {};

    template<>
    struct is_floating_point<double> : __true_type {};

    template<>
    struct is_floating_point<long double> : __true_type {};
}

#endif // __FT_CONTAINERS__TYPE_TRAIT__