#include "ghost.h"

#include <QBrush>
#include <QPen>

Ghost::Ghost()
{
    ghost_texture = QPixmap(":/assets/ghost.png");
    QBrush ghost_brush(ghost_texture);

    y_pos = 4;
    x_pos = 4;

                // y_pos * 20
    this->setRect(0, 0, ghost_size, ghost_size);
    this->setBrush(ghost_brush);
    this->setPen(Qt::NoPen);
    this->setFlag(QGraphicsItem::ItemIsFocusable);

    this->setPos(x_pos * 20, y_pos * 20);

    direction = GhostDirection::rightDown;

}

void Ghost::changeDirection()
{
    qDebug() << "changeDirection()";
    if(direction == GhostDirection::rightDown)
    {
        qDebug() << "dir changed";
        direction = GhostDirection::leftUp;
    }
    //if(direction == GhostDirection::leftUp)
    //{
    //    qDebug() << "dir changed";
    //    direction = GhostDirection::rightDown;
    //}
}

void Ghost::moveGhost()
{
    positionOnBoard();

    qDebug() << "before checkMove emit in moveGhost";
    emit checkMove(y_pos, x_pos);
    qDebug() << "after checkMove emit in moveGhost";
    //board.cpp check whats under [x][y]



    if(direction == GhostDirection::leftUp) {
        setPos(x() - step, y() - step);
    }
    if(direction == GhostDirection::leftDown) {
        setPos(x() - step, y() + step);
    }
    if(direction == GhostDirection::rightUp) {
        setPos(x() + step, y() - step);
    }
    if(direction == GhostDirection::rightDown) {
        setPos(x() + step, y() + step);
    }
    if(direction == GhostDirection::none) {
        //do not move;
    }
}

void Ghost::positionOnBoard()
{
    int prev_x = x_pos;
    int prev_y = y_pos;

    if(fmod(this->x(), ghost_size) == 0)
        x_pos = this->x() / ghost_size;

    if(fmod(this->y(), ghost_size) == 0)
        y_pos = this->y() / ghost_size;


    if(prev_x != x_pos || prev_y != y_pos)
        qDebug() << "ghost y: " << y_pos << ", x: " << x_pos;

}
