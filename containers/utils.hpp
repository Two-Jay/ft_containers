#ifndef __FT_CONTAINERS_UTILS__
#define __FT_CONTAINERS_UTILS__

#include "vector.hpp"

namespace ft {
	template <class _InputIt1, class _InputIt2>
	bool
	lexicographical_compare_equal (_InputIt1 _first1, _InputIt1 _last1, _InputIt2 _first2, _InputIt2 _last2 ) {
		while ((_first1 != _last1) && (_first2 != _last2)) {
			if (*_first1++ != *_first2++) {
				return false;
			}
    	}
		return (_first1 == _last1) && (_first2 == _last2);
	}

	template< class _InputIt1, class _InputIt2, class _Compare >
	bool
	lexicographical_compare_equal (_InputIt1 _first1, _InputIt1 _last1, _InputIt2 _first2, _InputIt2 _last2, _Compare _comp ) {
		while ((_first1 != _last1) && (_first2 != _last2)) {
			if (!_comp(*_first1++, *_first2++)) {
				return false;
			}
		}
		return (_first1 == _last1) && (_first2 == _last2);
	}

	template <class _InputIt1, class _InputIt2>
	bool
	lexicographical_compare_less (_InputIt1 _first1, _InputIt1 _last1, _InputIt2 _first2, _InputIt2 _last2 ) {
		while ((_first1 != _last1) && (_first2 != _last2)) {
			if (*_first1 < *_first2) return true;
			if (*_first2 < *_first1) return false;
			_first1++, _first2++;
    	}
		return (_first1 == _last1) && (_first2 != _last2);
	}

	template< class _InputIt1, class _InputIt2, class _Compare >
	bool
	lexicographical_compare_less (_InputIt1 _first1, _InputIt1 _last1, _InputIt2 _first2, _InputIt2 _last2, _Compare _comp ) {
		while ((_first1 != _last1) && (_first2 != _last2)) {
			if (_comp(*_first1, *_first2)) return true;
			if (_comp(*_first2, *_first1)) return false;
			_first1++, _first2++;
		}
		return (_first1 == _last1) && (_first2 != _last2);
	}
}

#endif // __FT_CONTAINERS_UNINITIALIZED__
