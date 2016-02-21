#include "circle.h"
#include <QImage>
#include <QDebug>
#include <cmath>

Circle::Circle(QObject *parent) : QObject(parent), center_x(0), center_y(0), r(1) {}

void Circle::setX(int x) {
    this->center_x = x;
}

void Circle::setY(int y) {
    this->center_y = y;
}

void Circle::setR(int r) {
    this->r = r;
}

// TODO: сделать построчно
void Circle::draw(QImage *pBackBuffer) {

    if (!pBackBuffer) {
        return;
    }

    auto delta_x = center_x + pBackBuffer->width() / 2;
    auto delta_y = center_y + pBackBuffer->height() / 2;

    auto start_y = std::max(0, -r + delta_y);
    auto end_y = std::min(pBackBuffer->height(), delta_y + r);

    auto width = [=](int y, int r) {
        return (int) sqrt(r*r - (delta_y-y)*(delta_y-y));
    };
    auto drawHorizontalLine = [=](int y, int x_from, int length, QRgb color) {
        memset(pBackBuffer->bits() + (y * pBackBuffer->bytesPerLine()) + x_from*3*sizeof(uchar), color, length*sizeof(uchar)*3);
    };

    for (int y = start_y; y < end_y; y++) {
        auto w = width(y, r);
        auto start_x = (delta_x-w < 0) ? 0 : std::min(pBackBuffer->width(), delta_x-w);
        auto end_x = (delta_x+w > pBackBuffer->width()) ? pBackBuffer->width() : std::max(0, delta_x + w);
        drawHorizontalLine(y, start_x, end_x-start_x+1, qRgb(255,255,255));
    }
}
