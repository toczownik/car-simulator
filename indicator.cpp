#include "indicator.h"

Indicator::Indicator(const QString &onPath, const QString &offPath) {
    on = false;
    onImg = new QPixmap(onPath);
    offImg = new QPixmap(offPath);
}

void Indicator::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    setPalette(QPalette(Qt::black));
    setAutoFillBackground(true);

    if (on) {
        painter.drawPixmap(0,0, *onImg);
    } else {
        painter.drawPixmap(0, 0, *offImg);
    }
}

void Indicator::switchState() {
    on = !on;
}