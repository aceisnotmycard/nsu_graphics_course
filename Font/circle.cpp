#include "circle.h"
#include <cmath>

Circle::Circle(int x, int y, int r) : center_x(x), center_y(y), radius(r)
{
}

void Circle::draw(QImage *pBackBuffer, QRgb color)
{
    if (!pBackBuffer) {
        return;
    }

    int delta_x = center_x + pBackBuffer->width() / 2;
    int delta_y = center_y + pBackBuffer->height() / 2;
    for (int y = std::max(0, -radius + delta_y - 1); y < std::min(pBackBuffer->height(), delta_y + radius + 1); y++) {
        int w = (int) std::sqrt(radius*radius - (delta_y-y)*(delta_y-y));
        int start_x = (delta_x-w < 0) ? 0 : std::min(pBackBuffer->width(), delta_x-w);
        int end_x = (delta_x+w > pBackBuffer->width()) ? pBackBuffer->width() : std::max(0, delta_x + w + 1);
        memset(pBackBuffer->bits() + (y * pBackBuffer->bytesPerLine()) + start_x*3*sizeof(uchar), color, (end_x - start_x)*sizeof(uchar)*3);
    }
}

QString Circle::desc() const
{
    return QString("Circle { x: %1 y: %2 r: %3 }").arg(QString::number(center_x), QString::number(center_y), QString::number(radius));
}

