#include "mainwindow.h"
#include "meter.h"

#include <QSizePolicy>
#include <QHBoxLayout>
#include <QVBoxLayout>
<<<<<<< HEAD
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>
#include <QSlider>
#include <QTableWidget>
#include <QHeaderView>
=======
#include <QResource>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>
>>>>>>> 07d5cd0ae9622e969e3f723e3241efb88059f230

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
<<<<<<< HEAD
=======
    connect(this, &MainWindow::conditioning, conditioningIndicator, &Indicator::switchState);
>>>>>>> 07d5cd0ae9622e969e3f723e3241efb88059f230
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
<<<<<<< HEAD
=======
    //fuelWidget->setTextDirection(QProgressBar::BottomToTop);
>>>>>>> 07d5cd0ae9622e969e3f723e3241efb88059f230
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
<<<<<<< HEAD
    auto menu = new QWidget(middle);
    auto menuLayout = new QGridLayout(menu);
    middleLayout->addWidget(menu);
    menu->setLayout(menuLayout);
    auto musicButton = new QPushButton(menu);
    musicButton->setText("MUSIC");
    menuLayout->addWidget(musicButton, 0, 0);
    auto mapButton = new QPushButton(menu);
    mapButton->setText("MAP");
    menuLayout->addWidget(mapButton, 0, 1);
    auto bluetoothButton = new QPushButton(menu);
    bluetoothButton->setText("BLUETOOTH");
    menuLayout->addWidget(bluetoothButton, 0, 2);
    connect(bluetoothButton, &QPushButton::clicked, menu, &QWidget::hide);
    auto settingsButton = new QPushButton(menu);
    settingsButton->setText("SETTINGS");
    menuLayout->addWidget(settingsButton, 1, 0);
    connect(settingsButton, &QPushButton::clicked, menu, &QWidget::hide);
    auto airConditioningButton = new QPushButton(menu);
    airConditioningButton->setText("AIR CONDITIONING");
    connect(airConditioningButton, &QPushButton::clicked, menu, &QWidget::hide);
    menuLayout->addWidget(airConditioningButton, 1, 1);

    auto music = new QWidget(middle);
    middleLayout->addWidget(music);
    music->hide();

    auto bluetooth = new QWidget(middle);
    auto bluetoothLayout = new QVBoxLayout(bluetooth);
    bluetooth->setLayout(bluetoothLayout);
    connect(bluetoothButton, &QPushButton::clicked, bluetooth, &QWidget::show);
    auto bluetoothTable = new QTableWidget(2, 2, bluetooth);

    //bluetoothTable->setFixedSize(1, 100);
    auto devicesHeader = new QTableWidgetItem("Detected Devices");
    bluetoothTable->setHorizontalHeaderItem(0, devicesHeader);
    auto connectionHeader = new QTableWidgetItem("Connection");
    bluetoothTable->setHorizontalHeaderItem(1, connectionHeader);
    auto device1 = new QTableWidgetItem("smartphone");
    bluetoothTable->setItem(0, 0, device1);
    auto device2 = new QTableWidgetItem("tablet");
    bluetoothTable->setItem(1, 0, device2);
    auto device1Connection = new QTableWidgetItem("strong");
    bluetoothTable->setItem(0, 1, device1Connection);
    auto device2Connection = new QTableWidgetItem("weak");
    bluetoothTable->setItem(1, 1, device2Connection);
    bluetoothLayout->addWidget(bluetoothTable);
    auto bluetoothExit = new QPushButton(bluetooth);
    connect(bluetoothExit, &QPushButton::clicked, bluetooth, &QWidget::hide);
    connect(bluetoothExit, &QPushButton::clicked, menu, &QWidget::show);
    bluetoothExit->setText("RETURN");
    bluetoothTable->resizeColumnsToContents();
    bluetoothTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    bluetoothTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    bluetoothTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    bluetoothLayout->addWidget(bluetoothExit);
    bluetooth->hide();
    middleLayout->addWidget(bluetooth);

    auto settings = new QLabel(middle);
    settings->setText("There should car settings here, ex. gearbox mode.\nI can't really implement any without simulating the entire car.");
    auto settingsExit = new QPushButton(settings);
    settingsExit->setText("RETURN");
    connect(settingsExit, &QPushButton::clicked, settings, &QWidget::hide);
    connect(settingsExit, &QPushButton::clicked, settingsExit, &QWidget::hide);
    connect(settingsExit, &QPushButton::clicked, menu, &QWidget::show);
    middleLayout->addWidget(settings);
    middleLayout->addWidget(settingsExit);
    settings->hide();
    settingsExit->hide();
    connect(settingsButton, &QPushButton::clicked, settingsExit, &QWidget::show);
    connect(settingsButton, &QPushButton::clicked, settings, &QWidget::show);

    auto airConditioning = new QWidget(middle);
    auto airConditioningLayout = new QVBoxLayout(airConditioning);
    airConditioning->setLayout(airConditioningLayout);
    auto heatSliderLabel = new QLabel(airConditioning);
    heatSliderLabel->setText("Temperature");
    airConditioningLayout->addWidget(heatSliderLabel);
    auto heatSlider = new QSlider(airConditioning);
    heatSlider->setTickInterval(1);
    heatSlider->setOrientation(Qt::Horizontal);
    heatSlider->setRange(15, 30);
    airConditioningLayout->addWidget(heatSlider);
    heatSliderLabel->setBuddy(heatSlider);
    auto levelSliderLabel = new QLabel(airConditioning);
    levelSliderLabel->setText("Level");
    airConditioningLayout->addWidget(levelSliderLabel);
    auto levelSlider = new QSlider(airConditioning);
    levelSlider->setTickInterval(1);
    levelSlider->setOrientation(Qt::Horizontal);
    levelSlider->setRange(0, 5);
    airConditioningLayout->addWidget(levelSlider);
    levelSliderLabel->setBuddy(levelSlider);
    auto airConditioningSwitch = new QPushButton(airConditioning);
    airConditioningSwitch->setText("SWITCH AC");
    connect(airConditioningSwitch, &QPushButton::clicked, conditioningIndicator, &Indicator::switchState);
    airConditioningLayout->addWidget(airConditioningSwitch);
    auto airConditioningExit = new QPushButton(airConditioning);
    airConditioningExit->setText("RETURN");
    connect(airConditioningExit, &QPushButton::clicked, airConditioning, &QWidget::hide);
    connect(airConditioningExit, &QPushButton::clicked, menu, &QWidget::show);
    airConditioningLayout->addWidget(airConditioningExit);
    middleLayout->addWidget(airConditioning);
    airConditioning->hide();
    connect(airConditioningButton, &QPushButton::clicked, airConditioning, &QWidget::show);

=======
    auto radioOn = new QPushButton(middle);
    middleLayout->addWidget(radioOn);
>>>>>>> 07d5cd0ae9622e969e3f723e3241efb88059f230
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
<<<<<<< HEAD
            turningLeft = !turningLeft;
=======
            turningLeft = true;
>>>>>>> 07d5cd0ae9622e969e3f723e3241efb88059f230
            emit(turnLeft());
            break;
        case Qt::Key_Right:
            if (turningLeft) {
                emit(turnLeft());
                turningLeft = false;
            }
<<<<<<< HEAD
            turningRight = !turningRight;
=======
            turningRight = true;
>>>>>>> 07d5cd0ae9622e969e3f723e3241efb88059f230
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
