#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

#include "player.h"
#include "board.h"
#include "ghost.h"
#include "fruit.h"

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QDebug>


class GameBuilder : public QObject
{
    Q_OBJECT
public:
    GameBuilder(int level, int lives);

    ~GameBuilder();

    QGraphicsScene *scene = new QGraphicsScene(0, 0, 900, 600);

signals:
    void livesSignal(int lives);
    void areaSignal(double score);
    void pauseSignal(bool pause);

public slots:
    void killedByGhostSlot();
    void isGameWonSlot(double filled);
    void pauseSlot();

    void addToSceneSlot();
    void deleteFromSceneSlot();

    void givePowerSlot(Fruit::Power power, int effect_time);
    void disablePowerSlot(Fruit::Power power);

private:
    QTimer master_timer;
    QTimer power_timer;

    Board *board = new Board(scene);
    Player *player = new Player();

    std::vector<Ghost*> ghosts;

    int level = 0;
    double filled_area = 0;
    int lives = 0;
    bool game_over = false;

    bool pause = false;

    std::vector<Ghost*> ghost_vec;
    void makeGhosts(int quantity);

    std::vector<Fruit*> fruit_vec;
    void makeFruits(int quantity);

};

#endif // GAMEBUILDER_H
