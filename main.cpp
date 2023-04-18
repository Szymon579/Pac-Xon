//#include "logic.h"
#include "player.h"
#include "board.h"

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
    //scene->addItem(board);
    //board->drawBoard();

    board->drawTileBoard();

    //adding player
    Player *player = new Player();
    scene->addItem(player);
    player->setZValue(5);

    QObject::connect(player, &Player::positionChanged, board, &Board::updateBoard);

    //timer
    QTimer player_timer;

    //QObject::connect(&player_timer, &QTimer::timeout, board, &Board::drawTileBoard);
    QObject::connect(&player_timer, &QTimer::timeout, player, &Player::movePlayer);
    player_timer.start(10);


    QGraphicsView *view = new QGraphicsView(scene);
    view->show();

    qDebug() << "before exec";
    return a.exec();
}

