#ifndef POINT_H
#define POINT_H

#include "drawable.h"



class Point : public IDrawable
{
public:
    Point(int x, int y) : x(x), y(y) {}
    Point(const Point& a) : x(a.x), y(a.y) {}

    virtual void draw(QImage *pBackBuffer) const;
    virtual QString desc() const;

    int absSquared() const;
    Point abs() const;

    Point operator-(const Point& b) const;
    Point operator+(const Point& b) const;
    Point shift() const;

    int x;
    int y;
};

#endif // POINT_H
