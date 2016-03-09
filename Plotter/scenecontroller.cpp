#include "scenecontroller.h"

SceneController::SceneController()
{
}

void SceneController::setCanvas(Canvas* c) {
    canvas = c;
    circle1 = std::make_shared<Circle>(-100, 0, 2);
    circle2 = std::make_shared<Circle>(100, 0, 2);
    lemniscate = std::make_shared<Lemniscate>(circle1->getX(), circle1->getY(), circle2->getX(), circle2->getY());
    canvas->addDrawable(circle1);
    canvas->addDrawable(circle2);
    canvas->addDrawable(lemniscate);
}

void SceneController::updateX1(int x1)
{
    circle1->setX(x1);
    canvas->repaint();
}

void SceneController::updateX2(int x2)
{
    circle2->setX(x2);
    canvas->repaint();
}

void SceneController::updateY1(int y1)
{
    circle1->setY(y1);
    canvas->repaint();
}

void SceneController::updateY2(int y2)
{
    circle2->setY(y2);
    canvas->repaint();
}
