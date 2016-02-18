#ifndef CIRCLE_H
#define CIRCLE_H

#include <QObject>
#include <QImage>

class Circle : public QObject
{
  Q_OBJECT
public:
  explicit Circle(QObject *parent = 0);
  void setX(int x);
  void setY(int y);
  void setR(int r);
  void draw(QImage* pBackBuffer);
signals:

public slots:
private:
  int center_x;
  int center_y;
  int r;
};

#endif // CIRCLE_H
