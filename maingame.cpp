#include "maingame.h"

#include <QTimer>

MainGame::MainGame(QWidget *parent)
    : QMainWindow(parent)
{
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(5); //5ms
}

MainGame::~MainGame()
{
}

void MainGame::update()
{
    //all changes between frames will be precessed here
}

