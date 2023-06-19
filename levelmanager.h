#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "gamebuilder.h"
#include "ghost.h"
#include "fruit.h"

#include <QObject>
#include <QGraphicsScene>

class LevelManager : public QObject
{
    Q_OBJECT
public:
    LevelManager();

    QGraphicsScene *scene;
    GameBuilder *game;

    void createLevel(int level_num);

signals:
    void livesSignal(int lives);
    void scoreSignal(double score);
    void levelSignal(int level);
    void pauseSignal(bool paused);

public slots:
    void livesSlot(int lives);
    void scoreSlot(double score);
    void pauseSlot(bool pause);

private:
    int level = 1;
    double score = 0;
    int lives = 0;

    std::vector<Ghost*> ghost_vec;
    void makeGhosts(int quantity);

    std::vector<Fruit*> fruit_vec;
    void makeFruits(int quantity);
};

#endif // LEVELMANAGER_H
