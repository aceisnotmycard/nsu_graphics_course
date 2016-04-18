#include "bezier.h"
#include "line.h"
#include "point.h"
#include <cmath>

#include <QDebug>


Bezier::Bezier(const std::vector<BezierPoint>& points) : points(points) {}

const double Bezier::COEF = 0.05;
const double Bezier::DELTA = 1e-6;

void Bezier::draw(QImage *pBackBuffer, QRgb color) {
    drawPart(points, pBackBuffer, color);
}

void Bezier::drawPart(const std::vector<BezierPoint>& ps, QImage *pBackBuffer, QRgb color) {
    BezierPoint middle = (ps[0] + ps[2]) * 0.25 + ps[1] * 0.5;
    if (distance(ps[0], ps[2], middle) < COEF) {
        Line l(ps[0], ps[2]);
        l.draw(pBackBuffer, color);
    } else {
        BezierPoint a = (ps[0] + ps[1]) * 0.5;
        BezierPoint b = (ps[1] + ps[2]) * 0.5;
        drawPart({ ps[0], a, middle }, pBackBuffer, color);
        drawPart({ middle, b, ps[2] }, pBackBuffer, color);
    }
}

std::vector<double> Bezier::trace(double y) const {

    std::vector<double> res;

    auto minmax = std::minmax_element(std::begin(points), std::end(points),
                                        [](const BezierPoint& a, const BezierPoint& b) { return a.y < b.y; }
    );

    if (y < minmax.first->y || y >= minmax.second->y) {
        return {};
    }

    auto findX = [&](double t) -> double {
        return (1-t)*(1-t)*points[0].x + 2*(1-t)*t*points[1].x + t*t*points[2].x;
    };

    double B = 2 * (points[1].y - points[0].y);
    double A = points[0].y - 2*points[1].y + points[2].y;
    double C = points[0].y - y;

    double deter = B*B - 4*A*C;

    if (deter >= 0) {
        double t[2];
        t[0] = (-B + std::sqrt(deter)) / (2 * A);
        t[1] = (-B - std::sqrt(deter)) / (2 * A);
        for (int i = 0; i < 2; ++i) {
            if (t[i] >= - Bezier::DELTA && t[i] <= 1 + Bezier::DELTA) {
               res.push_back(findX(t[i]));
            }
        }
    }
    return res;
}

double Bezier::distance(const BezierPoint& a, const BezierPoint& b, const BezierPoint& c) {
    double hypot = std::hypot(b.x - a.x, b.y - a.y);
    if (hypot < 1) {
        return std::hypot(b.x - c.x, b.y - c.y);
    } else {
        return std::abs((b.x - a.x) * c.y - (b.y - a.y) * c.x + b.x * a.y - a.x * b.y) / hypot;
    }
}

QString Bezier::desc() const {
    return QString("implement me plz");
}
