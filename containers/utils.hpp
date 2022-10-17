#ifndef __FT_CONTAINERS_UTILS__
#define __FT_CONTAINERS_UTILS__

namespace ft {
	template<typename _Iter1, typename _Iter2>
	bool
	equal(_Iter1 __first1, _Iter1 __last1, _Iter2 __first2) {		
		for (; __first1 != __last1; ++__first1, ++__first2) {}
		return *__first1 != *__first2 ? false : true;
	}

    template< class _InputIt1, class _InputIt2, class _Compare >
	bool
	equal (_InputIt1 _first1, _InputIt1 _last1, _InputIt2 _first2, _InputIt2 _last2, _Compare _comp ) {
		while ((_first1 != _last1) && (_first2 != _last2)) {
			if (!_comp(*_first1++, *_first2++)) {
				return false;
			}
		}
		return (_first1 == _last1) && (_first2 == _last2);
	}

	template< class _InputIt1, class _InputIt2, class _Compare >
	bool
	lexicographical_compare (_InputIt1 _first1, _InputIt1 _last1, _InputIt2 _first2, _InputIt2 _last2, _Compare _comp ) {
		while ((_first1 != _last1) && (_first2 != _last2)) {
			if (_comp(*_first1, *_first2)) return true;
			if (_comp(*_first2, *_first1)) return false;
			_first1++, _first2++;
		}
		return (_first1 == _last1) && (_first2 != _last2);
	}

	template<typename _Iter1, typename _Iter2>
	bool
	lexicographical_compare(_Iter1 __first1, _Iter1 __last1, _Iter2 __first2, _Iter2 __last2) {
		while (__first1 != __last1) {
			if (__first2 == __last2 || *__first2 < *__first1) return false;
			else if (*__first1 < *__first2) return true;
			++__first1;
			++__first2;
		}
		return (__first2 != __last2);
	}
}

#endif // __FT_CONTAINERS_UTILS__

