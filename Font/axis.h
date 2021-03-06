#ifndef AXIS_H
#define AXIS_H

#include "drawable.h"



class Axis : public IDrawable
{
public:
    Axis(bool isVertical);

    virtual void draw(QImage *pBackBuffer, QRgb color);
    virtual QString desc() const;

    static const bool VERTICAL;
    static const bool HORIZONTAL;
private:
    bool isVertical;
};

#endif // AXIS_H
