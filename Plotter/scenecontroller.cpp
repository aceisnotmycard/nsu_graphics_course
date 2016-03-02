#include "scenecontroller.h"

SceneController::SceneController()
{
}

void SceneController::setCanvas(Canvas* c) {
    canvas = c;
    circle1 = std::make_shared<Circle>(5, 5, 10);
    circle2 = std::make_shared<Circle>(50, 50, 10);
    canvas->addDrawable(circle1);
    canvas->addDrawable(circle2);
}

void SceneController::updateX1(int x1)
{
    canvas->repaint();
}

void SceneController::updateX2(int x2)
{
    canvas->repaint();
}

void SceneController::updateY1(int y1)
{
    canvas->repaint();
}

void SceneController::updateY2(int y2)
{
    canvas->repaint();
}
