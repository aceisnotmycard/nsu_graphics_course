#ifndef CONFIG_H
#define CONFIG_H

#include <QJsonDocument>
#include <QMap>

namespace Config {
    QMap<QString, int>* load(const QString &fileName);

    QJsonDocument* save(int x1, int y1, int x2, int y2, int height, int width);
}

#endif // CONFIG_H
