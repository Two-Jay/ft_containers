#include "./containers/rbt_tree.hpp"
#include "./containers/pair.hpp"

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

int main() {
    ft::rbt_tree<int, int, std::less<int>, std::allocator<ft::pair<int, int> > > __t;

    __t.insert(TEST_NAMESPACE::make_pair(42, 84));
    __t.insert(TEST_NAMESPACE::make_pair(13, 92));
    __t.insert(TEST_NAMESPACE::make_pair(69, 96));
    __t.insert(TEST_NAMESPACE::make_pair(1, 2));
    __t.insert(TEST_NAMESPACE::make_pair(5, 10));
    __t.insert(TEST_NAMESPACE::make_pair(7, 14));
    __t.insert(TEST_NAMESPACE::make_pair(9, 18));
    __t.insert(TEST_NAMESPACE::make_pair(11, 22));
    __t.insert(TEST_NAMESPACE::make_pair(15, 30));
    __t.insert(TEST_NAMESPACE::make_pair(17, 34));
    __t.insert(TEST_NAMESPACE::make_pair(19, 38));
    __t.insert(TEST_NAMESPACE::make_pair(21, 42));
    __t.insert(TEST_NAMESPACE::make_pair(25, 50));

    

    

    __t.print();

    __t.erase(13);
    __t.erase(5);
    __t.erase(9);
    __t.erase(15);
    __t.erase(21);

    __t.print();
    system("leaks main");
    return 0;
}