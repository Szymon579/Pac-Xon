#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "gamebuilder.h"
#include "ghost.h"

#include <QObject>
#include <QGraphicsScene>

class LevelManager : public QObject
{
    Q_OBJECT
public:
    LevelManager();

    QGraphicsScene *scene = new QGraphicsScene(0, 0, 900, 600);
    GameBuilder *game;

    void createLevel(int level_num);

signals:
    void livesSignal(int lives);
    void scoreSignal(double score);
    void levelSignal(int level);

public slots:
    void livesSlot(int lives);
    void scoreSlot(double score);

private:
    int level = 1;
    double score = 0;
    int lives = 0;

    std::vector<Ghost*> ghost_vec;
    void makeGhosts(int quantity);
};

#endif // LEVELMANAGER_H
