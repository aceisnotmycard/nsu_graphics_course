#include "point.h"
#include <QColor>
#include <cmath>

Point Point::operator-(const Point& b) const
{
    return Point(x - b.x, y - b.y);
}

Point Point::operator+(const Point& b) const
{
    return Point(x + b.x, y + b.y);
}

bool Point::operator==(const Point &b) const
{
    return x == b.x && y == b.y;
}

long long Point::operator*(const Point &b) const
{
    return x * b.x + y * b.y;
}

Point Point::operator*(double val) const
{
    return Point((int) x * val, (int) y * val);
}

bool Point::operator<(const Point &b) const
{
    return x < b.x && y < b.y;
}

Point Point::shift() const
{
    return Point(x >> 1, y >> 1);
}

void Point::draw(QImage *pBackBuffer, QRgb color)
{
    QColor clr(color);
    int delta_x = x + pBackBuffer->width() / 2;
    int delta_y = -y + pBackBuffer->height() / 2;
    if (delta_x > 0 && delta_x < pBackBuffer->width() && delta_y > 0 && delta_y < pBackBuffer->height()) {
        unsigned char* pos = pBackBuffer->bits() + (delta_y * pBackBuffer->bytesPerLine()) + delta_x*3*sizeof(uchar);
        *pos = clr.red();
        *(pos + 1) = clr.green();
        *(pos + 2) = clr.blue();
    }
}

QString Point::desc() const
{
    return QString("Point { %1 %2 }").arg(QString::number(x), QString::number(y));
}

long long Point::absSquared() const
{
    return std::hypot(x, y);
}

Point Point::abs() const
{
    return Point(x > 0 ? x : -x, y > 0 ? y : -y);
}

void Point::set(int newX, int newY)
{
    this->x = newX;
    this->y = newY;
}
