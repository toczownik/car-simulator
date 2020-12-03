#ifndef CAR_MAINWINDOW_H
#define CAR_MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLCDNumber>
#include <QKeyEvent>

#include "indicator.h"

#define ACCELERATION 1

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QLCDNumber *speedometer;
    Indicator *indicator;

    int speed = 0;
    void changeSpeed(int increase);

signals:
    void switchLights();
};

#endif //CAR_MAINWINDOW_H
