#ifndef QUADRATIC_EQUATION_H
#define QUADRATIC_EQUATION_H

#include "Complex.h"

class QuadraticEquation
{
private:
    double a, b, c;

public:
    QuadraticEquation(double a, double b, double c);

    double getA() const;
    double getB() const;
    double getC() const;

    double getDiscriminant() const;
    bool hasRealRoots() const;

    Complex getRoot1() const;
    Complex getRoot2() const;
    void printSolutions() const;
};

#endif
