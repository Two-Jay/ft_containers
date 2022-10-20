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


            pair() : first(), second() {};

            pair(const first_type& _a, const second_type& _b) : first(_a), second(_b) {};

            template<class _U1, class _U2>
            pair(const pair<_U1, _U2>& other) : first(other.first), second(other.second) {};

            pair& operator= (const pair& other) {
                if (this != &other) {
                    this->first = other.first;
                    this->second = other.second;
                }
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

#endif // __FT_CONTAINERS_COMPRESSED_PAIR__
