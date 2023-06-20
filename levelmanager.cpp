#include "levelmanager.h"
#include "gamebuilder.h"

#include <QObject>
//#include <random>

LevelManager::LevelManager()
{

}

void LevelManager::createLevel(int level_num)
{
    scene = new QGraphicsScene(0, 0, 900, 600);

    makeGhosts(level_num);
    makeFruits(level_num);

    game = new GameBuilder(level_num, 3, ghost_vec, fruit_vec);

    QObject::connect(game, &GameBuilder::livesSignal, this, &LevelManager::livesSlot);
    QObject::connect(game, &GameBuilder::areaSignal, this, &LevelManager::areaSlot);
    QObject::connect(game, &GameBuilder::pauseSignal, this, &LevelManager::pauseSlot);

    this->scene = game->scene;

    ghost_vec.clear();
    fruit_vec.clear();

    emit livesSignal(3);
    emit areaSignal(0);
    emit levelSignal(level_num);
    emit pauseSignal(false);
}

void LevelManager::livesSlot(int lives)
{
    this->lives = lives;
    emit livesSignal(lives);
}

void LevelManager::areaSlot(double score)
{
    this->score = score;
    emit areaSignal(score);
}

void LevelManager::pauseSlot(bool pause)
{
    emit pauseSignal(pause);
}

void LevelManager::makeGhosts(int quantity)
{
    for(int i = 0; i < quantity; i++)
    {
        int rand_y      = 2 + (rand() % 27);
        int rand_x      = 2 + (rand() % 42);
        int rand_dir    = rand() % 4;

        Ghost *ghost = new Ghost(rand_y, rand_x, (Ghost::GhostDirection)rand_dir);
        ghost_vec.push_back(ghost);
    }
}

void LevelManager::makeFruits(int quantity)
{
    for(int i = 0; i < quantity; i++)
    {
        int rand_y      = 2 + (rand() % 27);
        int rand_x      = 2 + (rand() % 42);
        int rand_time   = 3 + (rand() % 13);
        int rand_power  = rand() % 3;

        Fruit *fruit = new Fruit(rand_y, rand_x, rand_time, (Fruit::Power)rand_power);
        fruit_vec.push_back(fruit);
    }
}
