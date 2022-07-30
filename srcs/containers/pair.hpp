#ifndef __FT_CONTAINERS_COMPRESSED_PAIR__
#define __FT_CONTAINERS_COMPRESSED_PAIR__

#include <utility>

template<class T1, class T2>
struct pair {
    public :
        typedef T1                      first_type;
        typedef T2                      second_type;
        typedef T1&                     first_reference;
        typedef T2&                     second_reference;
        typedef const first_reference   const_first_reference;
        typedef const second_reference  const_second_reference;

    protected :
        
    private :
        first_type              first_value_;
        second_type             second_value_;

    pair() : first_value_(), second_value_() {};
    pair(const_first_reference) : first_value_(const_first_reference) {}
    pair(const_first_reference, const_second_reference) : first_value_(const_first_reference), second_value_(const_second_reference) {};
    pair(const pair<T1, T2>& other) : first_value_(other.first_value_), second_value_(other.second_value_) {};

    pair& operator= (const pair<T1, T2>& other) { this->first_value_ = other.first_value_; this->second_value_ = other.second_value_; return *this };
};

template <class T1, class T2>
bool operator== (const pair<T1, T2> pair_a, const pair<T1, T2> pair_b) { return (pair_a.first_value_ == pair_b.first_value_ && pair_a.second_value_ == pair_b.second_value_) };

template <class T1, class T2>
bool operator<= (const pair<T1, T2> pair_a, const pair<T1, T2> pair_b) { return (pair_a.first_value_ <= pair_b.first_value_ || (!(pair_a.first_value_ <= pair_b.first_value_) && pair_a.second_value_ <= pair_b.second_value_)) };

template <class T1, class T2>
bool operator>= (const pair<T1, T2> pair_a, const pair<T1, T2> pair_b) { return (pair_a.first_value_ >= pair_b.first_value_ || (!(pair_a.first_value_ >= pair_b.first_value_) && pair_a.second_value_ >= pair_b.second_value_)) };

template <class T1, class T2>
bool operator<  (const pair<T1, T2> pair_a, const pair<T1, T2> pair_b) { return () };

template <class T1, class T2>
bool operator> (const pair<T1, T2> pair_a, const pair<T1, T2> pair_b) { return () };


#endif // __FT_CONTAINERS_COMPRESSED_PAIR__