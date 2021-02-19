#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QQuickWidget>
#include <QPushButton>

class Map : public QWidget
{
    Q_OBJECT
public:
    explicit Map(QWidget *parent = nullptr);
    QPushButton *returnButton;

private:
    QQuickWidget *mapWidget;

signals:
    void goBack();
};

#endif // MAP_H
