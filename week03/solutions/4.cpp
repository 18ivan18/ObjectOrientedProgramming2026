// Компилиране: g++ -o 4 4.cpp QuadraticEquation.cpp Complex.cpp
#include "QuadraticEquation.h"
#include <iostream>

int main()
{
    QuadraticEquation eq1(2, -12, 16);
    std::cout << "2x^2 - 12x + 16 = 0\n";
    eq1.printSolutions();

    std::cout << "\nx^2 + 1 = 0 (комплексни корени)\n";
    QuadraticEquation eq2(1, 0, 1);
    eq2.printSolutions();

    std::cout << "\nx^2 - 4x + 4 = 0 (двоен корен)\n";
    QuadraticEquation eq3(1, -4, 4);
    eq3.printSolutions();
}
