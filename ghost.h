#ifndef GHOST_H
#define GHOST_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QPixmap>

class Ghost : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    enum GhostDirection
    {
        leftUp,
        leftDown,
        rightUp,
        rightDown,
        none
    };

    Ghost(int y, int x, GhostDirection init_direction); //explicit



    void changeDirection(int y, int x, bool left, bool right, bool up, bool down);

signals:
    void checkTile(int y_pos, int x_pos);

public slots:
    void moveGhost();

private:
    QPixmap ghost_texture;
    qreal ghost_size = 20;

    qreal step = 0.5;
    GhostDirection direction;

    bool at_border;
    void positionOnBoard();
    int x_pos;
    int y_pos;

};

#endif // GHOST_H
