#include "./test.hpp"

#include <iostream>

#define INPUT_LIMIT_LEN 10
#define TEST_NAMESPACE ft
#define TEST_TREE_TYPE ft::rbt_tree<int, int, std::less<int>, std::allocator<ft::pair<int, int> > >
#define man_content \
    "       to insert a node to the tree, insert \"I || insert\"\n \
    to erase a node from the tree, insert \"E || erase\"\n \
    to show the tree, insert \"S || show\"\n \
    to clear the tree, insert \"C || clear\"\n \
    to read this manual once again, insert \"M || man\"\n \
    to exit, insert \"(E)xit\"\n \""


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

enum input_value {
    insert,
    erase,
    show,
    clear,
    man,
    close
};

input_value check_input_value(std::string& input) {
    if (!input.compare("I") || !input.compare("insert")) {
        return insert;
    }
    if (!input.compare("E") || !input.compare("erase")) {
        return erase;
    }
    if (!input.compare("S") || !input.compare("show")) {
        return show;
    }
    if (!input.compare("C") || !input.compare("clear")) {
        return clear;
    }
    if (!input.compare("M") || !input.compare("man")) {
        return man;
    }
    if (!input.compare("E") || !input.compare("exit")) {
        return close;
    }
    return man;
}

static void deal_insert(TEST_TREE_TYPE& tree) {
    std::string input;
    std::cout << "insert key to create a pair : ";
    std::getline(std::cin, input);
    int atoi_key = atoi(input.c_str());
    std::cout << "insert value to create a pair : ";
    input = "";
    std::getline(std::cin, input);
    int atoi_value = atoi(input.c_str());

    tree.insert(TEST_NAMESPACE::make_pair(atoi_key, atoi_value));
}

static void deal_erase(TEST_TREE_TYPE& tree) {
    std::string input;
    std::cout << "insert key to delete a node : ";
    std::getline(std::cin, input);
    int atoi_key = atoi(input.c_str());

    tree.erase(atoi_key);
}

static void deal_show(TEST_TREE_TYPE& tree) {
    tree.print();
}

static void deal_clear(TEST_TREE_TYPE& tree) {
    tree.clear();
}

static void deal_man(TEST_TREE_TYPE& tree) {
    (void) tree;
    std::cout << man_content << std::endl;    
}

void test_free_run_rbt(void) {
    TEST_TREE_TYPE __t;
    void (*fp[5])(TEST_TREE_TYPE&);

    fp[0] = deal_insert;
    fp[1] = deal_erase;
    fp[2] = deal_show;
    fp[3] = deal_clear;
    fp[4] = deal_man;

    while (true) {
        std::string input;
        std::cout << "insert your command : (to read manual, insert M)";
        std::getline(std::cin, input);
        input_value input_val = check_input_value(input);
        if (input_val == close) break ;
        fp[input_val](__t);
    }
    check_leaks();
}

void test_rbt(void) {
    std::string input;
    std::cout << "need free_run test ? (y/n) : ";
    std::getline(std::cin, input);
    if (input.compare("y") == 0 || input.compare("yes") == 0 ) {
        test_free_run_rbt();
    } else {
        TEST_TREE_TYPE __t;

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
        check_leaks();
    }
}