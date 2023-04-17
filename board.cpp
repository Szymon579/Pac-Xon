#include "board.h"

#include <QPen>
#include <QGraphicsScene>
#include <QDebug>

Board::Board(QGraphicsScene *scene, QObject *parent)
    : QObject{parent}
{
    this->scene = scene;

    initBoard();

    blue_tile_texture = QPixmap(":/assets/blue_tile.png");
    blue_brush = QBrush(blue_tile_texture);

    black_tile_texture = QPixmap(":/assets/black_tile.png");
    black_brush = QBrush(black_tile_texture);
}

void Board::initBoard()
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            board[i][j] = 0;

            //top and bottom border
            board[0][j] = 1;
            board[height - 1][j] = 1;
        }

        //left and right border
        board[i][0] = 1;
        board[i][width - 1] = 1;
    }
}

void Board::drawBoard()
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            QGraphicsRectItem *tile = new QGraphicsRectItem();
            //qDebug() << "iteration nr: " << i << ", " << j;
            tile->setRect(0 + (20 * j), 0 + (20 * i), 20, 20);

            if(board[i][j] == 1)
                tile->setBrush(blue_brush);
            else
                tile->setBrush(black_brush);

            scene->addItem(tile);
        }
    }

    qDebug() << "drawBoard called";
}



