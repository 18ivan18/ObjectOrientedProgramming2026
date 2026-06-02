#include <iostream>
#include "Polynomial.h"

int main() {
    // p(x) = 3x^2 + 2x + 1
    Polynomial<2> p;
    p[0] = 1.0;
    p[1] = 2.0;
    p[2] = 3.0;

    std::cout << "p(x) = "; p.print();
    std::cout << "p(0) = " << p.evaluate(0) << "\n"; // 1
    std::cout << "p(1) = " << p.evaluate(1) << "\n"; // 6
    std::cout << "p(2) = " << p.evaluate(2) << "\n"; // 17

    // q(x) = x^2 - x + 4
    Polynomial<2> q;
    q[0] =  4.0;
    q[1] = -1.0;
    q[2] =  1.0;

    std::cout << "\nq(x) = "; q.print();

    // Addition: (p + q)(x) = 4x^2 + x + 5
    Polynomial<2> r = p + q;
    std::cout << "p + q  = "; r.print();

    // Scalar multiply: 2*p(x) = 6x^2 + 4x + 2
    Polynomial<2> s = p * 2.0;
    std::cout << "2 * p  = "; s.print();

    // f(x) = x^3 - 6x^2 + 11x - 6  ==  (x-1)(x-2)(x-3)
    std::cout << "\n";
    Polynomial<3> f;
    f[0] = -6.0;
    f[1] =  11.0;
    f[2] = -6.0;
    f[3] =  1.0;

    std::cout << "f(x) = "; f.print();
    std::cout << "f(1) = " << f.evaluate(1) << "\n"; // 0
    std::cout << "f(2) = " << f.evaluate(2) << "\n"; // 0
    std::cout << "f(3) = " << f.evaluate(3) << "\n"; // 0

    // Zero polynomial
    std::cout << "\n";
    Polynomial<3> zero;
    std::cout << "zero   = "; zero.print(); // 0
}
