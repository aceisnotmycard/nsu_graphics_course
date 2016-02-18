#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include "canvas.h"
#include "circle.h"

class DrawWidget : public QWidget
{
  Q_OBJECT
public:
  explicit DrawWidget(QWidget *parent = 0);
public slots:
  void setX(int x);
  void setY(int y);
  void setR(int r);
private:
  Circle* circle;
  Canvas* canvas;
};

#endif // DRAWWIDGET_H
