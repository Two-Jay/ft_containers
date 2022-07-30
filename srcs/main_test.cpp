#include <utility>
#include <iostream>

void isTrue(bool condition) {
    if (condition) std::cout << "This is True";
    if (!condition) std::cout << "This is False";
}

int main() {
    std::pair <int, int> a(1, 5);
    std::pair <int, int> b(1, 4);
    isTrue((a >= b));
    return 0;
}