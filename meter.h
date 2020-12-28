#ifndef CAR_METER_H
#define CAR_METER_H

#include <QWidget>

//use qwt
class Meter : public QWidget {
    Q_OBJECT
public:
    explicit Meter(QWidget *parent = nullptr, unsigned int minValue = 0, unsigned int maxValue = 1000,
                   unsigned int step = 1, unsigned int maxLevel = 1, const QString &bgImgPath = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    unsigned int value;
    const unsigned int max;
    const unsigned int min;
    const unsigned int increase;
    unsigned int level;
    const unsigned int levelLimit;
    const QPixmap *background = nullptr;

public slots:
    void increaseValue();
    void decreaseValue();

signals:
    void impossibleAcceleration();
    void impossibleDeceleration();
};

#endif //CAR_METER_H
