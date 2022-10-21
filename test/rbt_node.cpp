#include "./containers/tree_set/rbt_node.hpp"
#include <iostream>

#define TEST_NAMESPACE ft

void print_split_line()
{
    std::cout << "----------------------------------------" << std::endl;
}

bool isEqualColor(TEST_NAMESPACE::rbt_node_type& a, TEST_NAMESPACE::rbt_node_type& b)
{
    return (a == b) ? true : false;
}

template <class T11, class T12, class T21, class T22>
bool isEqualValue(TEST_NAMESPACE::rbt_node<T11, T12>& __n1, TEST_NAMESPACE::rbt_node<T21, T22>& __n2) {
    return (__n1._value->first == __n2._value->first && __n1._value->second == __n2._value->second);
}

template <class T1, class T2>
void print_node(TEST_NAMESPACE::rbt_node<T1, T2>& __n) {
    std::string color = (__n._color == TEST_NAMESPACE::BLACK) ? "BLACK" : (__n._color == TEST_NAMESPACE::RED) ? "RED" : "NIL";
    std::cout << "first : " << __n._value->first << std::endl;
    std::cout << "second : " << __n._value->second << std::endl;
    std::cout << "color : " << color << std::endl;
    print_split_line();
}

template <class T11, class T12, class T21, class T22>
void print_node_is_equal(TEST_NAMESPACE::rbt_node<T11, T12>& __n1, TEST_NAMESPACE::rbt_node<T21, T22>& __n2) {
    std::string equal_ret = isEqualValue(__n1, __n2) && isEqualColor(__n1._color, __n2._color) ? "Equal" : "Not Equal";
    std::cout << equal_ret << std::endl;
    print_split_line();
}

int test_node() {
    ft::rbt_node<int, int> __n(42, 84);
    ft::rbt_node<int, int> __n2(42, 84, NULL, TEST_NAMESPACE::RED);
    print_node(__n);
    print_node(__n2);
    print_node_is_equal(__n, __n2);
    
    __n2.change_color(TEST_NAMESPACE::BLACK);
    print_node(__n);
    print_node(__n2);
    print_node_is_equal(__n, __n2);

    __n._left = new ft::rbt_node<int, int>(13, 92);
    __n._right = &__n2;
    
    print_node(__n);
    print_node(__n2);
    print_node(*__n._left);
    print_node_is_equal(*__n._right, __n2);

    delete __n._left;
    // system("leaks main");
    return 0;
}

