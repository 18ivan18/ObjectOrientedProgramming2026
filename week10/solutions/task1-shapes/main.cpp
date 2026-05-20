// c++ -std=c++17 -Wall -Wextra Shape.cpp Circle.cpp Rectangle.cpp Triangle.cpp main.cpp -o main
#include "Circle.h"
#include "Rectangle.h"
#include "Shape.h"
#include "Triangle.h"
#include <iostream>

int main()
{
    Circle c(5);
    Rectangle r(4, 6);
    Triangle t(3, 4, 5);

    printInfo(c);
    printInfo(r);
    printInfo(t);

    std::cout << "\n";

    Shape *shapes[] = {new Circle(1), new Rectangle(2, 3), new Triangle(5, 12, 13)};
    int len = 3;
    for (int i = 0; i < len; i++)
    {
        printInfo(*shapes[i]);
        delete shapes[i];
    }
}
