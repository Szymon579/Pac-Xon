#include "ghost.h"

#include <QBrush>
#include <QPen>

Ghost::Ghost()
{
    ghost_texture = QPixmap(":/assets/ghost.png");
    QBrush ghost_brush(ghost_texture);

    this->setRect(60, 60, ghost_size, ghost_size);
    this->setBrush(ghost_brush);
    this->setPen(Qt::NoPen);
    this->setFlag(QGraphicsItem::ItemIsFocusable);

    direction = GhostDirection::rightDown;

}

void Ghost::moveGhost()
{
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
