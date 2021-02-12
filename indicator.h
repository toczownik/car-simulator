<<<<<<< HEAD
#ifndef INDICATOR_H
#define INDICATOR_H
=======
#ifndef CAR_INDICATOR_H
#define CAR_INDICATOR_H
>>>>>>> 07d5cd0ae9622e969e3f723e3241efb88059f230

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

class Indicator : public QWidget {
    Q_OBJECT
public:
    Indicator(QWidget *parent, const QString &onPath);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    bool on;
    const QPixmap *onImg;

public slots:
    void switchState();
};

<<<<<<< HEAD
#endif // INDICATOR_H
=======

#endif //CAR_INDICATOR_H
>>>>>>> 07d5cd0ae9622e969e3f723e3241efb88059f230
