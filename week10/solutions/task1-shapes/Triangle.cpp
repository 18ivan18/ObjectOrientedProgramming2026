#include "Triangle.h"
#include <cmath>
#include <iostream>

Triangle::Triangle(double a, double b, double c) : a(a), b(b), c(c)
{
}

double Triangle::area() const
{
    double s = (a + b + c) / 2.0;
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

double Triangle::perimeter() const
{
    return a + b + c;
}

void Triangle::describe() const
{
    std::cout << "Triangle(" << a << ", " << b << ", " << c << "): area=" << area() << ", perimeter=" << perimeter()
              << "\n";
}
