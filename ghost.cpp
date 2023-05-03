#include "ghost.h"

#include <QBrush>
#include <QPen>

Ghost::Ghost(int y, int x, GhostDirection init_direction)
{
    ghost_texture = QPixmap(":/assets/ghost_white.png");
    QBrush ghost_brush(ghost_texture);

    y_pos = y;
    x_pos = x;

    this->setRect(0, 0, ghost_size, ghost_size);
    this->setBrush(ghost_brush);
    this->setPen(Qt::NoPen);
    this->setFlag(QGraphicsItem::ItemIsFocusable);

    this->setPos(x_pos * 20, y_pos * 20);

    direction = init_direction;

}

void Ghost::changeDirection(int y, int x, bool flag_left, bool flag_right, bool flag_up, bool flag_down)
{
    //qDebug() << "changeDirection()";
    if(y != y_pos || x != x_pos)
        return;

    //handle rightDown
    if(direction == GhostDirection::rightDown && flag_down)
    {
        direction = GhostDirection::rightUp;
        return;
    }
    if(direction == GhostDirection::rightDown && flag_right)
    {
        direction = GhostDirection::leftDown;
        return;
    }

    //handle rightUp
    if(direction == GhostDirection::rightUp && flag_up)
    {
        direction = GhostDirection::rightDown;
        return;
    }
    if(direction == GhostDirection::rightUp && flag_right)
    {
        direction = GhostDirection::leftUp;
        return;
    }

    //handle leftDown
    if(direction == GhostDirection::leftDown && flag_down)
    {
        direction = GhostDirection::leftUp;
        return;
    }
    if(direction == GhostDirection::leftDown && flag_left)
    {
        direction = GhostDirection::rightDown;
        return;
    }

    //handle leftUp
    if(direction == GhostDirection::leftUp && flag_up)
    {
        direction = GhostDirection::leftDown;
        return;
    }
    if(direction == GhostDirection::leftUp && flag_left)
    {
        direction = GhostDirection::rightUp;
        return;
    }

}

void Ghost::moveGhost()
{
    positionOnBoard();

    emit checkTile(y_pos, x_pos);

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

    if(fmod(this->x(), ghost_size) == 0) {
        x_pos = this->x() / ghost_size;
    }
    if(fmod(this->y(), ghost_size) == 0) {
        y_pos = this->y() / ghost_size;
    }

    if(prev_x != x_pos || prev_y != y_pos)
        qDebug() << "ghost y: " << y_pos << ", x: " << x_pos;

}
