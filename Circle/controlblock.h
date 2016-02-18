#ifndef CONTROLBLOCK_H
#define CONTROLBLOCK_H

#include <QWidget>
#include <QObject>
#include <QString>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>

#include <functional>

class ControlBlock : public QWidget
{
    Q_OBJECT
public:
    explicit ControlBlock(QWidget* parent=0, std::function<void(int)> callback=0);
    void setLabel(const QString& text);
    void setRange(int min, int max);
signals:
    void valueChanged(int value);
public slots:
    void setValue(int value);
    void upCall(int);
private:
    QLabel* label;
    QSpinBox* spinBox;
    QSlider* slider;
    std::function<void(int)> callback;
};

#endif // CONTROLBLOCK_H
