#ifndef __FT_CONTAINERS__CONCEPT_CHECK__
#define __FT_CONTAINERS__CONCEPT_CHECK__

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

    /*
    ** Basic Concepts
    */

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
}

#endif // __FT_CONTAINERS__CONCEPT_CHECK__