#ifndef LINE_H
#define LINE_H

#include "Point.h"

class Line
{
private:
    Point start, end;

public:
    Line();
    Line(const Point &start, const Point &end);

    Point getStart() const;
    Point getEnd() const;
    void setStart(const Point &p);
    void setEnd(const Point &p);

    double length() const;
    Point midpoint() const;
    bool isParallelTo(const Line &other) const;
    bool contains(const Point &p) const;
};

#endif
