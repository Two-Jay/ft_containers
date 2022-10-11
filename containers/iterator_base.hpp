#ifndef __FT_CONTAINERS_ITERATOR_BASE__
#define __FT_CONTAINERS_ITERATOR_BASE__

#include <cstddef> // for ptrdiff_t
#include "./type_traits.hpp"

namespace ft {
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : input_iterator_tag {};
	struct bidirectional_iterator_tag : forward_iterator_tag {};
	struct random_access_iterator_tag : bidirectional_iterator_tag {};

	template <typename _Tp, bool>
	struct __iterator_traits {
		typedef std::ptrdiff_t                  		difference_type;
		typedef ft::random_access_iterator_tag  		iterator_category;
		typedef _Tp                              		value_type;
		typedef _Tp*                            		pointer;
		typedef _Tp&                            		reference;
	};

	template <typename _Tp>
	struct __iterator_traits<const _Tp, false> {
		typedef std::ptrdiff_t                  		difference_type;
		typedef ft::random_access_iterator_tag  		iterator_category;
		typedef const _Tp                              	value_type;
		typedef const _Tp*                            	pointer;
		typedef const _Tp&                            	reference;
	};

	template <typename _Tp>
	struct __iterator_traits<_Tp, true> {
		typedef typename _Tp::difference_type       	difference_type;
		typedef typename _Tp::value_type            	value_type;
		typedef typename _Tp::pointer               	pointer;
		typedef typename _Tp::reference             	reference;
		typedef typename _Tp::iterator_category     	iterator_category;
	};

	template<class _Iter>
	struct __has_iterator_typedefs {
		private :
			struct __two {char __lx; char __lxx;};
			template <class _Up> static __two __test(...);
			template <class _Up> static char __test(
				typename ft::__void_t<typename _Up::iterator_category>::type* = 0,
				typename ft::__void_t<typename _Up::difference_type>::type* = 0,
				typename ft::__void_t<typename _Up::value_type>::type* = 0,
				typename ft::__void_t<typename _Up::reference>::type* = 0,
				typename ft::__void_t<typename _Up::pointer>::type* = 0
			);
		public :
			static const bool value = sizeof(__test<_Iter>(0,0,0,0,0)) == 1;
	};

	template<class _Iter>
	struct iterator_traits : __iterator_traits <_Iter, __has_iterator_typedefs<_Iter>::value>
	{};

	template<class T>
	struct iterator_traits<T *>
	{
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef ft::random_access_iterator_tag iterator_category;
	};

	template<class T>
	struct iterator_traits<const T *>
	{
		typedef std::ptrdiff_t 						difference_type;
		typedef T 									value_type;
		typedef const T*							pointer;
		typedef const T&							reference;
		typedef ft::random_access_iterator_tag		iterator_category;
	};

	template <
		class _Category,
		class _T,
		class _Distance = std::ptrdiff_t,
		class _Pointer = _T*,
		class _Reference = _T&
	>
	struct iterator {
		typedef _Category                        	iterator_category;
		typedef _T                               	value_type;
		typedef _Distance                        	difference_type;
		typedef _Pointer                         	pointer;
		typedef _Reference                       	reference;
	};

	template <class _Iter>
	typename ft::iterator_traits<_Iter>::iterator_category _iterator_category(const _Iter&) {
		return typename ft::iterator_traits<_Iter>::iterator_category();
	}

	template <class _Iter>
	typename ft::iterator_traits<_Iter>::difference_type _difference_type(const _Iter&) {
		return typename ft::iterator_traits<_Iter>::difference_type();
	}

	template <class _Iter>
	typename ft::iterator_traits<_Iter>::difference_type _distance(_Iter __first, _Iter __last, ft::input_iterator_tag) {
		typename ft::iterator_traits<_Iter>::difference_type result = 0;
		for (; __first != __last ; ++__first) {
			++result;
		}
		return result;
	}

	template <class _Iter>
	typename ft::iterator_traits<_Iter>::difference_type _distance(_Iter __first, _Iter __last, ft::random_access_iterator_tag) {
		return __last - __first;
	}

	template <class _Iter>
	typename ft::iterator_traits<_Iter>::difference_type distance(_Iter __first, _Iter __last) {
		return ft::_distance(__first, __last, _iterator_category(__first));
	}

	template <class _Iter>
	void _advance(_Iter iter, typename ft::iterator_traits<_Iter>::difference_type n, ft::input_iterator_tag) {
		for (; n > 0; --n) {
			++iter;
		}
	}

	template <class _Iter>
	void _advance(_Iter __iter, typename ft::iterator_traits<_Iter>::difference_type n, ft::bidirectional_iterator_tag) {
		if (n < 0) {
			for (; n < 0; ++n) {
				--__iter;
			}
		} else {
			for (; n > 0; --n) {
				++__iter;
			}
		}
	}

	template <class _Iter>
	void _advance(_Iter __iter, typename ft::iterator_traits<_Iter>::difference_type n, ft::random_access_iterator_tag) {
		__iter += n;
	}

	template <class _Iter, class Distance>
	void advance(_Iter __iter, Distance __n) {
		ft::_advance(__iter, __n, _iterator_category(__iter));
	}
}

#endif // __FT_CONTAINERS_ITERATOR_T YPE__
