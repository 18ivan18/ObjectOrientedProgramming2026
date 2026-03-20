// Компилиране: g++ -o 5 5.cpp Vector.cpp -std=c++14
#include "Vector.h"
#include <iostream>

int main()
{
    std::cout << "=== Copy конструктор ===\n";
    Vector v1;
    v1.pushBack(10);
    v1.pushBack(20);
    v1.pushBack(30);

    Vector v2(v1);
    std::cout << "v1: " << v1 << "\n";
    std::cout << "v2 (копие на v1): " << v2 << "\n";

    v2[1] = 99;
    std::cout << "v2 след промяна: " << v2 << "\n";
    std::cout << "v1 непроменен: " << v1 << "\n";

    std::cout << "\n=== operator= ===\n";
    Vector v3;
    v3 = v1;
    std::cout << "v3 = v1: " << v3 << "\n";

    std::cout << "\n=== operator[] ===\n";
    std::cout << "v1[0] = " << v1[0] << ", v1[2] = " << v1[2] << "\n";

    std::cout << "\n=== operator==, != ===\n";
    std::cout << "v1 == v3: " << (v1 == v3) << "\n";
    std::cout << "v1 != v2: " << (v1 != v2) << "\n";

    std::cout << "\n=== operator+, += ===\n";
    Vector a, b;
    a.pushBack(1);
    a.pushBack(2);
    b.pushBack(3);
    b.pushBack(4);
    Vector c = a + b;
    std::cout << "a + b = " << c << "\n";

    a += b;
    std::cout << "a += b, a = " << a << "\n";
}
