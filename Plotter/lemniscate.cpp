#include "lemniscate.h"
#include "point.h"
#include <cmath>
#include <QString>

#include <QDebug>


Lemniscate::Lemniscate(int x1, int y1, int x2, int y2)
    : focus1(x1, y1), focus2(x2, y2)
{
    error = 0;
}

void Lemniscate::draw(QImage *pBackBuffer) const
{
    Point cur = findStartPoint();
    int error = 1000;
    qDebug() << cur.desc();
    cur.draw(pBackBuffer);
    Point center = (focus1 - focus2).shift();
//    while ((cur - center).absSquared() > 2) {
//        auto next = findNextPoint(cur, error);
//        cur = next.first;
//        error = next.second;
//    }
    for (int i = 0; i < 100; ++i) {
        auto next = findNextPoint(cur, error);
        cur = next.first;
        error = next.second;
        cur.draw(pBackBuffer);
    }
}

std::pair<Point, int> Lemniscate::findNextPoint(const Point& current, int prev_error) const {
    std::map<Point, int> neighbours = {
        { Point(-1, -1),    0 },
        { Point(-1, 0),     0 },
        { Point(-1, 1),     0 },
        { Point(0, -1),     0 },
        { Point(0, 1),      0 },
        { Point(1, -1),     0 },
        { Point(1, 0),      0 },
        { Point(1, 1),      0 }
    };

    for (auto& n : neighbours) {
        Point maybeNext = n.first + current;
        n.second = (maybeNext - focus1).absSquared() * (maybeNext - focus2).absSquared() - (focus1 - focus2).shift().absSquared();
    }
    auto it = std::min_element(neighbours.begin(), neighbours.end(), [](std::pair<Point, int>& l, std::pair<Point, int>& r) -> bool {
        return l.second < r.second && (l.second * prev_error) < 0;
    });

    return *it;
}

Point Lemniscate::findStartPoint() const {
    Point c = (focus1 - focus2).shift().abs();
    Point left = focus1 - c;
    Point right = focus1;
    Point center = (left + right).shift();
    while ((right-left).absSquared() > 2) {
        center = (left + right).shift();
        if (center.absSquared() < 2 * c.absSquared()) {
            left = center;
        } else {
            right = center;
        }
    }
    return center;
}

QString Lemniscate::desc() const
{
    return QString("Leminiscate { (%1, %2), (%3, %4) }").arg(
                QString::number(focus1.x), QString::number(focus1.y),
                QString::number(focus2.x), QString::number(focus2.y)
    );
}
