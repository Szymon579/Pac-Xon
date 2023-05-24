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

void Ghost::changeDirection(int y, int x, bool left, bool right, bool up, bool down, bool left_up, bool left_down, bool right_up, bool right_down, bool game_over)
{
    //qDebug() << "changeDirection()";
    if(y != y_pos || x != x_pos)
        return;

    if(game_over)
    {
        qDebug() << "gameOver() emited";
        emit gameOver();
        return;
    }

    //handle rightDown
    if(direction == GhostDirection::rightDown && !left && !right && !up && down)
    {
        direction = GhostDirection::rightUp;
        return;
    }
    if(direction == GhostDirection::rightDown && !left && right && !up && !down)
    {
        direction = GhostDirection::leftDown;
        return;
    }
    if(direction == GhostDirection::rightDown && right_down)
    {
        direction = GhostDirection::leftUp;
        return;
    }


    //handle rightUp
    if(direction == GhostDirection::rightUp && !left && !right && up && !down)
    {
        direction = GhostDirection::rightDown;
        return;
    }
    if(direction == GhostDirection::rightUp && !left && right && !up && !down)
    {
        direction = GhostDirection::leftUp;
        return;
    }
    if(direction == GhostDirection::rightUp && right_up)
    {
        direction = GhostDirection::leftDown;
        return;
    }


    //handle leftDown
    if(direction == GhostDirection::leftDown && !left && !right && !up && down)
    {
        direction = GhostDirection::leftUp;
        return;
    }
    if(direction == GhostDirection::leftDown && left && !right && !up && !down)
    {
        direction = GhostDirection::rightDown;
        return;
    }
    if(direction == GhostDirection::leftDown && left_down)
    {
        direction = GhostDirection::rightUp;
        return;
    }


    //handle leftUp
    if(direction == GhostDirection::leftUp && !left && !right && up && !down)
    {
        direction = GhostDirection::leftDown;
        return;
    }
    if(direction == GhostDirection::leftUp && left && !right && !up && !down)
    {
        direction = GhostDirection::rightUp;
        return;
    }
    if(direction == GhostDirection::leftUp && left_up)
    {
        direction = GhostDirection::rightDown;
        return;
    }


}

std::pair<int, int> Ghost::getGhostPos()
{
    std::pair<int, int> cords;
    cords.first = y_pos;
    cords.second = x_pos;

    return cords;
}

void Ghost::moveGhost()
{
    if(positionOnBoard())
        emit checkTile(y_pos, x_pos, y_prev_pos, x_prev_pos);

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

bool Ghost::positionOnBoard()
{
    x_prev_pos = x_pos;
    y_prev_pos = y_pos;

    if(fmod(this->x(), ghost_size) == 0) {
        x_pos = this->x() / ghost_size;
    }
    if(fmod(this->y(), ghost_size) == 0) {
        y_pos = this->y() / ghost_size;
    }

    if(y_prev_pos != y_pos || x_prev_pos != x_pos)
    {
        //qDebug() << "ghost y: " << y_pos << ", x: " << x_pos;
        return true;
    }
    //pos didnt change
    return false;
}
