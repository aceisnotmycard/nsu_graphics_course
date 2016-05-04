#include "axis.h"
#include "font.h"
#include "scenecontroller.h"

SceneController::SceneController()
{
}

void SceneController::setCanvas(Canvas* c) {
    canvas = c;
    canvas->setController(this);

    sphere = std::make_shared<Sphere>("sviborg");
    auto axis = std::make_shared<Axis>(Axis::HORIZONTAL);
    drawables = { axis, sphere };

    for (auto drawable : drawables) {
        canvas->addDrawable(drawable);
    }
}

int SceneController::getX() {
    return sphere->center_x;
}

int SceneController::getY() {
    return sphere->center_y;
}

int SceneController::getScale() {
    return sphere->scale;
}

void SceneController::fromJSON(const QJsonObject& json) {
//    font->fromJSON(json);
//    emit fontUpdated(font->x, font->y, font->scale, font->is_filled, font->is_outlined);
//    canvas->update();
}


void SceneController::setX(int x) {
    sphere->center_x = x;
    canvas->update();
}

void SceneController::setY(int y) {
    sphere->center_y = y;
    canvas->update();
}

void SceneController::setScale(int scale) {
    sphere->scale = scale;
    canvas->update();
}

void SceneController::setXrotate(int x_rotate) {
    sphere->x_rotate = x_rotate;
    canvas->update();
}

void SceneController::setYrotate(int y_rotate) {
    sphere->y_rotate = y_rotate;
    canvas->update();
}

void SceneController::setFiltration(bool filtation)
{
    sphere->bilinear = filtation;
    canvas->update();
}

void SceneController::setOutline(bool outline)
{
    //font->is_outlined = outline;
    canvas->update();
}

void SceneController::setFill(bool fill)
{
    //font->is_filled = fill;
    canvas->update();
}
