#ifndef LEMINISCATE_H
#define LEMINISCATE_H

#include "drawable.h"
#include "point.h"
#include <QImage>
#include <QString>


class Lemniscate : public IDrawable
{
public:
    Lemniscate(int x1, int y1, int x2, int y2);
    virtual void draw(QImage *pBackBuffer) const;
    virtual QString desc() const;
private:
    Point focus1;
    Point focus2;
    long long distanceToFocuses(const Point &p) const;
    std::pair<Point, Point> findStartPoint() const;
    std::pair<Point, Point> findNextPoint(const Point& prev, const Point& prevDir) const;
    long long betweenFocuses() const;
    static const std::vector<Point> neighbours;

};

#endif // LEMINISCATE_H
