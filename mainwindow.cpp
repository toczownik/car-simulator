#include "mainwindow.h"
#include "meter.h"

#include <QSizePolicy>
#include <QHBoxLayout>
#include <QResource>

MainWindow::MainWindow() : canAccelerate(true), canDecelerate(true) {
    setWindowTitle("Car Simulator");

    auto *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    auto *centralLayout = new QHBoxLayout(centralWidget);
    centralWidget->setLayout(centralLayout);

    auto *indicatorsWidget = new QWidget(centralWidget);
    auto *indicatorsLayout = new QHBoxLayout(indicatorsWidget);
    indicatorsWidget->setLayout(indicatorsLayout);

    indicator = new Indicator(indicatorsWidget, ":/assets/scared.png", ":/assets/scared.png");
    connect(this, &MainWindow::switchLights, indicator, &Indicator::switchState);
    centralLayout->addWidget(indicatorsWidget);

    auto speedometer = new Meter(centralWidget, 0, 200, 1, 1, ":/assets/speedometer.png");
    centralLayout->addWidget(speedometer);
    connect(this, &MainWindow::deceleration, speedometer, &Meter::decreaseValue);
    connect(this, &MainWindow::acceleration, speedometer, &Meter::increaseValue);

    auto tachometer = new Meter(centralWidget, 1000, 5000, 200, 7, ":/assets/speedometer.png");
    centralLayout->addWidget(tachometer);
    connect(this, &MainWindow::deceleration, tachometer, &Meter::decreaseValue);
    connect(this, &MainWindow::acceleration, tachometer, &Meter::increaseValue);
    connect(tachometer, &Meter::impossibleAcceleration, this, &MainWindow::interruptAcceleration);
    connect(tachometer, &Meter::impossibleDeceleration, this, &MainWindow::interruptDeceleration);

    setMinimumSize(640, 480);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Up:
            if (canAccelerate) {
                emit(acceleration());
                canDecelerate = true;
            }
            break;
        case Qt::Key_Down:
            if (canDecelerate) {
                emit(deceleration());
                canAccelerate = true;
            }
            break;
        case Qt::Key_Q:
            emit(switchLights());
            break;
        default:
            break;
    }
}

void MainWindow::paintEvent(QPaintEvent *event) {
    setPalette(QPalette(Qt::black));
    setAutoFillBackground(true);
}

void MainWindow::interruptAcceleration() {
    canAccelerate = false;
}

void MainWindow::interruptDeceleration() {
    canDecelerate = false;
}
