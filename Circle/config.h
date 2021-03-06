#ifndef CONFIG_H
#define CONFIG_H

#include <QJsonDocument>
#include <QMap>

namespace Config {
void load(QString fileName, QMap<QString, int>& map);
QJsonDocument* save(int x, int y, int r, int height, int width);
}

#endif // CONFIG_H
