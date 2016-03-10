#ifndef AXIS_H
#define AXIS_H

#include "drawable.h"



class Axis : public IDrawable
{
public:
    Axis(bool isVertical);

    virtual void draw(QImage *pBackBuffer) const;
    virtual QString desc() const;
private:
    bool isVertical;
};

#endif // AXIS_H
