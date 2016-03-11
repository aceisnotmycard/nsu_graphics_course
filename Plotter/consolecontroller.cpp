#include "consolecontroller.h"
#include "config.h"
#include "canvas.h"
#include "circle.h"
#include "lemniscate.h"
#include "axis.h"
#include <QDebug>
#include <iostream>

int ConsoleController::start(int argc, char** argv)
{
    if (argc != 3) {
        std::cout << "Usage: ./Plotter {configuration filename} {output filename}"
    }

    auto configMap = *Config::load(argv[1]);

    auto circle1 = std::make_shared<Circle>(configMap["x1"], configMap["y1"], 2);
    auto circle2 = std::make_shared<Circle>(configMap["x2"], configMap["y2"], 2);
    auto lemniscate = std::make_shared<Lemniscate>(circle1->getX(), circle1->getY(), circle2->getX(), circle2->getY());
    auto verticalAxis = std::make_shared<Axis>(true);
    auto horizontalAxis = std::make_shared<Axis>(false);

    std::vector<std::shared_ptr<IDrawable>> drawables = { circle1, circle2, lemniscate, verticalAxis, horizontalAxis };
    Canvas::capture(argv[2], configMap["width"], configMap["height"], drawables);

    return 0;
}
