#include "./containers/pair.hpp"
#include <iostream>

template<class T1, class T2>
void
print_pair(ft::pair<T1, T2>& __p) {
    std::cout << __p.first << std::endl;
    std::cout << __p.second << std::endl;    
}

void test_pair()
{
    ft::pair<int, int> __p;

    __p.first = 4242;
    __p.second = 2424;

    print_pair(__p);

    __p.first += 4242;
    __p.second *= -1;
    
    print_pair(__p);

    ft::pair<int, int> __p2(__p);

    print_pair(__p2);
    print_pair(__p);

    ft::pair<int, int> __p3 = __p2;
    __p3.first += 10000;
    __p3.second -= 10000;

    print_pair(__p2);
    print_pair(__p3);

    return 0;
}