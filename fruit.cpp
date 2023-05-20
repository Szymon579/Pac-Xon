#include "fruit.h"

#include <QBrush>
#include <QPen>

Fruit::Fruit(int y, int x)
{
    fruit_texture = QPixmap(":/assets/cherry.png");
    QBrush fruit_brush(fruit_texture);

    y_pos = y;
    x_pos = x;

    this->setRect(0, 0, fruit_size, fruit_size);
    this->setBrush(fruit_brush);
    this->setPen(Qt::NoPen);
    this->setFlag(QGraphicsItem::ItemIsFocusable);

    this->setPos(x_pos * 20, y_pos * 20);
}
