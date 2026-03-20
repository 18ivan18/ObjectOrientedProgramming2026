// Компилиране: g++ -o 4 4.cpp Rational.cpp -std=c++14
#include "Rational.h"
#include <iostream>

int main()
{
    std::cout << "=== Rational + Rational, опростяване ===\n";
    Rational a(1, 4), b(1, 4);
    Rational c = a + b;
    std::cout << "1/4 + 1/4 = " << c << "\n"; // 1/2

    Rational d(2, 6), e(1, 3);
    std::cout << "2/6 + 1/3 = " << (d + e) << "\n"; // 2/3

    std::cout << "\n=== Rational + int, int + Rational ===\n";
    Rational r(1, 2);
    std::cout << "1/2 + 3 = " << (r + 3) << "\n";   // 7/2
    std::cout << "3 + 1/2 = " << (3 + r) << "\n";   // 7/2
    std::cout << "1/2 - 1 = " << (r - 1) << "\n";   // -1/2
    std::cout << "2 * 1/3 = " << (2 * Rational(1, 3)) << "\n"; // 2/3
    std::cout << "1/4 * 4 = " << (Rational(1, 4) * 4) << "\n"; // 1

    std::cout << "\n=== Сравнения ===\n";
    std::cout << "1/2 < 2/3: " << (Rational(1, 2) < Rational(2, 3)) << "\n";
    std::cout << "2 == 4/2: " << (2 == Rational(4, 2)) << "\n";
    std::cout << "1/2 != 1/3: " << (Rational(1, 2) != Rational(1, 3)) << "\n";

    std::cout << "\n=== Деление ===\n";
    std::cout << "3/4 / 1/2 = " << (Rational(3, 4) / Rational(1, 2)) << "\n"; // 3/2
    std::cout << "5 / 1/2 = " << (5 / Rational(1, 2)) << "\n";                 // 10
}
