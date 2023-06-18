#include "fruit.h"

#include <QBrush>
#include <QPen>
#include <QDebug>

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

    setOnBoard();

    timer.singleShot(sec_active * 1000, this, &Fruit::eraseFromBoard);
}

void Fruit::setOnBoard()
{
    active = true;
    emit setPosOnBoard(y_pos, x_pos, active);
}

void Fruit::eraseFromBoard()
{
    active = false;
    setPosOnBoard(y_pos, x_pos, active);

    emit deleteFromScene();
    qDebug() << "erased from Board";
}


