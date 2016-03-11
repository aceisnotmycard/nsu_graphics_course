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

    void setColor(int red, int green, int blue);
private:
    int color;
    int center_x;
    int center_y;
    int radius;

};

#endif // CIRCLE_H
