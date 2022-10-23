#include "test.hpp"

#define TESTED_NAMESPACE ft
#define TESTED_TYPE int

static void print_test_header () {
    split_line_2();
    std::cout << "    Vector Test    " << std::endl;
    split_line_2();
}

template <class T>
void print_tested_vector(TESTED_NAMESPACE::vector<T>& vct) {
    std::cout << "Content : " << std::endl;
    typename TESTED_NAMESPACE::vector<T>::const_iterator it = vct.begin();
    typename TESTED_NAMESPACE::vector<T>::const_iterator ite = vct.end();

    for (; it != ite; ++it) {
        if (it == vct.begin()) {
            std::cout << "[ ";
        }
        std::cout << *it << " ";
        if (it == --vct.end()) {
            std::cout << "]" << std::endl;
        }
    }
    std::cout << "Size : " << vct.size() << std::endl;
}

template <class T>
void print_vector_empty(TESTED_NAMESPACE::vector<T>& vct) {
    std::string ret = vct.empty() ? "true" : "false";
    std::cout << "is_vector1_empty ? : " << ret << std::endl;
}

void test_vector(void) {
    print_test_header();

    TESTED_NAMESPACE::vector<TESTED_TYPE> vct(10);
    TESTED_NAMESPACE::vector<TESTED_TYPE> vct2;


    for (unsigned long int i = 0; i < vct.size(); ++i) {
        vct[i] = (vct.size() - i) * 3;
    }

    vct2.assign(10, 32);
    print_tested_vector(vct);
    print_tested_vector(vct2);

    print_vector_empty(vct);
    vct.clear();
    print_tested_vector(vct);
    print_vector_empty(vct);
    split_line_3();

    vct.insert(vct.begin(), vct2.begin(), vct2.end());
    print_tested_vector(vct);
    print_tested_vector(vct2);

    TESTED_NAMESPACE::vector<TESTED_TYPE> vct3(vct2);
    print_tested_vector(vct3);
    for (unsigned long int i = 0; i < vct.size(); ++i) {
        vct3[i] = (vct.size() - i) * 3;
    }
    TESTED_NAMESPACE::vector<TESTED_TYPE> vct4 = vct3;
    print_tested_vector(vct4);

    split_line_3();

    print_tested_vector(vct3);
    print_tested_vector(vct4);
    vct3.erase(vct3.begin(), vct3.end() - 2);
    vct4.erase(vct4.begin() + 2);
    print_tested_vector(vct3);
    print_tested_vector(vct4);

    vct3.clear();
    vct4.clear();
    for (unsigned long int i = 0; i < 10; ++i) {
        vct3.push_back(i);
    }
    vct4.insert(vct4.begin(), vct3.begin(), vct3.end());
    print_tested_vector(vct3);
    print_tested_vector(vct4);
    
    std::cout << "vct_a is" << std::endl;
    print_tested_vector(vct2);
    std::cout << "vct_b is" << std::endl;
    print_tested_vector(vct4);
    vct4.swap(vct2);

    split_line_3();
    
    std::cout << "vct_a is" << std::endl;
    print_tested_vector(vct2);
    std::cout << "vct_b is" << std::endl;
    print_tested_vector(vct4);
    // system("leaks containers_test");
}