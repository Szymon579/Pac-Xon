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

}
