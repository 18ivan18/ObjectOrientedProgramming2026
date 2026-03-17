#include "Line.h"
#include <cmath>

const double EPS = 1e-9;

Line::Line() : start(0, 0), end(1, 0)
{
}

Line::Line(const Point &s, const Point &e) : start(s), end(e)
{
}

Point Line::getStart() const
{
    return start;
}

Point Line::getEnd() const
{
    return end;
}

void Line::setStart(const Point &p)
{
    start = p;
}

void Line::setEnd(const Point &p)
{
    end = p;
}

double Line::length() const
{
    return start.distance(end);
}

Point Line::midpoint() const
{
    return start.midpoint(end);
}

bool Line::isParallelTo(const Line &other) const
{
    double dx1 = end.getX() - start.getX();
    double dy1 = end.getY() - start.getY();
    double dx2 = other.end.getX() - other.start.getX();
    double dy2 = other.end.getY() - other.start.getY();

    bool vertical1 = fabs(dx1) < EPS;
    bool vertical2 = fabs(dx2) < EPS;
    if (vertical1 && vertical2)
        return true;
    if (vertical1 || vertical2)
        return false;
    return fabs(dy1 / dx1 - dy2 / dx2) < EPS;
}

bool Line::contains(const Point &p) const
{
    double cross = (end.getX() - start.getX()) * (p.getY() - start.getY()) -
                  (end.getY() - start.getY()) * (p.getX() - start.getX());
    return fabs(cross) < EPS;
}
