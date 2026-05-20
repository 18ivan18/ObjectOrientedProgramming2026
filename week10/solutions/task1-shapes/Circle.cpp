#include "Circle.h"
#include <cmath>
#include <iostream>

Circle::Circle(double r) : radius(r)
{
}

double Circle::area() const
{
    return M_PI * radius * radius;
}

double Circle::perimeter() const
{
    return 2 * M_PI * radius;
}

void Circle::describe() const
{
    std::cout << "Circle(r=" << radius << "): area=" << area() << ", perimeter=" << perimeter() << "\n";
}
