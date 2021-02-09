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
    bool canAccelerate;
    bool canDecelerate;
    bool fuelLow;
    bool turningLeft;
    bool turningRight;
    int fuel;

public slots:
    void interruptAcceleration();
    void interruptDeceleration();

signals:
    void turnLeft();
    void turnRight();
    void conditioning();
    void hazard();
    void switchHigh();
    void switchLow();
    void parking();
    void seatbelt();
    void lowFuel();
    void acceleration(int newFuel);
    void deceleration();
};

#endif //CAR_MAINWINDOW_H
