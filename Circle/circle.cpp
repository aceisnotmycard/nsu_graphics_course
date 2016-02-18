#include "circle.h"
#include <QImage>
#include <math.h>

Circle::Circle(QObject *parent) : QObject(parent) {

}

void Circle::setX(int x) {
    this->center_x = x;
}

void Circle::setY(int y) {
    this->center_y = y;
}

void Circle::setR(int r) {
    this->r = r;
}

void Circle::draw(QImage *pBackBuffer) {

    if (!pBackBuffer) {
        return;
    }

    uchar* bits = pBackBuffer->bits();
    int delta_x = center_x + pBackBuffer->width() / 2;
    int delta_y = center_y + pBackBuffer->height() / 2;
    for (int y = fmax(0, -r + delta_y); y < fmin(pBackBuffer->height(), delta_y + r); y++) {
        for (int x = fmax(0, -r + delta_x); x < fmin(pBackBuffer->width(), delta_x + r); x++) {
            if (r*r >= (delta_x - x)*(delta_x - x) + (delta_y - y)*(delta_y - y)) {
                memset(bits + (y * pBackBuffer->bytesPerLine()) + x*3*sizeof(uchar), qRgb(255,255,255), sizeof(uchar)*3);
            }
        }
    }
}
