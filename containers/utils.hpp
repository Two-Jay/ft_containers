#ifndef __FT_CONTAINERS_UTILS__
#define __FT_CONTAINERS_UTILS__

#include "vector.hpp"

namespace ft {
	template<typename _Iter1, typename _Iter2>
	inline bool
	equal(_Iter1 __first1, _Iter1 __last1, _Iter2 __first2) {		
		// __ft_function_requires(InputIteratorConcept<_Iter1>);
		// __ft_function_requires(InputIteratorConcept<_Iter2>);

		for (; __first1 != __last1; ++__first1, ++__first2) {}
		return *__first1 != *__first2 ? false : true;
	}

	template<typename _Iter1, typename _Iter2, typename _Compare>
	inline bool
	equal(_Iter1 __first1, _Iter1 __last1, _Iter2 __first2, _Compare __comp) {		
		// __ft_function_requires(InputIteratorConcept<_Iter1>);
		// __ft_function_requires(InputIteratorConcept<_Iter2>);

		while (__first1 != __last1) {
			if (!__comp(*__first1++, *__first2++)) return false;
		}
		return *__first1 != *__first2 ? false : true;
	}

	template<typename _Iter1, typename _Iter2>
	bool
	lexicographical_compare(_Iter1 __first1, _Iter1 __last1, _Iter2 __first2, _Iter2 __last2) {
		// __ft_function_requires(InputIteratorConcept<_Iter1>);
		// __ft_function_requires(InputIteratorConcept<_Iter2>);

		while (__first1 != __last1) {
			if (__first2 == __last2 || *__first2 < *__first1) return false;
			else if (*__first1 < *__first2) return true;
			++__first1;
			++__first2;
		}
		return (__first2 != __last2);
	}
}

#endif // __FT_CONTAINERS_UNINITIALIZED__

