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
//                switch (res.size()) {
//                case 0:
//                    qDebug() << y << "not found";
//                    break;
//                case 1:
//                    qDebug() << y << res[0];
//                    break;
//                case 2:
//                    qDebug() << y << res[0] << " " << res[1];
//                    break;
//                }

                intersections.insert(std::end(intersections), std::begin(res), std::end(res));
                ++i;
            }
        }
        std::sort(std::begin(intersections), std::end(intersections), [](int a, int b) { return a < b; });
        //std::unique(std::begin(intersections), std::end(intersections));

//        qDebug() << "y:" << y << "number of intersections:" << intersections.size();
//        if (intersections.size() > 2) {
//            qDebug() << "Found" << intersections.size() << "intersections" << "at" << y;
//            //Line({ -500, y, false }, {intersections[2], y, false }).draw(pBackBuffer, qRgb(255, 0, 0));
//            for (auto inter : intersections) {
//                qDebug() << inter;
//            }
//        }
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

void Font::setX(int x)
{
    this->x = x;
}

void Font::setY(int y)
{
    this->y = y;
}

int Font::getX() const
{
    return x;
}

int Font::getY() const
{
    return y;
}

int Font::getScale() const
{
    return scale;
}

bool Font::getFill() const
{
    return is_filled;
}

bool Font::getOutline() const
{
    return is_outlined;
}

void Font::setScale(int scale) {
    this->scale = scale;
}

void Font::setFill(bool fill)
{
    is_filled = fill;
}

void Font::setOutline(bool outline)
{
    is_outlined = outline;
}
