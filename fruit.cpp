#include "fruit.h"

#include <QBrush>
#include <QPen>
#include <QDebug>

Fruit::Fruit(int y, int x, int time, Fruit::Power power)
{
    y_pos = y;
    x_pos = x;
    sec_active = time;
    this->power = power;

    if(power == add_life)
        fruit_texture = QPixmap(":/assets/cherry.png");
    if(power == fast_player)
        fruit_texture = QPixmap(":/assets/pear.png");
    if(power == slow_ghost)
        fruit_texture = QPixmap(":/assets/melon.png");

    QBrush fruit_brush(fruit_texture);


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
    is_active = true;
    emit setPosOnBoard(y_pos, x_pos, is_active);
}

void Fruit::eraseFromBoard()
{
    is_active = false;
    emit setPosOnBoard(y_pos, x_pos, is_active);

    emit deleteFromScene();
    qDebug() << "erased from Board";
}


