#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <QImage>


class IDrawable {
public:
    virtual void draw(QImage *pBackBuffer) const = 0;
    virtual QString desc() const = 0;
};

#endif // DRAWABLE_H
