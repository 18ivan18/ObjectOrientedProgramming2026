// c++ -std=c++17 -Wall -Wextra main.cpp -o main
#include "Pair.h"
#include <iostream>

int main()
{
    // same-type pair
    Pair<int> a(3, 7);
    std::cout << "a = (" << a.getFirst() << ", " << a.getSecond() << ")\n";

    a.setFirst(10);
    std::cout << "after setFirst(10): a = (" << a.getFirst() << ", " << a.getSecond() << ")\n";

    Pair<int> b(10, 7);
    std::cout << "a == b: " << (a == b) << "\n";
    std::cout << "a != b: " << (a != b) << "\n";

    Pair<int> c = b;
    std::cout << "b == c: " << (b == c) << "\n";

    // bonus: two different types
    Pair<int, double> d(4, 4.5);
    std::cout << "\nd = (" << d.getFirst() << ", " << d.getSecond() << ")\n";

    Pair<double, int> e(9.9, 3);
    std::cout << "e = (" << e.getFirst() << ", " << e.getSecond() << ")\n";
}
