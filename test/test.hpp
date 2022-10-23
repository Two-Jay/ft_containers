#ifndef _FT_CONTAINERS_TEST_
#define _FT_CONTAINERS_TEST_

#include "../containers/map.hpp"
#include "../containers/set.hpp"
#include "../containers/vector.hpp"
#include "../containers/stack.hpp"
#include "../containers/rbt_tree.hpp"
#include "../containers/rbt_node.hpp"

#include <iostream>
#include <istream>
#include <string>
#include <cstdlib>

// #include "../containers/rbt_tree.hpp"
// #include "../containers/rbt_node.hpp"

void test_vector(void);
void test_stack(void);
void test_map(void);
void test_set(void);
void test_all(void);
void test_rbt(void);

void split_line_1(void);
void split_line_2(void);
void split_line_3(void);

void check_leaks(void);

#endif // _FT_CONTAINERS_TEST_
