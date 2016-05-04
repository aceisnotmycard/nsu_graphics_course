#ifndef LINE_H
#define LINE_H

#include "bezier.h"
#include "drawable.h"
#include "point.h"


class Line : public IDrawable
{
public:
    Line(const BezierPoint& a, const BezierPoint& b);

    virtual QString desc() const;
    bool isHorizontal();
    virtual void draw(QImage *pBackBuffer, QRgb color);

    BezierPoint* trace(double y);
private:
    BezierPoint a;
    BezierPoint b;
    void drawGeneral(QImage *pBackBuffer, QRgb color);
    void drawHorizontal(QImage *pBackBuffer, QRgb color);

    static const double DELTA;
};

#endif // LINE_H
