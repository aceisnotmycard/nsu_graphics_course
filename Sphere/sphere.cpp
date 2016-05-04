#include "point.h"
#include "sphere.h"
#include <QColor>
#include <QDebug>
#include <cmath>
#include <tgmath.h>

Sphere::Sphere(const QString & texture_filename): center_x(0), center_y(0), scale(1), x_rotate(0), y_rotate(0), bilinear(false) {
    texture_file = std::make_unique<QImage>();
    if (!texture_file->load(texture_filename)) {
        qDebug() << texture_filename << "not found";
    } else {
        qDebug() << "Succesfully loaded texture";
    }
}

void Sphere::draw(QImage *pBackBuffer, QRgb color)
{
    for (int y = -r(); y < r(); ++y) {
        for (int x = - r(); x < r(); ++x) {
            if (std::hypot(x, y) > r()) {
                continue;
            }
            QColor t = texture(project_cartesian({x, y}));
            Point(x + center_x, y + center_y).draw(pBackBuffer, t.rgb());
        }
    }
}

dcoords Sphere::project_cartesian(const dcoords & xy) const {

    double x = xy.first;
    double y = xy.second;
    double z = std::sqrt(r()*r() - x*x - y*y);

    double theta = std::acos(y / r());
    double phi = std::atan2(z, x);

    double u = 1 - std::fmod(phi + M_PI, 2*M_PI) / (2*M_PI);
    double v = std::fmod(theta, M_PI) / M_PI;

    return { u, v };
}

QColor Sphere::texture(const dcoords & uv) const {
    return bilinear ? bilinear_filtration(uv) : nearest_filtration(uv);
}

QColor Sphere::nearest_filtration(const dcoords & uv) const {
    int x = std::round(texture_file->width() * uv.first + 0.5);
    int y = std::round(texture_file->height() * uv.second + 0.5);
    return get_color(x, y);
}

QColor Sphere::bilinear_filtration(const dcoords & uv) const {
    auto calc_color = [](int u_ratio, int v_ratio, const std::vector<QColor>& cs, std::function<int(QColor)> f) {
        return (f(cs[0]) * (1-u_ratio) + f(cs[1]) * u_ratio) * (1-v_ratio) +
               (f(cs[2]) * (1-u_ratio) + f(cs[3]) * u_ratio) * v_ratio;
    };
    double u = texture_file->width() * uv.first + 0.5;
    double v = texture_file->height() * uv.second + 0.5;
    int x = std::floor(u);
    int y = std::floor(v);
    double u_ratio = u - x;
    double v_ratio = v - y;
    std::vector<QColor> colors{ get_color(x, y), get_color(x+1, y), get_color(x, y+1), get_color(x+1, y+1) };
    int r = std::round(calc_color(u_ratio, v_ratio, colors, &QColor::red));
    int g = std::round(calc_color(u_ratio, v_ratio, colors, &QColor::green));
    int b = std::round(calc_color(u_ratio, v_ratio, colors, &QColor::blue));
    return QColor(r, g, b);
}

QColor Sphere::get_color(int x, int y) const {
    int nx = std::fmod(texture_file->width() + x + x_rotate, texture_file->width());
    int ny = std::fmod(texture_file->height() + y + y_rotate, texture_file->height());
    return QColor(texture_file->pixel(nx, ny));
}

double Sphere::r() const {
    double factor = 1 + static_cast<double>(scale) / (scale <= 0 ? 1000 : 100);
    return factor * RADIUS;
}

QString Sphere::desc() const {}

QJsonObject Sphere::toJSON() const {}

void Sphere::fromJSON(const QJsonObject &jsonObject) {}

const int Sphere::RADIUS = 256;
