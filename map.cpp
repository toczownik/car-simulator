#include "map.h"

#include <QVBoxLayout>

Map::Map(QWidget *parent) : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);
    setLayout(layout);
    mapWidget = new QQuickWidget(QUrl::fromLocalFile(":/map.qml"), this);
    layout->addWidget(mapWidget);
    mapWidget->show();
    returnButton = new QPushButton(this);
    returnButton->setText("RETURN");
    layout->addWidget(returnButton);
    hide();
    connect(returnButton, &QPushButton::clicked, this, &QWidget::hide);
}
