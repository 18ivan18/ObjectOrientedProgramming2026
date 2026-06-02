#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include "../task8-array/Array.h"

// Polynomial<N> represents a polynomial of degree N:
//   p(x) = coeffs[0] + coeffs[1]*x + coeffs[2]*x^2 + ... + coeffs[N]*x^N

template<size_t N>
class Polynomial {
    Array<double, N + 1> coeffs;

public:
    Polynomial() {} // Array default-constructs all coefficients to 0.0

    double& operator[](size_t i) {
        return coeffs[i];
    }

    const double& operator[](size_t i) const {
        return coeffs[i];
    }

    size_t degree() const {
        return N;
    }

    // Horner's method: c0 + x*(c1 + x*(c2 + ... + x*cN))
    // Requires only N multiplications instead of 1+2+...+N
    double evaluate(double x) const {
        double result = coeffs[N];
        for (int i = static_cast<int>(N) - 1; i >= 0; i--) {
            result = result * x + coeffs[i];
        }
        return result;
    }

    Polynomial<N> operator+(const Polynomial<N>& other) const {
        Polynomial<N> result;
        for (size_t i = 0; i <= N; i++) {
            result[i] = coeffs[i] + other[i];
        }
        return result;
    }

    Polynomial<N> operator*(double scalar) const {
        Polynomial<N> result;
        for (size_t i = 0; i <= N; i++) {
            result[i] = coeffs[i] * scalar;
        }
        return result;
    }

    void print() const {
        bool printed = false;

        for (int i = static_cast<int>(N); i >= 0; i--) {
            double c = coeffs[static_cast<size_t>(i)];
            if (c == 0.0) { continue; }

            // Sign and separator
            if (printed) {
                if (c > 0) { std::cout << " + "; }
                else       { std::cout << " - "; c = -c; }
            } else if (c < 0) {
                std::cout << "-";
                c = -c;
            }

            // Value and power
            if (i == 0) {
                std::cout << c;
            } else if (i == 1) {
                if (c != 1.0) { std::cout << c; }
                std::cout << "x";
            } else {
                if (c != 1.0) { std::cout << c; }
                std::cout << "x^" << i;
            }

            printed = true;
        }

        if (!printed) { std::cout << "0"; }
        std::cout << "\n";
    }
};

#endif // POLYNOMIAL_H
