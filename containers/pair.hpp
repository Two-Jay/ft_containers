#ifndef __FT_CONTAINERS_COMPRESSED_PAIR__
#define __FT_CONTAINERS_COMPRESSED_PAIR__

#include <utility>

namespace ft {
    template<class _T1, class _T2>
    struct pair {
            typedef _T1                      first_type;
            typedef _T2                      second_type;

            first_type              first;
            second_type             second;


            pair() : first(_T1()), second(_T2()) {};

            pair(const first_type& _a, const second_type& _b) : first(_a), second(_b) {};

            template<class _U1, class _U2>
            pair(const pair<_U1, _U2>& other) : first(other.first), second(other.second) {};

            pair& operator= (const pair& other) {
                this->first = other.first;
                this->second = other.second;
                return *this;
            };

            ~pair() {};


            first_type& get_first() { return this->first; };
            second_type& get_second() { return this->second; };
    };

    template<typename _T1, typename _T2>
    bool operator== (const ft::pair<_T1, _T2>& lhs, const ft::pair<_T1, _T2>& rhs) {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template <typename _T1, typename _T2>
    bool operator!= (const ft::pair<_T1, _T2>& lhs, const ft::pair<_T1, _T2>& rhs) {
        return !(lhs == rhs);
    }

    template <typename _T1, typename _T2>
    bool operator< (const ft::pair<_T1, _T2>& lhs, const ft::pair<_T1, _T2>& rhs) {
        return lhs.first == rhs.first ? lhs.second < rhs.second : lhs.first < rhs.first;
    }

    template <typename _T1, typename _T2>
    bool operator> (const ft::pair<_T1, _T2>& lhs, const ft::pair<_T1, _T2>& rhs) {
        return lhs.first == rhs.first ? lhs.second > rhs.second : lhs.first > rhs.first;
    }

    template <typename _T1, typename _T2>
    bool operator<= (const ft::pair<_T1, _T2>& lhs, const ft::pair<_T1, _T2>& rhs) {
        return !(lhs > rhs);
    }

    template <typename _T1, typename _T2>
    bool operator>= (const ft::pair<_T1, _T2>& lhs, const ft::pair<_T1, _T2>& rhs) {
        return !(lhs < rhs);
    }

    template <typename _T1, typename _T2>
    ft::pair<_T1, _T2> make_pair (_T1 first, _T2 second) {
        return ft::pair<_T1, _T2>(first, second);
    }
}


	template <class T1, class T2>
	struct pair {
		typedef T1 first_type;
		typedef T2 second_type;
        first_type first;
        second_type second;

		pair() : first(), second() {}

        template <class U1, class U2>
        pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}

        pair(const first_type& k, const second_type& v) : first(k), second(v) { };

		pair& operator=(const pair& other) {
			if (this == &other)
                return *this;
            first = other.first;
			second = other.second;
			return *this;
		}

		void swap(pair& p)
		{
			std::swap(first,  p.first);
			std::swap(second, p.second);
		}
	};

	template <class T1, class T2>
	inline bool operator==(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return x.first == y.first && x.second == y.second;
	}

	template <class T1, class T2>
	inline bool operator!=(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return !(x == y);
	}

	template <class T1, class T2>
	inline bool operator< (const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
	}

	template <class T1, class T2>
	inline bool operator> (const pair<T1, T2>& x, const pair<T1, T2>& y) { return y < x; }

	template <class T1, class T2>
	inline bool operator>=(const pair<T1, T2>& x, const pair<T1, T2>& y) { return !(x < y); }

	template <class T1, class T2>
	inline bool operator<=(const pair<T1, T2>& x, const pair<T1, T2>& y) { return !(y < x); }

	template <class T1, class T2>
	inline pair<T1, T2> make_pair(T1 x, T2 y) { return pair<T1, T2>(x, y); }


#endif // __FT_CONTAINERS_COMPRESSED_PAIR__
