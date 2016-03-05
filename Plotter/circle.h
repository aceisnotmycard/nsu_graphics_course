#ifndef CIRCLE_H
#define CIRCLE_H

#include "drawable.h"


class Circle : public IDrawable
{
public:
    Circle(int x, int y, int r);
    virtual void draw(QImage *pBackBuffer) const;
    virtual QString desc() const;

    void setX(int x) { center_x = x; }
    void setY(int y) { center_y = y; }
    int getX() const { return center_x; }
    int getY() const { return center_y; }
private:
  int center_x;
  int center_y;
  int r;
};

#endif // CIRCLE_H
