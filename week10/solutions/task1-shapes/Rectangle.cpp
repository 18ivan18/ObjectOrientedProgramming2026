#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle(double w, double h) : width(w), height(h)
{
}

double Rectangle::area() const
{
    return width * height;
}

double Rectangle::perimeter() const
{
    return 2 * (width + height);
}

void Rectangle::describe() const
{
    std::cout << "Rectangle(" << width << "x" << height << "): area=" << area() << ", perimeter=" << perimeter()
              << "\n";
}
