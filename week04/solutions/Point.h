#ifndef POINT_H
#define POINT_H

class Point
{
private:
    double x;
    double y;

public:
    Point();
    Point(double x, double y);

    double getX() const;
    double getY() const;
    void setX(double x);
    void setY(double y);

    double distance(const Point &to) const;
    Point midpoint(const Point &other) const;
};

double distance(const Point &a, const Point &b);

#endif
