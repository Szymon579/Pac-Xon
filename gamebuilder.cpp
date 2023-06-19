#include "gamebuilder.h"
#include "player.h"
#include "board.h"
#include "ghost.h"

#include <QObject>
#include <QTimer>
#include <QDebug>

GameBuilder::GameBuilder(int level, int lives,
                         std::vector<Ghost*> ghost_vec,
                         std::vector<Fruit *> fruit_vec)
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
        QObject::connect(&master_timer, &QTimer::timeout, ghost_vec[i], &Ghost::moveGhost);
    }

    for(int i = 0; i < fruit_vec.size(); i++)
    {
        QObject::connect(fruit_vec[i], &Fruit::setPosOnBoard, board, &Board::handleFruit);
        QObject::connect(board, &Board::fruitEaten, fruit_vec[i], &Fruit::eaten);
        QObject::connect(fruit_vec[i], &Fruit::addToScene, this, &GameBuilder::addToScene);
        QObject::connect(fruit_vec[i], &Fruit::deleteFromScene, this, &GameBuilder::deleteFromScene);

    }

    QObject::connect(player, &Player::positionChanged, board, &Board::updateBoard);
    QObject::connect(&master_timer, &QTimer::timeout, player, &Player::movePlayer);
    QObject::connect(board, &Board::coloredArea, this, &GameBuilder::isGameWon);

    QObject::connect(player, &Player::pause, this, &GameBuilder::pauseSlot);

    master_timer.start(10); //10

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
}

void GameBuilder::isGameWon(double filled)
{
    emit scoreSignal(filled);

    if(filled > 80.0)
    {
        master_timer.stop();
        qDebug() << "YOU WIN!";
    }
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

void GameBuilder::addToScene()
{
    QGraphicsItem *item = dynamic_cast<QGraphicsItem*>(QObject::sender());
    scene->addItem(item);
    qDebug() << "added to scene";
}

void GameBuilder::deleteFromScene()
{
    QGraphicsItem *item = dynamic_cast<QGraphicsItem*>(QObject::sender());
    scene->removeItem(item);
    qDebug() << "deleted from scene";
}

