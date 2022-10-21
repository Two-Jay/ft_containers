#ifndef __FT_CONTAINERS__PAIR__
#define __FT_CONTAINERS__PAIR__

namespace ft {

    template<class _T1, class _T2>
    struct pair {
            typedef _T1                      first_type;
            typedef _T2                      second_type;

            first_type              first;
            second_type             second;


            pair() : first(), second() {};

            pair(const first_type& _a, const second_type& _b) : first(_a), second(_b) {};

            pair(const pair& other) : first(other.first), second(other.second) {};

            pair& operator= (const pair& other) {
                if (this != &other) {
                    this->first = other.first;
                    this->second = other.second;
                }
                return *this;
            };

            // needed fix to delete
            first_type& get_first() { return this->first; };
            second_type& get_second() { return this->second; };
    };

    template <class _T1, class _T2>
    bool operator== (const ft::pair<_T1, _T2>& lhs, const ft::pair<_T1, _T2>& rhs) {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template <class _T1, class _T2>
    bool operator!= (const ft::pair<_T1, _T2>& lhs, const ft::pair<_T1, _T2>& rhs) {
        return !(lhs == rhs);
    }

    template <class _T1, class _T2>
    bool operator< (const ft::pair<_T1, _T2>& lhs, const ft::pair<_T1, _T2>& rhs) {
        return lhs.first == rhs.first ? lhs.second < rhs.second : lhs.first < rhs.first;
    }

    template <class _T1, class _T2>
    bool operator> (const ft::pair<_T1, _T2>& lhs, const ft::pair<_T1, _T2>& rhs) {
        return lhs.first == rhs.first ? lhs.second > rhs.second : lhs.first > rhs.first;
    }

    template <class _T1, class _T2>
    bool operator<= (const ft::pair<_T1, _T2>& lhs, const ft::pair<_T1, _T2>& rhs) {
        return !(lhs > rhs);
    }

    template <class _T1, class _T2>
    bool operator>= (const ft::pair<_T1, _T2>& lhs, const ft::pair<_T1, _T2>& rhs) {
        return !(lhs < rhs);
    }

    template <class _T1, class _T2>
    ft::pair<_T1, _T2> make_pair (_T1 first, _T2 second) {
        return ft::pair<_T1, _T2>(first, second);
    }
} // end namespace ft here

#endif // __FT_CONTAINERS__PAIR__