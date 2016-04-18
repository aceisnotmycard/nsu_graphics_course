#ifndef MODEL_H
#define MODEL_H

#include <QJsonObject>


class IModel {
public:
    virtual QJsonObject toJSON() const = 0;
    virtual void fromJSON(const QJsonObject& jsonObject) = 0;
};

#endif // MODEL_H
