#ifndef __FT_CONTAINERS__TYPE_TRAIT__
#define __FT_CONTAINERS__TYPE_TRAIT__

#include <stdexcept>

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

    template <class _Tp, _Tp __v>
    struct integral_constant {
        static const _Tp                    value = __v;
        typedef _Tp                         value_type;
        typedef integral_constant           type;
    };

    template <class _Tp, _Tp __v>
    const _Tp integral_constant<_Tp, __v>::value;

    template <class>
    struct __void_t { typedef void type; };
    
    template <class _Tp>
    struct __identity { typedef _Tp type; };

    template <bool Cond, class T = void>
    struct enable_if {};

    template <class T>
    struct enable_if<true, T> { typedef T type; };

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

    template <class _Tp, class _Up>
    struct is_same : public __false_type {};

    template <class _Tp>
    struct is_same<_Tp, _Tp> : public __true_type {};

    /*
    *   is_void
    */



    template<typename T>
    struct is_void : __false_type {};

    template<>
    struct is_void<void> : __true_type {};

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
    struct is_integral<unsigned char> : __true_type {};

    template<>
    struct is_integral<unsigned short int> : __true_type {};

    template<>
    struct is_integral<unsigned int> : __true_type {};

    template<>
    struct is_integral<unsigned long int> : __true_type {};

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

    template <class _Tp>
    struct is_nothrow_default_constructible : __false_type {};


}

#endif // __FT_CONTAINERS__TYPE_TRAIT__
