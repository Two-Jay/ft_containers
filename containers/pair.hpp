#ifndef __FT_CONTAINERS_COMPRESSED_PAIR__
#define __FT_CONTAINERS_COMPRESSED_PAIR__

#include <utility>
#include "definition.hpp"

__LIBFT_CONTAINERS_START__


template<class _T1, class _T2>
struct pair {
    public :
        typedef _T1                      first_type;
        typedef _T2                      second_type;
        typedef _T1&                     first_reference;
        typedef _T2&                     second_reference;
        typedef const first_reference   const_first_reference;
        typedef const second_reference  const_second_reference;

    protected :
        
    private :
        first_type              __first_value;
        second_type             __second_value;

    pair() : __first_value(), __second_value() {};

    pair(const_first_reference) : __first_value(const_first_reference) {};
    
    pair(const_first_reference, const_second_reference) : __first_value(const_first_reference), __second_value(const_second_reference) {};
    
    pair(const pair<_T1, _T2>& other) : __first_value(other.__first_value), __second_value(other.__second_value) {};

    pair& operator= (const pair<_T1, _T2>& other) {
        this->__first_value = other.__first_value;
        this->__second_value = other.__second_value;
        return *this
    };
};

// == != < > <= >=
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
    return lhs.__first_value == rhs.__first_value ? lhs.__second_value < rhs.__second_value : lhs.__first_value < rhs.__first_value;
}

template <typename _T1, typename _T2>
bool operator> (const ft::pair<_T1, _T2>& lhs, const ft::pair<_T1, _T2>& rhs) {
    return lhs.__first_value == rhs.__first_value ? lhs.__second_value > rhs.__second_value : lhs.__first_value > rhs.__first_value;
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

__LIBFT_CONTAINERS_END__

#endif // __FT_CONTAINERS_COMPRESSED_PAIR__