// Компилиране: g++ -o 2 2.cpp Complex.cpp
#include "Complex.h"
#include <iostream>

int main()
{
    Complex a{5, -3.14};
    Complex b{10, 4.15};

    std::cout << "a = ";
    a.print();
    std::cout << "b = ";
    b.print();

    std::cout << "a + b = ";
    a.add(b).print();

    std::cout << "a * b = ";
    a.multiply(b).print();

    std::cout << "a conjugate = ";
    a.conjugate().print();
}
