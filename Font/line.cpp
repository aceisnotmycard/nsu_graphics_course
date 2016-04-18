#include "line.h"
#include <cmath>

#include <QColor>
#include <QDebug>

const double Line::DELTA = 1e-6;

Line::Line(const BezierPoint &a, const BezierPoint &b) : a(a), b(b) {}

// TODO: Refactor
void Line::draw(QImage *pBackBuffer, QRgb color) {
    if (isHorizontal()) {
        drawHorizontal(pBackBuffer, color);
    } else {
        drawGeneral(pBackBuffer, color);
    }
}

BezierPoint *Line::trace(double y_in)
{
    double x1 = a.x;
    double x2 = b.x;
    double y1 = a.y;
    double y2 = b.y;

    if (y_in < std::min(y1, y2) || y_in >= std::max(y1, y2)) {
        return nullptr;
    }

    double d = (y1-y2) * 2;
    if (d == 0) {
        return nullptr;
    } else {
        double x = ((x1 * y2 - y1 * x2) * -2 + (x1 - x2) * y_in * 2) / d;
        if (x < std::min(x1, x2) - Line::DELTA || x > std::max(x1, x2) + Line::DELTA) {
            return nullptr;
        }
        double y = 2 * (y1 - y2) * y_in / d;
        if (y < std::min(y1, y2) - Line::DELTA || y > std::max(y1, y2) + Line::DELTA) {
            return nullptr;
        }
        return new BezierPoint(x, y, true);
    }
}

BezierPoint *Line::intersection(const Line &l1, const Line &l2) {
    double x1 = l1.a.x;
    double x2 = l1.b.x;
    double x3 = l2.a.x;
    double x4 = l2.b.x;

    double y1 = l1.a.y;
    double y2 = l1.b.y;
    double y3 = l2.a.y;
    double y4 = l2.b.y;

    double x12 = x1-x2;
    double x34 = x3-x4;
    double y34 = y3-y4;
    double y12 = y1-y2;

    double d = x12 * y34 - y12 * x34;
    if (d == 0) {
        return nullptr;
    } else {
        double x = ((x1 * y2 - y1 * x2) * x34 - x12 * (x3 * y4 - y3 * x4)) / d;
        if (x < std::min(x1, x2) || x > std::max(x1, x2) || x < std::min(x3, x4) || x > std::max(x3, x4)) {
            return nullptr;
        }

        double y = ((x1 * y2 - y1 * x2) * y34 - y12 * (x3 * y4 - y3 * x4)) / d;
        if (y < std::min(y1, y2) || y > std::max(y1, y2) || y < std::min(y3, y4) || y > std::max(y3, y4)) {
            return nullptr;
        }

        return new BezierPoint(x, y, true);
    }
}

void Line::drawHorizontal(QImage *pBackBuffer, QRgb color) {
    QColor clr(color);
    int y = static_cast<int>(-a.y + pBackBuffer->height() / 2);
    int min_x = std::round(std::min(a.x, b.x) + pBackBuffer->width() / 2);
    int max_x = std::round(std::max(a.x, b.x) + pBackBuffer->width() / 2);
    int start_x = (min_x < 0) ? 0 : std::min(pBackBuffer->width(), min_x);
    int end_x = (max_x > pBackBuffer->width()) ? pBackBuffer->width() : std::max(0, max_x);
    for (int x = start_x; x < end_x; x++) {
        unsigned char* pos = pBackBuffer->bits() + (y * pBackBuffer->bytesPerLine()) + x*3*sizeof(uchar);
        *pos = clr.red();
        *(pos + 1) = clr.green();
        *(pos + 2) = clr.blue();
    }
}


// https://github.com/ssloy/tinyrenderer/wiki/Lesson-1:-Bresenham’s-Line-Drawing-Algorithm
void Line::drawGeneral(QImage *pBackBuffer, QRgb color) {
    bool steep = std::abs(b.y - a.y) > std::abs(b.x - a.x);
    if (steep) {
        std::swap(a.x, a.y);
        std::swap(b.x, b.y);
    }
    if(a.x > b.x) {
        std::swap(a.x, b.x);
        std::swap(a.y, b.y);
    }
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    double error = dx / 2;

    int ystep = (a.y < b.y) ? 1 : -1;
    int y = std::round(a.y);

    for(int x = std::round(a.x); x <= b.x; x++) {
        if (steep) {
            Point(y, x).draw(pBackBuffer, color);
        } else {
            Point(x, y).draw(pBackBuffer, color);
        }
        error -= dy;
        if (error < 0) {
            y += ystep;
            error += dx;
        }
    }
}

bool Line::isHorizontal() {
    return a.y == b.y;
}

QString Line::desc() const
{
    return QString("Line { %1 %2 : %3 %4 }").arg(QString::number(a.x), QString::number(a.y), QString::number(b.x), QString::number(b.y));
}
