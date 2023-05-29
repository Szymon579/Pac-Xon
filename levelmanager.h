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

    void createLevel();

signals:
    void livesSignal(int lives);
    void scoreSignal(double score);

public slots:
    void livesSlot(int lives);
    void scoreSlot(double score);

private:
    //int num_of_leves = 1;
    int level = 1;
    double score = 0;
    int lives = 0;

};

#endif // LEVELMANAGER_H
