#include "test.hpp"
#include <stack>

#define TESTED_NAMESPACE ft
#define TESTED_TYPE int

static void print_test_header() {
    split_line_2();
    std::cout << "    Stack Test    " << std::endl;
    split_line_2();
}

template<class T>
void print_stack_empty(TESTED_NAMESPACE::stack<T>& stk) {
    std::string ret = stk.empty() ? "true" : "false";
    std::cout << "is stack empty? : " << std::endl;
}


template<class T>
void print_stack(TESTED_NAMESPACE::stack<T>& stk) {
    std::cout << "Size : " << stk.size() << std::endl;
    std::cout << "Top : " << stk.top() << std::endl;
    print_stack_empty(stk);
}


void test_stack(void) {
    print_test_header();
    TESTED_NAMESPACE::stack<TESTED_TYPE> stk;

    for (unsigned int i = 0; i < 5; i++) {
        stk.push(i);
        print_stack(stk);
    }

    for (unsigned int i = 0; i < 5; i++) {
        stk.pop();
        print_stack(stk);
    }

    stk.pop();
}