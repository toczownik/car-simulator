#include "mainwindow.h"
#include "meter.h"

#include <QSizePolicy>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QResource>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>

#define MAX_FUEL 1000
#define INITIAL_FUEL MAX_FUEL/2

MainWindow::MainWindow() : canAccelerate(true), canDecelerate(true), fuelLow(false), turningLeft(false), turningRight(false) {
    setWindowTitle("Car Simulator");

    auto *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    auto *centralLayout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(centralLayout);

    auto *indicatorsWidget = new QWidget(centralWidget);
    auto *indicatorsLayout = new QHBoxLayout(indicatorsWidget);
    indicatorsWidget->setLayout(indicatorsLayout);

    auto leftIndicator = new Indicator(indicatorsWidget, ":/assets/left.png");
    auto rightIndicator = new Indicator(indicatorsWidget, ":/assets/right.png");
    auto conditioningIndicator = new Indicator(indicatorsWidget, ":/assets/air-conditioning.png");
    auto hazardIndicator = new Indicator(indicatorsWidget, ":/assets/hazard.png");
    auto highBeamIndicator = new Indicator(indicatorsWidget, ":/assets/high-beam.png");
    auto lowBeamIndicator = new Indicator(indicatorsWidget, ":/assets/low-beam.png");
    auto parkingIndicator = new Indicator(indicatorsWidget, ":/assets/parking-lights.png");
    auto seatbeltIndicator = new Indicator(indicatorsWidget, ":/assets/seatbelt.png");
    auto fuelIndicator = new Indicator(indicatorsWidget, ":/assets/fuel.png");
    connect(this, &MainWindow::turnLeft, leftIndicator, &Indicator::switchState);
    connect(this, &MainWindow::turnRight, rightIndicator, &Indicator::switchState);
    connect(this, &MainWindow::conditioning, conditioningIndicator, &Indicator::switchState);
    connect(this, &MainWindow::hazard, hazardIndicator, &Indicator::switchState);
    connect(this, &MainWindow::switchHigh, highBeamIndicator, &Indicator::switchState);
    connect(this, &MainWindow::switchLow, lowBeamIndicator, &Indicator::switchState);
    connect(this, &MainWindow::parking, parkingIndicator, &Indicator::switchState);
    connect(this, &MainWindow::seatbelt, seatbeltIndicator, &Indicator::switchState);
    connect(this, &MainWindow::lowFuel, fuelIndicator, &Indicator::switchState);
    indicatorsLayout->addWidget(leftIndicator);
    indicatorsLayout->addWidget(conditioningIndicator);
    indicatorsLayout->addWidget(hazardIndicator);
    indicatorsLayout->addWidget(highBeamIndicator);
    indicatorsLayout->addWidget(lowBeamIndicator);
    indicatorsLayout->addWidget(parkingIndicator);
    indicatorsLayout->addWidget(seatbeltIndicator);
    indicatorsLayout->addWidget(fuelIndicator);
    indicatorsLayout->addWidget(rightIndicator);
    centralLayout->addWidget(indicatorsWidget);
    emit(seatbelt());

    auto metersWidget = new QWidget(centralWidget);
    centralLayout->addWidget(metersWidget);
    metersWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    auto metersLayout = new QHBoxLayout(metersWidget);
    auto speedometer = new Meter(metersWidget, 0, 200, 1, 1, ":/assets/speedometer.png");
    metersLayout->addWidget(speedometer);
    connect(this, &MainWindow::deceleration, speedometer, &Meter::decreaseValue);
    connect(this, &MainWindow::acceleration, speedometer, &Meter::increaseValue);

    auto fuelWidget = new QWidget(metersWidget);
    fuelWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    auto fuelWidgetLayout = new QVBoxLayout(fuelWidget);
    auto fuelBar = new QProgressBar(fuelWidget);
    //fuelWidget->setTextDirection(QProgressBar::BottomToTop);
    fuelBar->setOrientation(Qt::Vertical);
    fuelBar->setRange(0, MAX_FUEL);
    fuel = INITIAL_FUEL;
    fuelBar->setValue(INITIAL_FUEL);
    fuelBar->setStyleSheet("::chunk{background-color:red}");
    fuelBar->setTextVisible(false);
    auto fuelBarLabel = new QLabel(fuelWidget);
    fuelBarLabel->setText("FUEL");
    fuelWidgetLayout->addWidget(fuelBarLabel);
    fuelWidgetLayout->addWidget(fuelBar, 0, Qt::AlignHCenter);
    metersLayout->addWidget(fuelWidget);
    connect(this, &MainWindow::acceleration, fuelBar, &QProgressBar::setValue);

    auto tachometer = new Meter(metersWidget, 1000, 5000, 200, 7, ":/assets/tachometer.png");
    metersLayout->addWidget(tachometer);
    connect(this, &MainWindow::deceleration, tachometer, &Meter::decreaseValue);
    connect(this, &MainWindow::acceleration, tachometer, &Meter::increaseValue);
    connect(tachometer, &Meter::impossibleAcceleration, this, &MainWindow::interruptAcceleration);
    connect(tachometer, &Meter::impossibleDeceleration, this, &MainWindow::interruptDeceleration);

    auto middle = new QWidget;
    middle->setWindowTitle("Middle Board");
    auto middleLayout = new QVBoxLayout(middle);
    middle->setLayout(middleLayout);
    auto radioOn = new QPushButton(middle);
    middleLayout->addWidget(radioOn);
    middle->show();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Up:
            if (canAccelerate) {
                fuel--;
                if (fuel <= MAX_FUEL/10) {
                    if (!fuelLow) fuelLow = true;
                    else emit(lowFuel());
                }
                emit(acceleration(fuel));
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
            emit(conditioning());
            break;
        case Qt::Key_E:
            emit(hazard());
            break;
        case Qt::Key_R:
            emit(switchHigh());
            break;
        case Qt::Key_T:
            emit(switchLow());
            break;
        case Qt::Key_Y:
            emit(parking());
            break;
        case Qt::Key_U:
            emit(seatbelt());
            break;
        case Qt::Key_Left:
            if (turningRight) {
                emit(turnRight());
                turningRight = false;
            }
            turningLeft = true;
            emit(turnLeft());
            break;
        case Qt::Key_Right:
            if (turningLeft) {
                emit(turnLeft());
                turningLeft = false;
            }
            turningRight = true;
            emit(turnRight());
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
