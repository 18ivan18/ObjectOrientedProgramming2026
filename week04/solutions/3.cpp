// Компилиране: g++ -o 3 3.cpp Point.cpp Line.cpp
#include "Line.h"
#include <iostream>

int main()
{
    Point p1;
    Point p2(3, 4);
    std::cout << "p1: (" << p1.getX() << ", " << p1.getY() << ")\n";
    std::cout << "p2: (" << p2.getX() << ", " << p2.getY() << ")\n";
    std::cout << "Разстояние p1-p2: " << p1.distance(p2) << '\n';

    Point mid = p1.midpoint(p2);
    std::cout << "Среда p1-p2: (" << mid.getX() << ", " << mid.getY() << ")\n";

    Line defaultLine;
    std::cout << "\nЛиния по подразбиране (дължина 1): " << defaultLine.length() << '\n';
    std::cout << "Среда на линията: (" << defaultLine.midpoint().getX() << ", " << defaultLine.midpoint().getY() << ")\n";

    Line line(Point(0, 0), Point(3, 4));
    std::cout << "Линия (0,0)-(3,4): " << line.length() << '\n';
    std::cout << "Съдържа (1.5, 2)? " << (line.contains(Point(1.5, 2)) ? "да" : "не") << '\n';

    Line parallel(Point(0, 1), Point(3, 5));
    std::cout << "Успоредна на (0,0)-(3,4)? " << (line.isParallelTo(parallel) ? "да" : "не") << '\n';
}
