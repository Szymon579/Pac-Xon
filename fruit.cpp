#include "fruit.h"

#include <QBrush>
#include <QPen>
#include <QDebug>

Fruit::Fruit(int y, int x, int time, Fruit::Power power)
{
    y_pos = y;
    x_pos = x;
    time_to_spawn = time;
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

    is_active = false;
    spawn_timer.singleShot(time_to_spawn * 1000, this, &Fruit::setOnBoard);
}

void Fruit::setOnBoard()
{
    is_active = true;
    emit setPosOnBoard(y_pos, x_pos, is_active);
    emit addToScene();
    qDebug() << "added to Board";
}

void Fruit::eraseFromBoard()
{
    is_active = false;
    emit setPosOnBoard(y_pos, x_pos, is_active);
    emit deleteFromScene();
    qDebug() << "erased from Board";
}

void Fruit::eaten(int y_pos, int x_pos)
{
    if(this->y_pos == y_pos && this->x_pos == x_pos)
    {
        eraseFromBoard();
        emit givePower(power);
    }

}


