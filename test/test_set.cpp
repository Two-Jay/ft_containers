#include "test.hpp"

#define TESTED_NAMESPACE ft
#define TESTED_TYPE int

void init_set(TESTED_NAMESPACE::set<TESTED_TYPE>& set) {
    set.insert(42);
    set.insert(13);
    set.insert(69);
    set.insert(1);
    set.insert(5);
    set.insert(7);
    set.insert(9);
    set.insert(11);
    set.insert(15);
    set.insert(17);
    set.insert(42);
    set.insert(13);
    set.insert(69);
    set.insert(1);
    set.insert(5);
    set.insert(7);
    set.insert(9);
    set.insert(11);
    set.insert(15);
    set.insert(17);
    set.insert(42);
    set.insert(13);
    set.insert(69);
    set.insert(1);
    set.insert(5);
    set.insert(7);
    set.insert(9);
    set.insert(11);
    set.insert(15);
    set.insert(17);
}

template<class T1, class T2>
void print_set(TESTED_NAMESPACE::set<T1, T2>& set, bool isEmpty) {
    std::cout << "Size : " << set.size() << std::endl;
    if (!isEmpty) {
        typename TESTED_NAMESPACE::set<T1, T2>::const_iterator it = set.begin(), ite = set.end();
        std::cout << "Content is : " << set.size() << std::endl;
        for (;it != ite; ++it) {
            if (it == set.begin()) {
                std::cout << "( ";
            }
            std::cout << *it << ", ";
            if (it == --set.end()) {
                std::cout << ")" << std::endl;
            }
        }
    }
    split_line_3();
}

void test_set(void) {
    TESTED_NAMESPACE::set<TESTED_TYPE> set;
   
    init_set(set);
    print_set(set, set.empty());

    set.erase(15);
    set.erase(set.begin());
    print_set(set, set.empty());
    
    set.erase(set.begin(), ++(++(++set.begin())));
    print_set(set, set.empty());

    set.clear();
    print_set(set, set.empty());

    split_line_3();
}