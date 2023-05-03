#include "logic.h"

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

    Logic logic;

//    QGraphicsScene *scene = new QGraphicsScene(0, 0, 900, 600);

//    Board *board = new Board(scene);
//    board->drawTileBoard();

//    Ghost *ghost_1 = new Ghost(4, 4, Ghost::rightDown);
//    scene->addItem(ghost_1);
//    Ghost *ghost_2 = new Ghost(15, 25, Ghost::rightUp);
//    scene->addItem(ghost_2);

//    //adding player
//    Player *player = new Player();
//    scene->addItem(player);
//    player->setZValue(5);

//    QObject::connect(player, &Player::positionChanged, board, &Board::updateBoard);

//    QObject::connect(ghost_1, &Ghost::checkTile, board, &Board::checkBoard);
//    QObject::connect(ghost_2, &Ghost::checkTile, board, &Board::checkBoard);

//    //QObject::connect(board, &Board::borderHit, ghost_1, &Ghost::changeDirection);
//    QObject::connect(board, &Board::borderHit, ghost_2, &Ghost::changeDirection);


//    QTimer player_timer;
//    QObject::connect(&player_timer, &QTimer::timeout, ghost_1, &Ghost::moveGhost);
//    QObject::connect(&player_timer, &QTimer::timeout, ghost_2, &Ghost::moveGhost);

//    QObject::connect(&player_timer, &QTimer::timeout, player, &Player::movePlayer);
//    player_timer.start(10);

//    QGraphicsView *view = new QGraphicsView(scene);
//    view->show();

    qDebug() << "before exec";
    return a.exec();
}

