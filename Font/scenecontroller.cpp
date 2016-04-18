#include "axis.h"
#include "font.h"
#include "scenecontroller.h"

SceneController::SceneController()
{
}

void SceneController::setCanvas(Canvas* c) {
    canvas = c;
    canvas->setController(this);
    std::vector<BezierPoint> pts = {
                                       { 59, 416, true  },
                                       { 234, 440, true },
                                       { 241, 272, false },
                                       { 297, 210, true },
                                       { 353, 148, false },
                                    };

    auto axis_x = std::make_shared<Axis>(Axis::VERTICAL);
    auto axis_y = std::make_shared<Axis>(Axis::HORIZONTAL);
    font = std::make_shared<Font>(std::vector<std::vector<BezierPoint>>{pts});

    drawables = { axis_x, axis_y, font };

    for (auto drawable : drawables) {
        canvas->addDrawable(drawable);
    }
}

int SceneController::getX() {
    return font->x;
}

int SceneController::getY() {
    return font->y;
}

int SceneController::getScale() {
    return font->scale;
}

void SceneController::fromJSON(const QJsonObject& json) {
    font->fromJSON(json);
    emit fontUpdated(font->x, font->y, font->scale, font->is_filled, font->is_outlined);
    canvas->update();
}


void SceneController::setX(int x) {
    font->x = x;
    canvas->update();
}

void SceneController::setY(int y) {
    font->y = y;
    canvas->update();
}

void SceneController::setScale(int scale) {
    font->scale = scale;
    canvas->update();
}

void SceneController::setOutline(bool outline)
{
    font->is_outlined = outline;
    canvas->update();
}

void SceneController::setFill(bool fill)
{
    font->is_filled = fill;
    canvas->update();
}
