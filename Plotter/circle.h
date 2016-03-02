#ifndef CIRCLE_H
#define CIRCLE_H

#include "drawable.h"


class Circle : public IDrawable
{
public:
    Circle(int x, int y, int r);
    virtual void draw(QImage *pBackBuffer) const;
    virtual QString desc() const;
private:
  int center_x;
  int center_y;
  int r;
};

#endif // CIRCLE_H
