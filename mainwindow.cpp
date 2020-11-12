#include "mainwindow.h"

MainWindow::MainWindow() {
    setWindowTitle("Car Simulator");

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    speedometer = new QLCDNumber(centralWidget);
    speedometer->display(speed);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Up:
            changeSpeed(ACCELERATION);
            break;
        case Qt::Key_Down:
            changeSpeed(-ACCELERATION);
            break;
        default:
            break;
    }
}

void MainWindow::changeSpeed(int increase) {
    speed += increase;
    speedometer->display(speed);
}