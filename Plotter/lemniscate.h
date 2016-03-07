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
    Point findStartPoint() const;
    Point findNextPoint(const Point& current) const;
    int error;
    std::pair<Point, int> findNextPoint(const Point &current, int prev_error) const;
};

#endif // LEMINISCATE_H
