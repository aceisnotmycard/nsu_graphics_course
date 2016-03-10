#include "lemniscate.h"
#include "point.h"
#include <cmath>
#include <QString>
#include <limits.h>

#include <QDebug>


Lemniscate::Lemniscate(int x1, int y1, int x2, int y2)
    : focus1(x1, y1), focus2(x2, y2)
{

}



void Lemniscate::draw(QImage *pBackBuffer) const
{
    auto points = findStartPoints();

    Point dir(1,1);
    Point cur(points.first.x, points.first.y);
    qDebug() << "Left bottom + right top";
    cur.draw(pBackBuffer);
    while ((cur - points.second).absSquared() > 1) {
        auto pair = findNextPoint(cur, dir);
        cur = pair.first;
        dir = pair.second;
        cur.draw(pBackBuffer);
    }
    qDebug() << "Right bottom + left top";
    while ((cur - points.first).absSquared() > 1) {
        auto pair = findNextPoint(cur, dir);
        cur = pair.first;
        dir = pair.second;
        cur.draw(pBackBuffer);
    }
}

long long Lemniscate::distanceToFocuses(const Point& p) const {
    return 16 * (p-focus1).absSquared() * (p-focus2).absSquared();
}

long long Lemniscate::betweenFocuses() const {
    return (focus1 - focus2).absSquared() * (focus1 - focus2).absSquared();
}

std::pair<Point, Point> Lemniscate::findNextPoint(const Point& prev, const Point& prevDir) const {

    long long minDistance = LLONG_MAX;
    Point nextDir(0,0);
    for(auto& dir : directions) {
        // checking for correct direction
        if (prevDir * dir > 0) {
            if (llabs(distanceToFocuses(dir+prev) - betweenFocuses()) < minDistance) {
                minDistance = llabs(distanceToFocuses(dir+prev) - betweenFocuses());
                nextDir = dir;
            }
        }
    }
    return { nextDir + prev, nextDir };
}

std::pair<Point, Point> Lemniscate::findStartPoints() const {
    Point c = (focus1 - focus2).abs();
    qDebug() << c.desc();
    Point left = focus1-c;
    Point right = focus1;
    Point center(0, 0);
    while ((left - right).absSquared() > 2 ) {
        center = (left + right).shift();
        if (distanceToFocuses(center) > betweenFocuses()) {
            left = center;
        } else {
            right = center;
        }
    }
    return { center, focus1 + focus2 - center };
}

QString Lemniscate::desc() const
{
    return QString("Leminiscate { (%1, %2), (%3, %4) }").arg(
                QString::number(focus1.x), QString::number(focus1.y),
                QString::number(focus2.x), QString::number(focus2.y)
                );
}

void Lemniscate::setX1(int x1)
{
    focus1 = Point(x1, focus1.y);
}

void Lemniscate::setY1(int y1)
{
    focus1 = Point(focus1.x, y1);
}

void Lemniscate::setX2(int x2)
{
    focus2 = Point(x2, focus2.y);
}

void Lemniscate::setY2(int y2)
{
    focus2 = Point(focus2.x, y2);
}

const std::vector<Point> Lemniscate::directions = {
        Point(0, 1),
        Point(1, 1),
        Point(1, 0),
        Point(1, -1),
        Point(0, -1),
        Point(-1, -1),
        Point(-1, 0),
        Point(-1, 1)
    };

