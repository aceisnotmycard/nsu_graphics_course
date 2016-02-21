#ifndef CANVAS_H
#define CANVAS_H

#include "circle.h"

#include <QWidget>

class Canvas : public QWidget
{
public:
    Canvas(Circle* circle);
    static void capture(Circle* circle, QString filename, int height, int width);
private:
    static void draw(QImage& backBuffer, Circle* cirlce);
    Circle* circle;
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // CANVAS_H
