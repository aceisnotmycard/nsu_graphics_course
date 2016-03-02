#include "circle.h"
#include <cmath>

Circle::Circle(int x, int y, int r)
{
    center_x = x;
    center_y = y;
    this->r = r;
}

void Circle::draw(QImage *pBackBuffer) const
{
    if (!pBackBuffer) {
        return;
    }

    int delta_x = center_x + pBackBuffer->width() / 2;
    int delta_y = center_y + pBackBuffer->height() / 2;

    auto width = [=](int y, int r) {
        return (int) sqrt(r*r - (delta_y-y)*(delta_y-y));
    };
    auto drawHorizontalLine = [=](int y, int x_from, int length, QRgb color) {
        memset(pBackBuffer->bits() + (y * pBackBuffer->bytesPerLine()) + x_from*3*sizeof(uchar), color, length*sizeof(uchar)*3);
    };

    for (int y = std::max(0, -r + delta_y); y < std::min(pBackBuffer->height(), delta_y + r); y++) {
        int w = width(y, r);
        int start_x = (delta_x-w < 0) ? 0 : std::min(pBackBuffer->width(), delta_x-w);
        int end_x = (delta_x+w > pBackBuffer->width()) ? pBackBuffer->width() : std::max(0, delta_x + w);
        drawHorizontalLine(y, start_x, end_x-start_x, qRgb(0, 0, 0));
    }
}

QString Circle::desc() const
{
    return QString("Circle { x: %1 y: %2 r: %3 }").arg(QString::number(center_x), QString::number(center_y), QString::number(r));
}
