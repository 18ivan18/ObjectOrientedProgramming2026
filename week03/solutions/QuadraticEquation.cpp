#include "QuadraticEquation.h"
#include <cmath>
#include <iostream>

QuadraticEquation::QuadraticEquation(double a, double b, double c) : a(a), b(b), c(c)
{
}

double QuadraticEquation::getA() const
{
    return a;
}

double QuadraticEquation::getB() const
{
    return b;
}

double QuadraticEquation::getC() const
{
    return c;
}

double QuadraticEquation::getDiscriminant() const
{
    return b * b - 4 * a * c;
}

bool QuadraticEquation::hasRealRoots() const
{
    return a != 0 && getDiscriminant() >= 0;
}

Complex QuadraticEquation::getRoot1() const
{
    Complex result;
    double d = getDiscriminant();
    if (a == 0){
        return result;}
    if (d >= 0)
    {
        result.setReal((-b + sqrt(d)) / (2 * a));
        result.setImaginary(0);
    }
    else
    {
        result.setReal(-b / (2 * a));
        result.setImaginary(sqrt(-d) / (2 * a));
    }
    return result;
}

Complex QuadraticEquation::getRoot2() const
{
    Complex result;
    double d = getDiscriminant();
    if (a == 0){
        return result;}
    if (d >= 0)
    {
        result.setReal((-b - sqrt(d)) / (2 * a));
        result.setImaginary(0);
    }
    else
    {
        result.setReal(-b / (2 * a));
        result.setImaginary(-sqrt(-d) / (2 * a));
    }
    return result;
}

void QuadraticEquation::printSolutions() const
{
    if (a == 0)
    {
        std::cout << "Не е квадратно уравнение (a = 0).\n";
        return;
    }
    double d = getDiscriminant();
    if (d < 0)
    {
        std::cout << "Комплексни корени:\n";
        std::cout << "x1 = ";
        getRoot1().print();
        std::cout << "x2 = ";
        getRoot2().print();
    }
    else if (d == 0)
    {
        std::cout << "Един двоен корен: x = ";
        getRoot1().print();
    }
    else
    {
        std::cout << "Два реални корена:\n";
        std::cout << "x1 = ";
        getRoot1().print();
        std::cout << "x2 = ";
        getRoot2().print();
    }
}
