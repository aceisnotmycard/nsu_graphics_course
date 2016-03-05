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
    Point p = findStartPoint();
    qDebug() << p.desc();
    p.draw(pBackBuffer);
}

Point Lemniscate::findNextPoint(const Point& current) const {
}

Point Lemniscate::findStartPoint() const {
    qDebug() << "Lemniscate::findStartPoint() start";
    Point c = (focus1 - focus2).shift().abs();
    qDebug() << "c:\t" << c.desc();
    Point left = focus1 - c;
    qDebug() << "left:\t" << left.desc();
    Point right = focus1;
    qDebug() << "right:\t" << right.desc();
    Point center = (left + right).shift();
    while ((right-left).absSquared() > 2) {
        center = (left + right).shift();
        qDebug() << "center:\t" << center.desc();
        if (center.absSquared() < 2 * c.absSquared()) {
            left = center;
        } else {
            right = center;
        }
    }
    qDebug() << "Lemniscate::findStartPoint() end";
    return center;
}

QString Lemniscate::desc() const
{
    return QString("Leminiscate { (%1, %2), (%3, %4) }").arg(
                QString::number(focus1.x), QString::number(focus1.y),
                QString::number(focus2.x), QString::number(focus2.y)
    );
}
