#ifndef __FT_CONTAINERS__CONCEPT_CHECK__
#define __FT_CONTAINERS__CONCEPT_CHECK__

#include "./iterator_base.hpp"

namespace ft {
    template <class _Concept>
    inline void __function_requires()
    {
        void (_Concept::*__fp)() = &_Concept::__constraints;
    }

    template <class _Tp1, class _Tp2>
    struct __require_same {};
    
    template <class _Tp>
    struct __require_same<_Tp, _Tp> { typedef _Tp _Type; };

    template <class _Tp1, class _Tp2>
    struct _same_type_concept {
        void __constraints() {
            typedef typename __require_same<_Tp1, _Tp2>::_Type _Required;

            _Required __x;

            (void)__x;
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
    };

    template <class _Tp>
    struct _UnsignedIntegerConcept {
        void __constraints() {
            __error_type_must_be_an_unsigned_integer_type();
        }
    };
    
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
    ** Basic Operator Concepts
    */

    // ====================================================================

    template <class _Tp1, class _Tp2>
    struct _SubtractOperatorConcept {
        _Tp1 __a;
        _Tp2 __b;
        void __constraints() {
            __a - __b;
            __b - __a;
        }
    };

    template <class _Tp1, class _Tp2>
    struct _PlusOperatorConcept {
        _Tp1 __a;
        _Tp2 __b;
        void __constraints() {
            __a + __b;
            __b + __a;
        }
    };

    template <class _Tp1, class _Tp2>
    struct _SubtractAssignOperatorConcept {
        _Tp1 __a;
        _Tp2 __b;
        void __constraints() {
            __a -= __b;
            __b -= __a;
        }
    };

    template <class _Tp1, class _Tp2>
    struct _PlusAssignOperatorConcept {
        _Tp1 __a;
        _Tp2 __b;
        void __constraints() {
            __a += __b;
            __b += __a;
        }
    };

    template <class _Tp>
    struct _IndexAssignOperatorConcept {
        _Tp __a;

        typename ft::iterator_traits<_Tp>::difference_type __n;
        void __constraints() {
            (void)__a[__n];
        }
    };

    // ====================================================================

    /*
    ** Basic Class Concepts
    */

    // ====================================================================

    #define _IsUnused __attribute__ ((__unused__))

    template <class _Tp>
    struct _DefaultConstructibleConcept {
        void __constraints() {
            _Tp __a;
        }
    };

    template <class _Tp>
    struct _AssignableConcept {
        _Tp __a, __c;

        void __constraints() {
            __a = __c;
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
            _Tp* __ptr = &__a;
            __const_constaints();
        }
        void __const_constaints(const _Tp& __a) {
            _Tp __c(__b);
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
    }

    template <class _Tp>
    struct _EqualityComparableConcept {
        _Tp __a, __b;
        
        void __constraints() {
            __require_boolean_expr(__a == __b);
            __require_boolean_expr(__a != __b);
        }
    };

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

    // ====================================================================

    /*
    ** Iterators Concept
    */

    // ====================================================================

    template <class _Tp>
    struct InputIteratorConcept {
        _Tp __a;

        void __constraints() { (void)__constraints_(); }
        void __constraints_() {
            __function_requires<_DefaultConstructibleConcept<_Tp> >();
            __function_requires<_AssignableConcept<_Tp> >();
            __function_requires<_EqualityComparableConcept<_Tp> >();
            __function_requires<_CopyConstructibleConcept<_Tp> >();

            typedef typename ft::iterator_traits<_Tp>::difference_type      _D;
            typedef typename ft::iterator_traits<_Tp>::pointer              _P;
            typedef typename ft::iterator_traits<_Tp>::reference            _R;

            __function_requires<_SignedIntegerConcept<_D> >();
            __function_requires<_ConvertibleConcept<
                typename ft::iterator_traits<_Tp>::iterator_category,
                ft::input_iterator_tag> >();

            ++__a;
            __a++;
            (void)*__a;
            _R __r = *__a;
            _P __p = &*__a;
            (void)__r;
            (void)__p;
        }
    }; 

    // RandomAccessIteratorConcept for ft::random_access_iterator
    // it's differ from boost_concepts cause random_access_iterator defined far away from libstd...
    // but it would be worked...
    template <class _Tp>
    struct RandomAccessIteratorConcept {
        void __constraints() { (void)__constraints_(); };
        void __constraints_() {
            __function_requires<_DefaultConstructibleConcept<_Tp> >;
            __function_requires<_AssignableConcept<_Tp> >;
            __function_requires<_CopyConstructibleConcept<_Tp> >();
            __function_requires<_EqualityComparableConcept<_Tp> >();
            __function_requires<_ComparableConcept<_Tp> >();
            __function_requires<_PlusOperatorConcept<_Tp, _Tp> >();
            __function_requires<_SubtractOperatorConcept<_Tp, _Tp> >();
            __function_requires<_PlusAssignOperatorConcept<_Tp, _Tp> >();
            __function_requires<_SubtractAssignOperatorConcept<_Tp, _Tp> >();
            __function_requires<_IndexAssignOperatorConcept<_Tp> >();
        }
    };
}

#endif // __FT_CONTAINERS__CONCEPT_CHECK__
