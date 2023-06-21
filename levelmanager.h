#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "gamebuilder.h"

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
    void areaSignal(double score);
    void levelSignal(int level);
    void pauseSignal(bool paused);

public slots:
    void livesSlot(int lives);
    void areaSlot(double score);
    void pauseSlot(bool pause);

private:
    int level = 1;
    int lives = 3;
    double filled_area = 0;

//    std::vector<Ghost*> ghost_vec;
//    void makeGhosts(int quantity);

//    std::vector<Fruit*> fruit_vec;
//    void makeFruits(int quantity);
};

#endif // LEVELMANAGER_H
