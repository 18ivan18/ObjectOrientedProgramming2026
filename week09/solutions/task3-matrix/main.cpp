// c++ -std=c++17 -Wall -Wextra main.cpp -o main
#include "Matrix.h"
#include <iostream>

int main()
{
    Matrix<int> a(2, 3);
    a.setElement(0, 0, 1);
    a.setElement(0, 1, 2);
    a.setElement(0, 2, 3);
    a.setElement(1, 0, 4);
    a.setElement(1, 1, 5);
    a.setElement(1, 2, 6);

    Matrix<int> b(2, 3);
    b.setElement(0, 0, 7);
    b.setElement(0, 1, 8);
    b.setElement(0, 2, 9);
    b.setElement(1, 0, 10);
    b.setElement(1, 1, 11);
    b.setElement(1, 2, 12);

    std::cout << "A:\n" << a;
    std::cout << "B:\n" << b;
    std::cout << "A + B:\n" << (a + b);

    // 2x3 * 3x2 = 2x2
    Matrix<int> c(3, 2);
    c.setElement(0, 0, 1);
    c.setElement(0, 1, 2);
    c.setElement(1, 0, 3);
    c.setElement(1, 1, 4);
    c.setElement(2, 0, 5);
    c.setElement(2, 1, 6);

    std::cout << "C:\n" << c;
    std::cout << "A * C:\n" << (a * c);

    // dimension mismatch
    std::cout << "A * B (mismatch):\n" << (a * b);

    // copy and move
    Matrix<int> d = a;
    std::cout << "D (copy of A):\n" << d;

    Matrix<double> e(2, 2);
    e.setElement(0, 0, 1.5);
    e.setElement(0, 1, 2.5);
    e.setElement(1, 0, 3.5);
    e.setElement(1, 1, 4.5);
    std::cout << "E (double):\n" << e;
}
