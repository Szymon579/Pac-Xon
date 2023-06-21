#include "levelmanager.h"
#include "gamebuilder.h"

#include <QObject>

LevelManager::LevelManager()
{

}

void LevelManager::createLevel(int level_num)
{
    qDebug() << "createLevel called";

    scene = new QGraphicsScene(0, 0, 900, 600);

    game = new GameBuilder(level_num, lives);

    QObject::connect(game, &GameBuilder::livesSignal, this, &LevelManager::livesSlot);
    QObject::connect(game, &GameBuilder::areaSignal,  this, &LevelManager::areaSlot);
    QObject::connect(game, &GameBuilder::pauseSignal, this, &LevelManager::pauseSlot);

    this->scene = game->scene;

    emit livesSignal(lives);
    emit areaSignal(0);
    emit pauseSignal(false);
    emit levelSignal(level_num);
}

void LevelManager::livesSlot(int lives)
{
    this->lives = lives;
    emit livesSignal(lives);
}

void LevelManager::areaSlot(double score)
{
    this->filled_area = score;
    emit areaSignal(score);
}

void LevelManager::pauseSlot(bool pause)
{
    emit pauseSignal(pause);
}
