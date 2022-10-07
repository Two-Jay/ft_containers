#include "containers/vector.hpp"
#include "containers/concept_check.hpp"
// #include <iterator>
#include <iostream>
#include <iterator>

// using namespace std;

int main(){
    std::vector<int> a(10, 5);

    std::vector<int>::iterator it = a.begin();

    __function_requires<RandomAccessIteratorConcept<it> >();
    return 0;
}
