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
    Indicator *indicator;

    bool canAccelerate;
    bool canDecelerate;

public slots:
    void interruptAcceleration();
    void interruptDeceleration();

signals:
    void switchLights();
    void acceleration();
    void deceleration();
};

#endif //CAR_MAINWINDOW_H
