#include "test.hpp"
#include <string>

#define TESTED_NAMESPACE ft
#define TESTED_TYPE_1 int
#define TESTED_TYPE_2 std::string


void init_map(TESTED_NAMESPACE::map<TESTED_TYPE_1, TESTED_TYPE_2>& map) {
    map.insert(TESTED_NAMESPACE::make_pair(42, "I"));
    map.insert(TESTED_NAMESPACE::make_pair(13, "II"));
    map.insert(TESTED_NAMESPACE::make_pair(69, "III"));
    map.insert(TESTED_NAMESPACE::make_pair(1, "IV"));
    map.insert(TESTED_NAMESPACE::make_pair(5, "V"));
    map.insert(TESTED_NAMESPACE::make_pair(7, "VI"));
    map.insert(TESTED_NAMESPACE::make_pair(9, "VII"));
    map.insert(TESTED_NAMESPACE::make_pair(11, "VIII"));
    map.insert(TESTED_NAMESPACE::make_pair(15, "IX"));
    map.insert(TESTED_NAMESPACE::make_pair(17, "X"));
    map.insert(TESTED_NAMESPACE::make_pair(42, "I"));
    map.insert(TESTED_NAMESPACE::make_pair(13, "II"));
    map.insert(TESTED_NAMESPACE::make_pair(69, "III"));
    map.insert(TESTED_NAMESPACE::make_pair(1, "IV"));
    map.insert(TESTED_NAMESPACE::make_pair(5, "V"));
    map.insert(TESTED_NAMESPACE::make_pair(7, "VI"));
    map.insert(TESTED_NAMESPACE::make_pair(9, "VII"));
    map.insert(TESTED_NAMESPACE::make_pair(11, "VIII"));
    map.insert(TESTED_NAMESPACE::make_pair(15, "IX"));
    map.insert(TESTED_NAMESPACE::make_pair(17, "X"));
    map.insert(TESTED_NAMESPACE::make_pair(42, "I"));
    map.insert(TESTED_NAMESPACE::make_pair(13, "II"));
    map.insert(TESTED_NAMESPACE::make_pair(69, "III"));
    map.insert(TESTED_NAMESPACE::make_pair(1, "IV"));
    map.insert(TESTED_NAMESPACE::make_pair(5, "V"));
    map.insert(TESTED_NAMESPACE::make_pair(7, "VI"));
    map.insert(TESTED_NAMESPACE::make_pair(9, "VII"));
    map.insert(TESTED_NAMESPACE::make_pair(11, "VIII"));
    map.insert(TESTED_NAMESPACE::make_pair(15, "IX"));
    map.insert(TESTED_NAMESPACE::make_pair(17, "X"));
}

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template<class T1, class T2>
void print_map(TESTED_NAMESPACE::map<T1, T2>& map, bool isEmpty) {
    std::cout << "Size : " << map.size() << std::endl;
    if (!isEmpty) {
        typename TESTED_NAMESPACE::map<T1, T2>::const_iterator it = map.begin(), ite = map.end();
        std::cout << "Content is : " << map.size() << std::endl;
        for (;it != ite; ++it) {
            if (it == map.begin()) {
                std::cout << "( ";
            }
            std::cout << printPair(it, false) << ", ";
            if (it == --map.end()) {
                std::cout << ")" << std::endl;
            }
        }
    }
    split_line_3();
}

void test_map(void) {
    TESTED_NAMESPACE::map<TESTED_TYPE_1, TESTED_TYPE_2> map;
   
    init_map(map);
    print_map(map, map.empty());

    map.erase(15);
    map.erase(map.begin());
    print_map(map, map.empty());
    
    map.erase(map.begin(), ++(++(++map.begin())));
    print_map(map, map.empty());

    map.clear();
    print_map(map, map.empty());

    split_line_3();
}