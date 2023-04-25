#ifndef GHOST_H
#define GHOST_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QPixmap>

class Ghost : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Ghost(); //explicit

    enum GhostDirection
    {
        leftUp,
        leftDown,
        rightUp,
        rightDown,
        none
    };


    void changeDirection();

signals:
    void checkBoardState();

public slots:
    void moveGhost();

private:
    QPixmap ghost_texture;
    qreal ghost_size = 20;

    qreal step = 0.5;
    GhostDirection direction;

};

#endif // GHOST_H
