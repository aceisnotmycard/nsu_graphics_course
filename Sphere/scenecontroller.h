#ifndef SCENECONTROLLER_H
#define SCENECONTROLLER_H

#include "canvas.h"
#include "controller.h"
#include "drawable.h"
#include "font.h"
#include "sphere.h"

class SceneController : public QObject, public IController
{
    Q_OBJECT
public:
    SceneController();
    void setCanvas(Canvas *c);
    void fromJSON(const QJsonObject &json);
    virtual int getX();
    virtual int getY();
    virtual int getScale();
public slots:
    void setX(int x);
    void setY(int y);
    void setScale(int scale);
    void setOutline(bool outline);
    void setFill(bool fill);
    void setXrotate(int x_rotate);
    void setFiltration(bool filtation);
    void setYrotate(int y_rotate);
signals:
    void fontUpdated(int x, int y, int scale, bool fill, bool outline);
private:
    Canvas* canvas;
    std::vector<std::shared_ptr<IDrawable>> drawables;
    std::shared_ptr<Sphere> sphere;
};

#endif // SCENECONTROLLER_H
