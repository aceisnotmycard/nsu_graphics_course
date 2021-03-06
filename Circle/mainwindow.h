#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "drawwidget.h"
#include "controls.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    DrawWidget* drawWidget;
    Controls* controls;
    void updateUI(QMap<QString, int>& map);

private slots:
    void saveConfig();
    void openConfig();
};

#endif // MAINWINDOW_H
