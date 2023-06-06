#include "levelmanager.h"
#include "gamebuilder.h"

#include <QObject>
//#include <random>

LevelManager::LevelManager()
{


}

void LevelManager::createLevel(int level_num)
{
    //std::vector<Ghost*> ghost_vec;
    makeGhosts(level_num);

    game = new GameBuilder(level_num, 3, ghost_vec);

    QObject::connect(game, &GameBuilder::livesSignal, this, &LevelManager::livesSlot);
    QObject::connect(game, &GameBuilder::scoreSignal, this, &LevelManager::scoreSlot);
    QObject::connect(game, &GameBuilder::pauseSignal, this, &LevelManager::pauseSlot);

    this->scene = game->scene;

    ghost_vec.clear();

    emit livesSignal(3);
    emit scoreSignal(0);
    emit levelSignal(level_num);
}

void LevelManager::livesSlot(int lives)
{
    this->lives = lives;
    emit livesSignal(lives);
}

void LevelManager::scoreSlot(double score)
{
    this->score = score;
    emit scoreSignal(score);
}

void LevelManager::pauseSlot(bool pause)
{
    emit pauseSignal(pause);
}

void LevelManager::makeGhosts(int quantity)
{
    for(int i = 0; i < quantity; i++)
    {
        int rand_y = 2 + (rand() % 28);
        int rand_x = 2 + (rand() % 43);
        int rand_dir = rand() % 4;

        Ghost *ghost = new Ghost(rand_y, rand_x, (Ghost::GhostDirection)rand_dir);
        ghost_vec.push_back(ghost);
    }
}
