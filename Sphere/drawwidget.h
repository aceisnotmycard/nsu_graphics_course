#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include "canvas.h"

#include <QWidget>

class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = 0);

    Canvas *getCanvas();
signals:

public slots:
private:
    Canvas* canvas;
};

#endif // DRAWWIDGET_H
