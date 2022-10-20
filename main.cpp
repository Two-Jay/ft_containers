#include "./containers/tree_set/rbt_node.hpp"
#include <iostream>

#define TEST_NAMESPACE ft

template <class T1, class T2>
void print_node(TEST_NAMESPACE::rbt_node<T1, T2>& __n) {
    std::cout << "first : " << __n._value->first << std::endl;
    std::cout << "second : " << __n._value->second << std::endl;
    std::cout << "color : " << (__n._color == TEST_NAMESPACE::BLACK) ? "BLACK" : (__n._color == TEST_NAMESPACE::RED) ? "RED" : "NIL" << std::endl;
}

template <class T11, class T12, class T21, class T22>
void print_node_is_equal(ft::rbt_node<T11, T12>& __n1, ft::rbt_node<T21, T22>& __n2) {
    std::cout << (__n1->_value.first == __n2._value->first && __n1->_value.second == __n2._value->second) ? "Equal" : "Not Equal" << std::endl;
}

int main() {
    ft::rbt_node<int, int> __n(42, 84);
    
    return 0;
}

