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
    virtual void draw(QImage *pBackBuffer);
    virtual QString desc() const;
    void setX1(int x1);
    void setY1(int y1);
    void setX2(int x2);
    void setY2(int y2);
private:
    Point focus1;
    Point focus2;
    long long betweenFocuses;
    long long distanceToFocuses(const Point &p) const;
    std::pair<Point, Point> findStartPoints() const;
    std::pair<Point, Point> findNextPoint(const Point& prev, const Point& prevDir) const;
    //long long betweenFocuses() const;
    static const std::vector<Point> directions;

    void drawPart(Point start, Point dir, QImage *pBackBuffer) const;
};

#endif // LEMINISCATE_H
