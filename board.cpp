#include "board.h"

#include <QPen>
#include <QGraphicsScene>
#include <QDebug>

Board::Board(QGraphicsScene *scene, QObject *parent)
    : QObject{parent}
{
    this->scene = scene;

    initLogicBoard();
    initTileBoard();

    blue_tile_texture = QPixmap(":/assets/blue_tile.png");
    blue_brush = QBrush(blue_tile_texture);

    black_tile_texture = QPixmap(":/assets/black_tile.png");
    black_brush = QBrush(black_tile_texture);

    border_tile_texture = QPixmap(":/assets/border_tile.png");
    border_brush = QBrush(border_tile_texture);

    trace_tile_texture = QPixmap(":/assets/trace_tile.png");
    trace_brush = QBrush(trace_tile_texture);
}

void Board::initLogicBoard()
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            logic_board[i][j] = LogicBoardEnum::black;

            //top and bottom border
            logic_board[0][j] = LogicBoardEnum::border;
            logic_board[height - 1][j] = LogicBoardEnum::border;
        }

        //left and right border
        logic_board[i][0] = LogicBoardEnum::border;
        logic_board[i][width - 1] = LogicBoardEnum::border;
    }
}

void Board::initTileBoard()
{
    //setting size and position of tiles
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            tile_board[i][j].setRect(0 + (20 * j), 0 + (20 * i), 20, 20);

        }
    }
}

void Board::logicBoardToTileBoard(LogicBoardEnum tile, int x, int y)
{
    switch(tile)
    {
    case blue:
        tile_board[x][y].setBrush(blue_brush);
        break;
    case black:
        tile_board[x][y].setBrush(black_brush);
        break;
    case border:
        tile_board[x][y].setBrush(border_brush);
        break;
    case trace:
        tile_board[x][y].setBrush(trace_brush);
        break;
    }
}

void Board::rememberTrace(int x, int y)
{
    std::pair<int, int> cords;
    cords.first = y;
    cords.second = x;

    trace_cords.push_back(cords);
    qDebug() << "pushed to trace_cords x: " << cords.first << ", y: " << cords.second;
}

void Board::changeTraceToBlue()
{
    for(int i = 0; i < trace_cords.size(); i++)
    {
        tile_board[trace_cords[i].second][trace_cords[i].first].setBrush(blue_brush);
    }

    trace_cords.clear();
}

//setting tile burshes based on enum value
void Board::drawTileBoard()
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(logic_board[i][j] == LogicBoardEnum::border)
                tile_board[i][j].setBrush(border_brush);
            else
                tile_board[i][j].setBrush(black_brush);

            scene->addItem(&tile_board[i][j]);
        }
    }

    qDebug() << "drawTileBoard called";
}

void Board::updateBoard(int x_pos, int y_pos)
{
    if(logic_board[y_pos][x_pos] == LogicBoardEnum::border ||
       logic_board[y_pos][x_pos] == LogicBoardEnum::blue)
    {
        drawing_trace = false;
    }

    if(logic_board[y_pos][x_pos] == LogicBoardEnum::black)
    {
        drawing_trace = true;
        rememberTrace(y_pos, x_pos);
    }

    if(!drawing_trace)
    {
        changeTraceToBlue();
    }

    if(logic_board[y_pos][x_pos] != LogicBoardEnum::border &&
       logic_board[y_pos][x_pos] != LogicBoardEnum::blue)
    {
        logicBoardToTileBoard(LogicBoardEnum::trace, y_pos, x_pos);
    }


    //TODO: check if pacman is on blue already or if
    //      he is drawing a trace on black area
    logic_board[y_pos][x_pos] = LogicBoardEnum::blue;
}




