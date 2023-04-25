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
    void checkMove(int y_pos, int x_pos);

public slots:
    void moveGhost();

private:
    QPixmap ghost_texture;
    qreal ghost_size = 20;

    qreal step = 0.5;
    GhostDirection direction;

    void positionOnBoard();
    int x_pos;
    int y_pos;

};

#endif // GHOST_H
