#include "logic.h"

#include "player.h"
#include "board.h"
#include "ghost.h"

#include <QObject>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QDebug>
#include <QPixmap>

Logic::Logic()
{
    qDebug() << "logic constructor";

    board->drawTileBoard();
    scene->addItem(ghost_1);
    scene->addItem(ghost_2);
    scene->addItem(player);
    player->setZValue(5);

    QObject::connect(player, &Player::positionChanged, board, &Board::updateBoard);

    QObject::connect(ghost_1, &Ghost::checkTile, board, &Board::checkBoard);
    QObject::connect(ghost_2, &Ghost::checkTile, board, &Board::checkBoard);

    QObject::connect(board, &Board::borderHit, ghost_1, &Ghost::changeDirection);
    QObject::connect(board, &Board::borderHit, ghost_2, &Ghost::changeDirection);

    QObject::connect(&player_timer, &QTimer::timeout, ghost_1, &Ghost::moveGhost);
    QObject::connect(&player_timer, &QTimer::timeout, ghost_2, &Ghost::moveGhost);

    QObject::connect(&player_timer, &QTimer::timeout, player, &Player::movePlayer);
    player_timer.start(10);

    view->show();

}

void Logic::makeGame(QGraphicsScene *scene)
{

}

void Logic::ghostPosToVec()
{
    ghosts_pos_vec.push_back(ghost_1->getGhostPos());
    ghosts_pos_vec.push_back(ghost_2->getGhostPos());
}
