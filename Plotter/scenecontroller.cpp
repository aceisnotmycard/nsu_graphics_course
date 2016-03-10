#include "scenecontroller.h"

SceneController::SceneController()
{
}

void SceneController::setCanvas(Canvas* c) {
    canvas = c;

    circle1 = std::make_shared<Circle>(0, 0, 2);
    circle2 = std::make_shared<Circle>(0, 0, 2);
    lemniscate = std::make_shared<Lemniscate>(circle1->getX(), circle1->getY(), circle2->getX(), circle2->getY());
    verticalAxis = std::make_shared<Axis>(true);
    horizontalAxis = std::make_shared<Axis>(false);

    std::vector<std::shared_ptr<IDrawable>> drawables = { circle1, circle2, lemniscate, verticalAxis, horizontalAxis };

    for (auto drawable : drawables) {
        canvas->addDrawable(drawable);
    }
}

void SceneController::updateX1(int x1)
{
    circle1->setX(x1);
    lemniscate->setX1(x1);
    canvas->repaint();
}

void SceneController::updateX2(int x2)
{
    circle2->setX(x2);
    lemniscate->setX2(x2);
    canvas->repaint();
}

void SceneController::updateY1(int y1)
{
    circle1->setY(y1);
    lemniscate->setY1(y1);
    canvas->repaint();
}

void SceneController::updateY2(int y2)
{
    circle2->setY(y2);
    lemniscate->setY2(y2);
    canvas->repaint();
}
