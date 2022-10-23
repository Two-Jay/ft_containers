#include "test.hpp"
#include <iostream>

void test_all(void) {
    test_map();
    test_set();
    test_vector();
    test_stack();
    test_rbt();
}

void split_line_1(void) {
    std::cout << "-------------------------------------------------------" << std::endl;
}

void split_line_2(void) {
    std::cout << "=======================================================" << std::endl;
}

void split_line_3(void) {
    std::cout << ". . . . . . . . . . . . . . . . . . . . . . . . . . . ." << std::endl;
}

void check_leaks(void) {
    system("leaks containers_test");
}