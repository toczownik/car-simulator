#ifndef CAR_INDICATOR_H
#define CAR_INDICATOR_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

class Indicator : public QWidget {
    Q_OBJECT
public:
    Indicator(QWidget *parent, const QString &onPath, const QString &offPath);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    bool on;
    const QPixmap *onImg;
    const QPixmap *offImg;

public slots:
    void switchState();
};


#endif //CAR_INDICATOR_H
