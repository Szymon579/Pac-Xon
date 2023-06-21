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

    board->renderTileBoard();
    scene->addItem(player);

    makeGhosts(level);
    makeFruits(level);

    for(int i = 0; i < ghost_vec.size(); i++)
    {
        ghosts.push_back(ghost_vec[i]);

        scene->addItem(ghost_vec[i]);
        QObject::connect(ghost_vec[i], &Ghost::checkTile, board, &Board::handleGhost);
        QObject::connect(ghost_vec[i], &Ghost::gameOver, this, &GameBuilder::killedByGhostSlot);
        QObject::connect(board, &Board::borderHit, ghost_vec[i], &Ghost::changeDirection);
        QObject::connect(&master_timer, &QTimer::timeout, ghost_vec[i], &Ghost::moveGhost);
    }

    for(int i = 0; i < fruit_vec.size(); i++)
    {
        QObject::connect(fruit_vec[i], &Fruit::setPosOnBoard, board, &Board::handleFruit);
        QObject::connect(board, &Board::fruitEaten, fruit_vec[i], &Fruit::eaten);

        QObject::connect(fruit_vec[i], &Fruit::givePower, this, &GameBuilder::givePowerSlot);
        QObject::connect(fruit_vec[i], &Fruit::disablePower, this, &GameBuilder::disablePowerSlot);

        QObject::connect(fruit_vec[i], &Fruit::addToScene, this, &GameBuilder::addToSceneSlot);
        QObject::connect(fruit_vec[i], &Fruit::deleteFromScene, this, &GameBuilder::deleteFromSceneSlot);

    }

    QObject::connect(player, &Player::positionChanged, board, &Board::updateBoard);
    QObject::connect(&master_timer, &QTimer::timeout, player, &Player::movePlayer);
    QObject::connect(board, &Board::coloredArea, this, &GameBuilder::isGameWonSlot);

    QObject::connect(player, &Player::pause, this, &GameBuilder::pauseSlot);

    master_timer.start(10); //10

}

GameBuilder::~GameBuilder()
{
    ghost_vec.clear();
    fruit_vec.clear();

    delete scene;
    delete board;
    delete player;
}

void GameBuilder::killedByGhostSlot()
{
    lives--;
    emit livesSignal(lives);

    player->resetAfterKilled();
}

void GameBuilder::isGameWonSlot(double filled)
{
    emit areaSignal(filled);

//    if(filled > 80.0)
//    {
//        master_timer.stop();
//        qDebug() << "YOU WIN!";
//    }
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
        for(int i = 0; i < ghosts.size(); i++)
        {
            ghosts[i]->step = ghosts[i]->step / 2;
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
        for(int i = 0; i < ghosts.size(); i++)
        {
            ghosts[i]->step = ghosts[i]->step * 2;
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
        int rand_time   = 3 + (rand() % 13);
        int rand_power  = rand() % 3;

        Fruit *fruit = new Fruit(rand_y, rand_x, rand_time, (Fruit::Power)rand_power);
        fruit_vec.push_back(fruit);
    }
}



