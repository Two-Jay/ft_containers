#include "containers/vector.hpp"
// #include <iterator>
#include <iostream>
#include <iterator>

// using namespace std;

int main(){
    ft::vector<int> a(10, 5);

    std::cout << a.size() << std::endl;
    for (ft::vector<int>::iterator it = a.begin(); it != a.end(); it++)
        std::cout << *it << std::endl;
    return 0;
}
