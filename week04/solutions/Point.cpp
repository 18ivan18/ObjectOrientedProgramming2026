#include "Point.h"
#include <cmath>

Point::Point() : x(0), y(0)
{
}

Point::Point(double x, double y) : x(x), y(y)
{
}

double Point::getX() const
{
    return x;
}

double Point::getY() const
{
    return y;
}

void Point::setX(double x)
{
    this->x = x;
}

void Point::setY(double y)
{
    this->y = y;
}

double Point::distance(const Point &to) const
{
    double dx = x - to.x;
    double dy = y - to.y;
    return sqrt(dx * dx + dy * dy);
}

Point Point::midpoint(const Point &other) const
{
    return Point((x + other.x) / 2, (y + other.y) / 2);
}

double distance(const Point &a, const Point &b)
{
    return a.distance(b);
}