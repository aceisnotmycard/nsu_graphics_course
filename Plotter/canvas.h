#ifndef CANVAS_H
#define CANVAS_H

#include "drawable.h"

#include <QWidget>

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = 0);
    void addDrawable(std::shared_ptr<IDrawable> drawable);
signals:

public slots:
protected:
    void paintEvent(QPaintEvent *event);
private:
    //void draw(QImage& backBuffer, std::shared_ptr<IDrawable> drawable);
    std::vector<std::shared_ptr<IDrawable>>* drawables;
};

#endif // CANVAS_H
