#include "levelmanager.h"
#include "gamebuilder.h"

#include <QObject>

LevelManager::LevelManager()
{
    Ghost *ghost_1 = new Ghost(4, 4, Ghost::rightDown);
    Ghost *ghost_2 = new Ghost(15, 25, Ghost::rightUp);
    Ghost *ghost_3 = new Ghost(20, 8, Ghost::leftDown);

    std::vector<Ghost*> ghost_vec;
    ghost_vec.push_back(ghost_1);
    ghost_vec.push_back(ghost_2);
    ghost_vec.push_back(ghost_3);

    game = new GameBuilder(1, 3, ghost_vec);

    QObject::connect(game, &GameBuilder::livesSignal, this, &LevelManager::livesSlot);
    QObject::connect(game, &GameBuilder::scoreSignal, this, &LevelManager::scoreSlot);

    this->scene = game->scene;
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
