#ifndef LOGIC_H
#define LOGIC_H

#include "player.h"
#include "board.h"
#include "ghost.h"

#include <QObject>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QDebug>
#include <QPixmap>

class Logic : public QObject
{
    Q_OBJECT
public:
    Logic();

    static void makeGame(QGraphicsScene *scene);

private:
    QGraphicsScene *scene = new QGraphicsScene(0, 0, 900, 600);

    Board *board = new Board(scene);


    Ghost *ghost_1 = new Ghost(4, 4, Ghost::rightDown);

    Ghost *ghost_2 = new Ghost(15, 25, Ghost::rightUp);

    //adding player
    Player *player = new Player();

    QGraphicsView *view = new QGraphicsView(scene);

    QTimer player_timer;

    std::vector<std::pair<int, int>> ghosts_pos_vec;
    void ghostPosToVec();
};

#endif // LOGIC_H
