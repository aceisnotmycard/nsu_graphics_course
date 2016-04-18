#ifndef CANVAS_H
#define CANVAS_H


#include "controller.h"
#include "drawable.h"

#include <QWidget>

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = 0);
    void addDrawable(std::shared_ptr<IDrawable> drawable);
    static void capture(const QString& filename, int width, int height, const std::vector<std::shared_ptr<IDrawable>>& drawables);
    void setController(IController *controller);
    void wheelEvent(QWheelEvent *event);
signals:
    void xChanged(int x);
    void yChanged(int y);
    void scaleChanged(int scale);
public slots:
protected:
    void paintEvent(QPaintEvent *event);
private:
    static void draw(QImage& backBuffer, const std::vector<std::shared_ptr<IDrawable> > &drawables);
    std::vector<std::shared_ptr<IDrawable>>* drawables;
    QPoint start_pos;
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    IController* controller;
};

#endif // CANVAS_H
