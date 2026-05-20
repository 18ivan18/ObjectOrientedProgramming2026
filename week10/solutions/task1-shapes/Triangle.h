#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

class Triangle : public Shape
{
    double a;
    double b;
    double c;

public:
    Triangle(double a, double b, double c);
    double area() const override;
    double perimeter() const override;
    void describe() const override;
};

#endif // TRIANGLE_H
