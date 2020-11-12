#ifndef CAR_MAINWINDOW_H
#define CAR_MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLCDNumber>
#include <QKeyEvent>

#define ACCELERATION 1

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event);
private:
    QWidget *centralWidget;
    QLCDNumber *speedometer;

    int speed = 0;
    void changeSpeed(int increase);



signals:
    void speedChanged();
};

#endif //CAR_MAINWINDOW_H
