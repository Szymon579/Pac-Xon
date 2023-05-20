#include "logic.h"

#include "player.h"
#include "board.h"
#include "ghost.h"

#include <QObject>
#include <QTimer>
#include <QDebug>

Logic::Logic()
{
    qDebug() << "logic constructor";

    board->renderTileBoard();

    scene->addItem(player);
    player->setZValue(5);

    scene->addItem(ghost_1);
    scene->addItem(ghost_2);
    scene->addItem(ghost_3);
    //scene->addItem(ghost_4);

    scene->addItem(fruit);

    QObject::connect(player, &Player::positionChanged, board, &Board::updateBoard);

    QObject::connect(ghost_1, &Ghost::checkTile, board, &Board::checkBoard);
    QObject::connect(ghost_2, &Ghost::checkTile, board, &Board::checkBoard);
    QObject::connect(ghost_3, &Ghost::checkTile, board, &Board::checkBoard);
    //QObject::connect(ghost_4, &Ghost::checkTile, board, &Board::checkBoard);

    QObject::connect(board, &Board::borderHit, ghost_1, &Ghost::changeDirection);
    QObject::connect(board, &Board::borderHit, ghost_2, &Ghost::changeDirection);
    QObject::connect(board, &Board::borderHit, ghost_3, &Ghost::changeDirection);
    //QObject::connect(board, &Board::borderHit, ghost_4, &Ghost::changeDirection);


    QObject::connect(&player_timer, &QTimer::timeout, ghost_1, &Ghost::moveGhost);
    QObject::connect(&player_timer, &QTimer::timeout, ghost_2, &Ghost::moveGhost);
    QObject::connect(&player_timer, &QTimer::timeout, ghost_3, &Ghost::moveGhost);
    //QObject::connect(&player_timer, &QTimer::timeout, ghost_4, &Ghost::moveGhost);

    QObject::connect(&player_timer, &QTimer::timeout, player, &Player::movePlayer);
    player_timer.start(10);

    view->show();

}

void Logic::ghostPosToVec()
{
    ghosts_pos_vec.push_back(ghost_1->getGhostPos());
    ghosts_pos_vec.push_back(ghost_2->getGhostPos());
}
