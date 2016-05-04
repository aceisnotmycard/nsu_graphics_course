#ifndef BEZIER_H
#define BEZIER_H

#include "drawable.h"
#include "model.h"
#include "point.h"

#include <QDebug>

struct BezierPoint {
    double x;
    double y;
    bool on_curve;

    BezierPoint(double x, double y, bool on_curve) : x(x), y(y), on_curve(on_curve) {}

    BezierPoint(const BezierPoint& bp) {
        x = bp.x;
        y = bp.y;
        on_curve = bp.on_curve;
    }

    BezierPoint(const QJsonObject& json) {
        x = json["position"].toObject()["x"].toDouble();
        y = json["position"].toObject()["y"].toDouble();
        on_curve = json["oncurve"].toBool();
    }

    BezierPoint operator+(const BezierPoint& bp) const {
        return BezierPoint(x + bp.x, y + bp.y, false);
    }

    BezierPoint operator*(double val) const {
        return BezierPoint(val*x, val*y, on_curve);
    }

    static BezierPoint scale(const BezierPoint& p, int scale) {
        double factor = 1 + static_cast<double>(scale) / (scale <= 0 ? 1000 : 100);
        return p * factor;
    }
};

class Bezier : public IDrawable
{
public:
    Bezier(const std::vector<BezierPoint>& points);

    virtual void draw(QImage *pBackBuffer, QRgb color);
    virtual QString desc() const;

    std::vector<double> trace(double y) const;
private:
    std::vector<BezierPoint> points;
    void drawPart(const std::vector<BezierPoint> &ps, QImage *pBackBuffer, QRgb color);
    double distance(const BezierPoint &a, const BezierPoint &b, const BezierPoint &target);

    static const double COEF;
    static const double DELTA;
};

#endif // BEZIER_H
