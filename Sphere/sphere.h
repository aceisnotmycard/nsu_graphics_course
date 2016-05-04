#ifndef SPHERE_H
#define SPHERE_H

#include "drawable.h"
#include "model.h"


typedef std::pair<double, double> dcoords;
typedef std::pair<int, int> icoords;

class Sphere : public IDrawable, public IModel
{
public:
    Sphere(const QString &texture_filename);
    int center_x;
    int center_y;
    int scale;
    int x_rotate;
    int y_rotate;
    bool bilinear;
    // IModel interface
public:
    virtual QJsonObject toJSON() const override;
    virtual void fromJSON(const QJsonObject &jsonObject) override;

    // IDrawable interface
public:
    virtual void draw(QImage *pBackBuffer, QRgb color) override;
    virtual QString desc() const override;

private:
    static const int RADIUS;
    double r() const;

    std::unique_ptr<QImage> texture_file;

    QColor texture(const dcoords &uv) const;
    dcoords project_cartesian(const dcoords &xy) const;
    QColor get_color(int x, int y) const;
    QColor nearest_filtration(const dcoords &uv) const;
    QColor bilinear_filtration(const dcoords &uv) const;
};

#endif // SPHERE_H
