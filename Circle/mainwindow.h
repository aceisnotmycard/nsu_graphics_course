#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "drawwidget.h"
#include "controls.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    DrawWidget* drawWidget;
    Controls* controls;
    void updateUI(int width, int height, int x, int y, int r);

private slots:
    void saveConfig();
    void loadConfig();
};

#endif // MAINWINDOW_H
