#ifndef POINT_H
#define POINT_H

#include "drawable.h"



class Point : public IDrawable
{
public:
    Point(int x, int y) : x(x), y(y) {}
    Point(const Point& a) : x(a.x), y(a.y) {}

    Point() : x(0), y(0) {}
    Point(std::pair<int, int> points) {
        x = points.first;
        y = points.second;
    }

    virtual QString desc() const;

    long long absSquared() const;
    Point abs() const;

    void set(int newX, int newY);

    Point operator-(const Point& b) const;
    Point operator+(const Point& b) const;
    bool operator==(const Point& b) const;
    long long operator*(const Point& b) const;
    Point operator*(double val) const;
    //Point operator=(const Point& b) const;
    bool operator<(const Point& b) const;
    Point shift() const;

    int x;
    int y;
    virtual void draw(QImage *pBackBuffer, QRgb color);
};

#endif // POINT_H
