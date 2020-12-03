#include "mainwindow.h"

#include <QVBoxLayout>
#include <QSizePolicy>
#include <QHBoxLayout>
#include <QResource>

MainWindow::MainWindow() {
    setWindowTitle("Car Simulator");

    auto *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    auto *centralLayout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(centralLayout);

    auto *indicatorsWidget = new QWidget(centralWidget);
    auto *indicatorsLayout = new QHBoxLayout(indicatorsWidget);
    indicatorsWidget->setLayout(indicatorsLayout);

    indicator = new Indicator(":/assets/scared.png", ":/assets/scared.png");
    indicatorsLayout->addWidget(indicator);
    connect(this, SIGNAL(switchLights()), indicator, SLOT(switchState()));
    centralLayout->addWidget(indicatorsWidget);

    speedometer = new QLCDNumber(centralWidget);
    speedometer->setStyleSheet("background-color:black; color:white");
    centralLayout->addWidget(speedometer);
    speedometer->display(speed);

    //setMinimumSize(640, 480);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Up:
            changeSpeed(ACCELERATION);
            break;
        case Qt::Key_Down:
            changeSpeed(-ACCELERATION);
            break;
        case Qt::Key_Q:
            emit(switchLights());
            break;
        default:
            break;
    }
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter;
    setPalette(QPalette(Qt::black));
    setAutoFillBackground(true);
}

void MainWindow::changeSpeed(int increase) {
    speed += increase;
    if (speed < 0) {
        speed = 0;
    }
    speedometer->display(speed);
}