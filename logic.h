#ifndef LOGIC_H
#define LOGIC_H

#include "player.h"
#include "board.h"
#include "ghost.h"
#include "fruit.h"

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QDebug>


//this class will be a level bulider taking number and pos of ghosts and fruits
class Logic : public QObject
{
    Q_OBJECT
public:
    Logic(int lives);

public slots:
    void stopTimer();
    void isGameWon(double filled);

private:
    QGraphicsScene *scene = new QGraphicsScene(0, 0, 900, 600);
    QGraphicsView *view = new QGraphicsView(scene);

    Board *board = new Board(scene);
    Player *player = new Player();

    //make this level dependent
    Ghost *ghost_1 = new Ghost(4, 4, Ghost::rightDown);
    Ghost *ghost_2 = new Ghost(15, 25, Ghost::rightUp);
    Ghost *ghost_3 = new Ghost(20, 8, Ghost::leftDown);
    Ghost *ghost_4 = new Ghost(6, 15, Ghost::leftUp);

    //Fruit *fruit = new Fruit(10, 20);

    QTimer player_timer;

    int score = 0;
    int lives = 0;
    bool game_over = false;

};

#endif // LOGIC_H
