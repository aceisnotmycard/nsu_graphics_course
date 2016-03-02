#ifndef SCENECONTROLLER_H
#define SCENECONTROLLER_H

#include "canvas.h"
#include "circle.h"
#include "drawable.h"



class SceneController : public QObject
{
    Q_OBJECT
public:
    SceneController();
    void setCanvas(Canvas *c);
public slots:
    void updateX1(int x1);
    void updateX2(int x2);
    void updateY1(int y1);
    void updateY2(int y2);
private:
    Canvas* canvas;
    std::shared_ptr<Circle> circle1;
    std::shared_ptr<Circle> circle2;
};

#endif // SCENECONTROLLER_H
