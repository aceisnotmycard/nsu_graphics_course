#ifndef CANVAS_H
#define CANVAS_H

#include "circle.h"

#include <QWidget>

class Canvas : public QWidget
{
public:
    Canvas(Circle* circle);
    void capture(QString filename, int height, int width);
private:
    Circle* circle;
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // CANVAS_H
