#include "point.h"

Point Point::operator-(const Point& b) const
{
    return Point(x - b.x, y - b.y);
}

Point Point::operator+(const Point& b) const
{
    return Point(x + b.x, y + b.y);
}

Point Point::shift() const
{
    return Point(x >> 1, y >> 1);
}

void Point::draw(QImage *pBackBuffer) const
{
    int delta_x = x + pBackBuffer->width() / 2;
    int delta_y = y + pBackBuffer->height() / 2;
    memset(pBackBuffer->bits() + (delta_y * pBackBuffer->bytesPerLine()) + delta_x*3*sizeof(uchar), qRgb(0, 0, 0), sizeof(uchar)*3);
}

QString Point::desc() const
{
    return QString("Point { %1 %2 }").arg(QString::number(x), QString::number(y));
}

int Point::absSquared() const
{
    return x*x + y*y;
}

Point Point::abs() const
{
    return Point(x > 0 ? x : -x, y > 0 ? y : -y);
}