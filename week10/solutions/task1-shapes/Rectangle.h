#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape
{
    double width;
    double height;

public:
    Rectangle(double width, double height);
    double area() const override;
    double perimeter() const override;
    void describe() const override;
};

#endif // RECTANGLE_H
