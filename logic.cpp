#include "logic.h"
#include "player.h"
#include "board.h"
#include "ghost.h"

#include <QObject>
#include <QTimer>
#include <QDebug>

Logic::Logic(int lives)
{
    qDebug() << "logic constructor";

    this->lives = lives;

    board->renderTileBoard();

    scene->addItem(player);
    player->setZValue(5);

    scene->addItem(ghost_1);
    scene->addItem(ghost_2);
    scene->addItem(ghost_3);

    QObject::connect(player, &Player::positionChanged, board, &Board::updateBoard);

    QObject::connect(ghost_1, &Ghost::checkTile, board, &Board::handleGhost);
    QObject::connect(ghost_2, &Ghost::checkTile, board, &Board::handleGhost);
    QObject::connect(ghost_3, &Ghost::checkTile, board, &Board::handleGhost);

    QObject::connect(ghost_1, &Ghost::gameOver, this, &Logic::stopTimer);
    QObject::connect(ghost_2, &Ghost::gameOver, this, &Logic::stopTimer);
    QObject::connect(ghost_3, &Ghost::gameOver, this, &Logic::stopTimer);

    QObject::connect(board, &Board::borderHit, ghost_1, &Ghost::changeDirection);
    QObject::connect(board, &Board::borderHit, ghost_2, &Ghost::changeDirection);
    QObject::connect(board, &Board::borderHit, ghost_3, &Ghost::changeDirection);  

    QObject::connect(&player_timer, &QTimer::timeout, ghost_1, &Ghost::moveGhost);
    QObject::connect(&player_timer, &QTimer::timeout, ghost_2, &Ghost::moveGhost);
    QObject::connect(&player_timer, &QTimer::timeout, ghost_3, &Ghost::moveGhost);  

    QObject::connect(&player_timer, &QTimer::timeout, player, &Player::movePlayer);

    QObject::connect(board, &Board::coloredArea, this, &Logic::isGameWon);

    player_timer.start(10);

    //view->show();

}

void Logic::stopTimer()
{
    //player->setPos(0, 0);
    //player_timer.stop();
}

void Logic::isGameWon(double filled)
{
    if(filled > 80.0)
    {
        player_timer.stop();
        qDebug() << "YOU WIN!";
    }
}

