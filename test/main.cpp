#include "./test.hpp"
#include <string>
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 1 || argc > 2)
        std::cout << "Usage: ./containers || ./containers [container_type]" << std::endl;

    if (argc == 1) {
        test_vector();
        test_stack();
        test_map();
        test_set();
        test_rbt();
    }

    if (argc == 2) {
        std::string arg = argv[1];
        if (arg.compare("vector") == 0)
            test_vector();
        if (arg.compare("stack") == 0)
            test_stack();
        if (arg.compare("map") == 0)
            test_map();
        if (arg.compare("set") == 0)
            test_set();
        if (arg.compare("tree") == 0)
            test_rbt();
    }

    return 0;
}
