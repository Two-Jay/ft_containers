#ifndef __FT_CONTAINERS__CONCEPT_CHECK__
#define __FT_CONTAINERS__CONCEPT_CHECK__

#include "./iterator_base.hpp"

namespace ft {
    template <class _Concept>
    inline void __function_requires()
    {
        void (_Concept::*__fp)() _IsUnused = &_Concept::__constraints;
    }

    template <class _Tp1, class _Tp2>
    struct __require_same {};
    
    template <class _Tp>
    struct __require_same<_Tp, _Tp> { typedef _Tp _Type; };

    template <class _Tp1, class _Tp2>
    struct _same_type_concept {
        void __constraints() {
            typedef typename __require_same<_Tp1, _Tp2>::_Type _Required;
        }
    };

    // ====================================================================

    /*
    ** integer Concepts
    */

    // ====================================================================

    void __error_type_must_be_an_integer_type();
    void __error_type_must_be_an_unsigned_integer_type();
    void __error_type_must_be_a_signed_integer_type();

    template <class _Tp>
    struct _IntegerConcept {
        void __constraints() {
            __error_type_must_be_an_integer_type();
        }
    };

    template <class _Tp>
    struct _SignedIntegerConcept {
        void __constraints() {
            __error_type_must_be_a_signed_integer_type();
        }
    }

    template <class _Tp>
    struct _UnsignedIntegerConcept {
        void __constraints() {
            __error_type_must_be_an_unsigned_integer_type();
        }
    }
    
    template <> struct _IntegerConcept<short> { void __constraints() {} };
    template <> struct _IntegerConcept<unsigned short> { void __constraints() {} };
    template <> struct _IntegerConcept<int> { void __constraints() {} };
    template <> struct _IntegerConcept<unsigned int> { void __constraints() {} };
    template <> struct _IntegerConcept<long> { void __constraints() {} };
    template <> struct _IntegerConcept<unsigned long> { void __constraints() {} };
    
    template <> struct _SignedIntegerConcept<short> { void __constraints() {} };
    template <> struct _SignedIntegerConcept<int> { void __constraints() {} };
    template <> struct _SignedIntegerConcept<long> { void __constraints() {} };

    template <> struct _UnsignedIntegerConcept<unsigned short> { void __constraints() {} };
    template <> struct _UnsignedIntegerConcept<unsigned int> { void __constraints() {} };
    template <> struct _UnsignedIntegerConcept<unsigned long> { void __constraints() {} };

    // ====================================================================

    /*
    ** Basic Concepts
    */

    // ====================================================================

    #define _IsUnused __attribute__ ((__unused__))

    template <class _Tp>
    struct _DefaultConstructibleConcept {
        void __constraints() {
            _Tp __a IsUnused;
        }
    };

    template <class _Tp>
    struct _AssignableConcept {
        _Tp __a;

        void __constraints() {
            __a = __a;
            __const_constaints(__a);
        }
        void __const_constaints(const _Tp& __b) {
            __a = __b;
        }
    };

    template <class _Tp>
    struct _CopyConstructibleConcept {
        _Tp __b;

        void __constraints() {
            _Tp __a(__b);
            _Tp* __ptr _IsUnused = &__a;
            __const_const
        }
        void __const_constaints(const _Tp& __a) {
            _Tp __c(__b) _IsUnused;
            const _Tp* __ptr _IsUnused = &__a;
        }
    };

    template <class _From, class _To>
    struct _ConvertibleConcept {
        _From __x;
    
        void __constraints() {
            _To __y _IsUnused = __x;
        }
    };

    template<class _Tp>
    void __require_boolean_expr(const _Tp& __t) {
        bool __x _IsUnused = __t;
    };

    template <class _Tp>
    struct _EqualityComparableConcept {
        _Tp __a, __b;
        
        void __constraints() {
            __require_boolean_expr(__a == __b);
            __require_boolean_expr(__a != __b);
        }
    };

    // template <class _Tp>
    // struct _LessComparableConcept {
    //     _Tp __a, __b;
    //     void __constraints() {
    //         __require_boolean_expr(__a < __b);
    //     }
    // };

    template <class _Tp>
    struct _ComparableConcept {
        _Tp __a, __b;
        
        void __constraints() {
            __require_boolean_expr(__a < __b);
            __require_boolean_expr(__a > __b);
            __require_boolean_expr(__a != __b);
            __require_boolean_expr(__a == __b);
        }
    };

    #define _BINARY_PREDICATE_OP_CONSTRAINT(_OP, _NAME) \
        template <class _First, class _Second> \
        struct _NAME { \
            void __constraints() { (void)__constraints_(); } \
            void __constraints_() { \
                return __a _OP __b; \
            } \
            _First      __a; \
            _Second     __b; \
        }

    #define _BINARY_OPERATOR_CONSTRAINT(_OP, _NAME) \
        template <class _Ret, class _First, class _Second> \
        struct _NAME { \
            void __constraints() { (void)__constraints_(); } \
            _Ret __constraints_() { \
                return __a _OP __b; \
            } \
            _First      __a; \
            _Second     __b; \
        }

    // _BINARY_PREDICATE_OP_CONSTRAINT(==, _EqualOpConcept);
    // _BINARY_PREDICATE_OP_CONSTRAINT(!=, _NotEqualOpConcept);
    // _BINARY_PREDICATE_OP_CONSTRAINT(<, _LessThanOpConcept);
    // _BINARY_PREDICATE_OP_CONSTRAINT(<=, _LessEqualOpConcept);
    // _BINARY_PREDICATE_OP_CONSTRAINT(>, _GreaterThanOpConcept);
    // _BINARY_PREDICATE_OP_CONSTRAINT(>=, _GreaterEqualOpConcept);
    
    // _BINARY_OPERATOR_CONSTRAINT(*, _TimesOpConcept);
    // _BINARY_OPERATOR_CONSTRAINT(/, _DivideOpConcept);
    
    // _BINARY_OPERATOR_CONSTRAINT(%, _ModOpConcept);

    // #undef _BINARY_PREDICATE_OP_CONSTRAINT
    // #undef _BINARY_OPERATOR_CONSTRAINT

    // ====================================================================

    /*
    ** Iterators Concept
    */

    // ====================================================================

    // _RandomAccessIteratorConcept for ft::random_access_iterator
    // it's differ from boost_concepts cause random_access_iterator defined far away from libstd...
    // but it would be worked...
    template <class _Tp>
    struct _RandomAcessIteratorConcept {
        _Tp __a, __b;
        _Tp __i, __j;
        typename ft::iterator_traits<_Tp>::difference_type __n;

        void __constraints() {
            __function_requires<_DefaultConstructibleConcept<_Tp> >();
            __function_requires<_AssignableConcept<_Tp> >();
            __function_requires<_CopyConstructibleConcept<_Tp> >();
            __function_requires<_EqualityComparableConcept<_Tp> >();
            __function_requires<_ComparableConcept<_Tp> >();
            _BINARY_OPERATOR_CONSTRAINT(-, _SubtractOperatorConcept);
            _BINARY_OPERATOR_CONSTRAINT(+, _PlusOperatorConcept);

            __i += __n;
            __i = __i + __n;
            __i = __n + __i;
            __i -= __n;
            __i = __i - __n;
            __n = __i - __j;
            (void)__i[__n];
        }
    }
}

#endif // __FT_CONTAINERS__CONCEPT_CHECK__