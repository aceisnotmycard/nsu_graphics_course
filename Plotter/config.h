#ifndef CONFIG_H
#define CONFIG_H

#include <QJsonDocument>
#include <QMap>

namespace Config {
    QMap<QString, int>* load(const QString &fileName);

    QJsonDocument* save(int x, int y, int r, int height, int width);
}

#endif // CONFIG_H
