#include "indicator.h"

Indicator::Indicator(QWidget *parent, const QString &onPath) : QWidget(parent) {
    on = false;
    setFixedSize(60, 60);
    onImg = new QPixmap(onPath);
}

void Indicator::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    if (on) {
        painter.drawPixmap(0,0, onImg->scaled(this->size(), Qt::KeepAspectRatio));
    }
}

void Indicator::switchState() {
    on = !on;
    update();
}
