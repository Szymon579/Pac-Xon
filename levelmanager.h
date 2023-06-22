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
    ~LevelManager();

    QGraphicsScene *scene;
    GameBuilder *game;

    void createLevel(int level_num);
    void setLives(int lives);

signals:
    void livesSignal(int lives);
    void areaSignal(double score);
    void levelSignal(int level);
    void pauseSignal(bool paused);

    void gameOverSignal();

public slots:
    void livesSlot(int lives);
    void areaSlot(double score);
    void pauseSlot(bool pause);

private:
    int level = 1;
    int lives = 3;
    int req_area = 20;
    double filled_area = 0;

};

#endif // LEVELMANAGER_H
