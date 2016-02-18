#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include "circle.h"

class DrawWidget : public QWidget
{
  Q_OBJECT
public:
  explicit DrawWidget(QWidget *parent = 0);

signals:

public slots:
  void setX(int x);
  void setY(int y);
  void setR(int r);
protected:
  void paintEvent(QPaintEvent *event);
private:
  Circle* circle;
};

#endif // DRAWWIDGET_H
