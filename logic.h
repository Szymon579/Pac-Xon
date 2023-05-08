#ifndef LOGIC_H
#define LOGIC_H

#include "player.h"
#include "board.h"
#include "ghost.h"

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QDebug>

class Logic : public QObject
{
    Q_OBJECT
public:
    Logic();

private:
    QGraphicsScene *scene = new QGraphicsScene(0, 0, 900, 600);
    QGraphicsView *view = new QGraphicsView(scene);

    Board *board = new Board(scene);
    Player *player = new Player();
    Ghost *ghost_1 = new Ghost(4, 4, Ghost::rightDown);
    Ghost *ghost_2 = new Ghost(15, 25, Ghost::rightUp);
    Ghost *ghost_3 = new Ghost(20, 8, Ghost::leftDown);
    Ghost *ghost_4 = new Ghost(6, 15, Ghost::leftUp);

    QTimer player_timer;

    std::vector<std::pair<int, int>> ghosts_pos_vec;
    void ghostPosToVec();
};

#endif // LOGIC_H
