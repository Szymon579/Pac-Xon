#include "gamebuilder.h"
#include "player.h"
#include "board.h"
#include "ghost.h"

#include <QObject>
#include <QTimer>
#include <QDebug>

GameBuilder::GameBuilder(int level, int lives, std::vector<Ghost*> ghost_vec)
{
    this->level = level;
    this->lives = lives;

    board->renderTileBoard();
    scene->addItem(player);

    for(int i = 0; i < ghost_vec.size(); i++)
    {
        scene->addItem(ghost_vec[i]);
        QObject::connect(ghost_vec[i], &Ghost::checkTile, board, &Board::handleGhost);
        QObject::connect(ghost_vec[i], &Ghost::gameOver, this, &GameBuilder::killedByGhost);
        QObject::connect(board, &Board::borderHit, ghost_vec[i], &Ghost::changeDirection);
        QObject::connect(&player_timer, &QTimer::timeout, ghost_vec[i], &Ghost::moveGhost);
    }

    fruit = new Fruit(13, 24);
    scene->addItem(fruit);
    QObject::connect(fruit, &Fruit::deleteFromScene, this, &GameBuilder::deleteFromScene);

    QObject::connect(player, &Player::positionChanged, board, &Board::updateBoard);
    QObject::connect(&player_timer, &QTimer::timeout, player, &Player::movePlayer);
    QObject::connect(board, &Board::coloredArea, this, &GameBuilder::isGameWon);

    QObject::connect(player, &Player::pause, this, &GameBuilder::pauseSlot);

    player_timer.start(10); //10

}

GameBuilder::~GameBuilder()
{
    delete scene;
    delete board;
    delete player;
}

void GameBuilder::killedByGhost()
{
    lives--;
    emit livesSignal(lives);

    player->setPos(0, 0);
    player->setMoveDirection(Player::MoveDirection::none);

    //player_timer.stop();
}

void GameBuilder::isGameWon(double filled)
{
    emit scoreSignal(filled);

    if(filled > 80.0)
    {
        player_timer.stop();
        qDebug() << "YOU WIN!";
    }
}

void GameBuilder::pauseSlot()
{
    if(!pause)
    {
        player_timer.stop();
        pause = true;
    }
    else
    {
        player_timer.start();
        pause = false;
    }

    emit pauseSignal(pause);
}

void GameBuilder::deleteFromScene()
{
    scene->removeItem(fruit);
    qDebug() << "deleted form Scene";
}

