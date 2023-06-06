#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

#include "player.h"
#include "board.h"
#include "ghost.h"
//#include "fruit.h"

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QDebug>


class GameBuilder : public QObject
{
    Q_OBJECT
public:
    GameBuilder(int level, int lives, std::vector<Ghost*> ghost_vec);
    ~GameBuilder();

    QGraphicsScene *scene = new QGraphicsScene(0, 0, 900, 600);

signals:
    void livesSignal(int lives);
    void scoreSignal(double score);
    void pauseSignal(bool pause);

public slots:
    void killedByGhost();
    void isGameWon(double filled);
    void pauseSlot();

private:
    QTimer player_timer;

    //QGraphicsView *view = new QGraphicsView(scene);

    Board *board = new Board(scene);
    Player *player = new Player();

    int level = 0;
    double score = 0;
    int lives = 0;
    bool game_over = false;

    bool pause = false;

};

#endif // GAMEBUILDER_H
