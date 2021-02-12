#include "meter.h"
#include <QPainter>

#define ONE_UNIT_ROTATION (180.0 / max)

Meter::Meter(QWidget *parent, const unsigned int minValue, const unsigned int maxValue,
             const unsigned int step, const unsigned int maxLevel, const QString &bgImgPath) :
             QWidget(parent), min(minValue), value(minValue), max(maxValue), increase(step), level(1), levelLimit(maxLevel) {
    if (bgImgPath != nullptr) {
        background = new QPixmap(bgImgPath);
        this->setFixedSize(background->size());
    }
};

void Meter::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    if (background) {
        painter.drawPixmap(0, 0, *background);
    }

    static const QPoint hand[3] = {
            QPoint(7, 8),
            QPoint(-7, 8),
            QPoint(0, -40)
    };



    QColor color(Qt::red);
    int side = qMin(width(), height());
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width()/2, height()/2);
    painter.scale(side/200.0, side/200.0);
    painter.setPen(Qt::NoPen);
    painter.setBrush(color);
    painter.save();
    painter.rotate(-135 + ONE_UNIT_ROTATION * value);
    painter.drawConvexPolygon(hand, 3);
    painter.restore();
}

void Meter::increaseValue() {
    if (value >= max && level < levelLimit - 1) {
        value = min;
        level++;
    } else if ((level == levelLimit - 1 && value >= max) || level >= levelLimit) emit(impossibleAcceleration());
    value += increase;
    update();
}

void Meter::decreaseValue() {
    if (value <= min && level > 1) {
        value = max;
        level--;
    } else if (level <= 1 && (value - increase <= min)) emit(impossibleDeceleration());
    value -= increase;
    update();
<<<<<<< HEAD
}
=======
}
>>>>>>> 07d5cd0ae9622e969e3f723e3241efb88059f230
