#ifndef FONT_H
#define FONT_H

#include "bezier.h"
#include "drawable.h"


class Font : public IDrawable, IModel
{
public:
    Font(const std::vector<std::vector<BezierPoint>>& figures);
    Font(const QJsonObject& jsonObject);

    virtual void draw(QImage *pBackBuffer, QRgb color) override;
    virtual QString desc() const override;

    virtual QJsonObject toJSON() const override;
    virtual void fromJSON(const QJsonObject& jsonObject) override;

    int x;
    int y;
    int scale;
    bool is_filled;
    bool is_outlined;
private:
    std::vector<std::vector<BezierPoint>> figures;
    void draw_outline(QImage *pBackBuffer, const std::vector<BezierPoint>& points, QRgb color);
    void fill(QImage *pBackBuffer, const std::vector<BezierPoint>& points, QRgb color);
    // returns scaled point at (idx % size) position
    BezierPoint point_at(size_t idx, const std::vector<BezierPoint>& points) const;
};

#endif // FONT_H
