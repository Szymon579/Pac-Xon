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

    Board *board = new Board();
    //scene->addItem(board);
    board->drawBoard(scene);




    //adding player
    Player *rect = new Player();
    scene->addItem(rect);


    //timer
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, rect, &Player::movePlayer);
    timer.start(10);


    QGraphicsView *view = new QGraphicsView(scene);
    view->show();

    return a.exec();
}

