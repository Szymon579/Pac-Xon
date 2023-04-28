//#include "logic.h"
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


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene *scene = new QGraphicsScene(0, 0, 900, 600);

    Board *board = new Board(scene);
    board->drawTileBoard();

    Ghost *ghost = new Ghost();
    scene->addItem(ghost);

    //adding player
    Player *player = new Player();
    scene->addItem(player);
    player->setZValue(5);

    QObject::connect(player, &Player::positionChanged, board, &Board::updateBoard);

    //caousing some problems
    QObject::connect(ghost, &Ghost::checkTile, board, &Board::checkBoard);
    QObject::connect(board, &Board::borderHit, ghost, &Ghost::changeDirection);

    QTimer player_timer;
    QObject::connect(&player_timer, &QTimer::timeout, ghost, &Ghost::moveGhost);
    QObject::connect(&player_timer, &QTimer::timeout, player, &Player::movePlayer);
    player_timer.start(10);

    QGraphicsView *view = new QGraphicsView(scene);
    view->show();

    qDebug() << "before exec";
    return a.exec();
}

