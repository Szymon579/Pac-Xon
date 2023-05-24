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

    void changeDirection(int y, int x, bool left, bool right, bool up, bool down,
               bool left_up, bool left_down, bool right_up, bool right_down, bool game_over);

    std::pair<int, int> getGhostPos();

signals:
    void checkTile(int y_pos, int x_pos, int y_prev_pos, int x_prev_pos);
    void gameOver();
public slots:
    void moveGhost();

private:
    QPixmap ghost_texture;
    qreal ghost_size = 20;

    qreal step = 0.5; /// 1
    GhostDirection direction;

    bool at_border;
    bool positionOnBoard();

    int x_pos = 0;
    int y_pos = 0;
    int x_prev_pos = 0;
    int y_prev_pos = 0;

};

#endif // GHOST_H
