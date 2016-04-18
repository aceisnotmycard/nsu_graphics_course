#include "bezier.h"
#include "font.h"
#include "line.h"
#include "tools.h"

#include <QDebug>
#include <QJsonArray>
#include <cmath>
#include <initializer_list>

Font::Font(const std::vector<std::vector<BezierPoint>>& figures) : figures(figures), x(0), y(0), scale(0), is_filled(true), is_outlined(true) {}

Font::Font(const QJsonObject &json)
{
    fromJSON(json);
}

void Font::draw(QImage *pBackBuffer, QRgb fillColor)
{
    for (auto figure : figures) {
        if (is_filled) {
            fill(pBackBuffer, figure, qRgb(0,0,255));
        }
        if (is_outlined) {
            draw_outline(pBackBuffer, figure, qRgb(0,0,0));
        }
    }
}

void Font::draw_outline(QImage *pBackBuffer, const std::vector<BezierPoint> &points, QRgb color) {
    for (size_t i = 0; i < points.size(); ++i) {
        if (point_at(i+1, points).on_curve) {
            Line(point_at(i, points), point_at(i+1, points)).draw(pBackBuffer, color);
        } else {
            Bezier({ point_at(i, points), point_at(i+1, points), point_at(i+2, points) }).draw(pBackBuffer, color);
            ++i;
        }
    }
}

void Font::fill(QImage *pBackBuffer, const std::vector<BezierPoint> &points, QRgb color) {
    auto minmax_y = std::minmax_element(std::begin(points), std::end(points),
                                        [](const BezierPoint& a, const BezierPoint& b) { return a.y < b.y; }
    );

    double factor = 1 + static_cast<double>(scale) / (scale <= 0 ? 1000 : 100);
    double min_y = (minmax_y.first->y + this->y) * factor;
    double max_y = (minmax_y.second->y + this->y) * factor;
    for (int j = min_y; j < max_y; ++j) {
        double y = static_cast<double>(j);
        std::vector<double> intersections;
        for (size_t i = 0; i < points.size(); ++i) {
            if (point_at(i+1, points).on_curve) {
                Line line_a(point_at(i, points), point_at(i+1, points));
                auto ptr = line_a.trace(y);
                if (ptr != nullptr) {
                    intersections.push_back(ptr->x);
                }
            } else {
                auto res = Bezier({ point_at(i, points), point_at(i+1, points), point_at(i+2, points) }).trace(y);
                intersections.insert(std::end(intersections), std::begin(res), std::end(res));
                ++i;
            }
        }
        std::sort(std::begin(intersections), std::end(intersections), [](int a, int b) { return a < b; });
        for (size_t i = 1; i < intersections.size(); i+= 2) {
                if (std::abs(intersections[i] - intersections[i-1]) > 1) {
                    Line l({ intersections[i-1], y, false }, { intersections[i], y, false });
                    l.draw(pBackBuffer, color);
                }
        }
    }
}

BezierPoint Font::point_at(size_t idx, const std::vector<BezierPoint>& points) const {
    auto p = points[(idx + points.size()) % points.size()];
    p.x += x;
    p.y += y;
    if (scale == 0) {
        return p;
    }
    return BezierPoint::scale(p, scale);
}

QString Font::desc() const
{
    return QString("implement me");
}

QJsonObject Font::toJSON() const
{

}

void Font::fromJSON(const QJsonObject &json)
{
    x = json["position"].toObject()["x"].toInt();
    y = json["position"].toObject()["y"].toInt();


    scale = json["scale"].toInt();
    is_filled = json["fill"].toBool();
    is_outlined = json["outline"].toBool();

    figures.clear();
    QJsonArray glyphs = json["glyphs"].toArray();
    for (auto glyph : glyphs) {
        std::vector<BezierPoint> figure;
        QJsonArray glyph_array = glyph.toObject()["figure1"].toArray();
        for (auto p : glyph_array) {
            figure.push_back(BezierPoint(p.toObject()));
        }
        figures.push_back(figure);
    }
}
