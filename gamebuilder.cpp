#include "gamebuilder.h"
#include "player.h"
#include "board.h"
#include "ghost.h"

#include <QObject>
#include <QTimer>
#include <QDebug>

GameBuilder::GameBuilder(int level, int lives)
{
    this->level = level;
    this->lives = lives;

    ghost_vec.clear();
    fruit_vec.clear();
    makeGhosts(level);
    makeFruits(level);

    board->renderTileBoard();
    scene->addItem(player);

    for(int i = 0; i < ghost_vec.size(); i++)
    {
        scene->addItem(ghost_vec[i]);
        QObject::connect(ghost_vec[i], &Ghost::checkTile, board, &Board::handleGhostSlot);
        QObject::connect(ghost_vec[i], &Ghost::gameOver, this, &GameBuilder::playerKilledSlot);
        QObject::connect(board, &Board::borderHit, ghost_vec[i], &Ghost::changeDirection);
        QObject::connect(&master_timer, &QTimer::timeout, ghost_vec[i], &Ghost::moveGhost);
    }

    for(int i = 0; i < fruit_vec.size(); i++)
    {
        QObject::connect(fruit_vec[i], &Fruit::setPosOnBoard, board, &Board::handleFruitSlot);
        QObject::connect(board, &Board::fruitEaten, fruit_vec[i], &Fruit::eaten);

        QObject::connect(fruit_vec[i], &Fruit::givePower, this, &GameBuilder::givePowerSlot);
        QObject::connect(fruit_vec[i], &Fruit::disablePower, this, &GameBuilder::disablePowerSlot);

        QObject::connect(fruit_vec[i], &Fruit::addToScene, this, &GameBuilder::addToSceneSlot);
        QObject::connect(fruit_vec[i], &Fruit::deleteFromScene, this, &GameBuilder::deleteFromSceneSlot);
    }

    QObject::connect(player, &Player::positionChanged, board, &Board::updateBoardSlot);
    QObject::connect(&master_timer, &QTimer::timeout, player, &Player::movePlayer);
    QObject::connect(board, &Board::coloredArea, this, &GameBuilder::areaSlot);

    QObject::connect(board, &Board::drawingTraceSignal, player, &Player::drawingTraceSlot);
    QObject::connect(board, &Board::suicide, this, &GameBuilder::playerKilledSlot);

    QObject::connect(player, &Player::pause, this, &GameBuilder::pauseSlot);

    master_timer.start(10);

}

GameBuilder::~GameBuilder()
{
    delete scene;
    delete board;
    delete player;
}

void GameBuilder::playerKilledSlot()
{
    lives--;
    player->resetAfterKilled();
    emit livesSignal(lives);
}

void GameBuilder::areaSlot(double filled)
{
    emit areaSignal(filled);
}

void GameBuilder::pauseSlot()
{
    if(!pause)
    {
        master_timer.stop();
        pause = true;
    }
    else
    {
        master_timer.start();
        pause = false;
    }

    emit pauseSignal(pause);
}

void GameBuilder::addToSceneSlot()
{
    QGraphicsItem *item = dynamic_cast<QGraphicsItem*>(QObject::sender());
    scene->addItem(item);
    qDebug() << "added to scene";
}

void GameBuilder::deleteFromSceneSlot()
{
    QGraphicsItem *item = dynamic_cast<QGraphicsItem*>(QObject::sender());
    scene->removeItem(item);
    qDebug() << "deleted from scene";
}

void GameBuilder::givePowerSlot(Fruit::Power power, int effect_time)
{

    if(power == Fruit::Power::add_life)
    {
        lives++;
        emit livesSignal(lives);
    }

    if(power == Fruit::Power::fast_player)
    {
        player->step = player->step * 2;
    }

    if(power == Fruit::Power::slow_ghost)
    {
        for(int i = 0; i < ghost_vec.size(); i++)
        {
            ghost_vec[i]->step = 0;
        }
    }
}

void GameBuilder::disablePowerSlot(Fruit::Power power)
{
    if(power == Fruit::Power::fast_player)
    {
        player->step = player->step / 2;
    }

    if(power == Fruit::Power::slow_ghost)
    {
        for(int i = 0; i < ghost_vec.size(); i++)
        {
            ghost_vec[i]->step = 0.5;
        }
    }
}

void GameBuilder::makeGhosts(int quantity)
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

void GameBuilder::makeFruits(int quantity)
{
    for(int i = 0; i < quantity; i++)
    {
        int rand_y      = 2 + (rand() % 27);
        int rand_x      = 2 + (rand() % 42);
        int rand_time   = 3 + (rand() % 30);
        int rand_power  = rand() % 3;

        Fruit *fruit = new Fruit(rand_y, rand_x, rand_time, (Fruit::Power)rand_power);
        fruit_vec.push_back(fruit);
    }
}



