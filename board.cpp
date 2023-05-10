#include "board.h"

#include <QPen>
#include <QGraphicsScene>
#include <QDebug>
#include <iostream>

Board::Board(QGraphicsScene *scene, QObject *parent)
    : QObject{parent}
{
    this->scene = scene;

    initLogicBoard();
    initTileBoard();

    blue_tile_texture = QPixmap(":/assets/tile_border.png");
    black_tile_texture = QPixmap(":/assets/tile_black.png");
    border_tile_texture = QPixmap(":/assets/tile_border.png");
    trace_tile_texture = QPixmap(":/assets/tile_red.png");

    black_brush = QBrush(black_tile_texture);
    blue_brush = QBrush(blue_tile_texture);
    border_brush = QBrush(border_tile_texture);
    trace_brush = QBrush(trace_tile_texture);
}

void Board::initLogicBoard()
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            logic_board[0][i][j] = LogicBoardEnum::black;

            //top and bottom border
            logic_board[0][0][j] = LogicBoardEnum::blue;
            logic_board[0][height - 1][j] = LogicBoardEnum::blue;
        }

        //left and right border
        logic_board[0][i][0] = LogicBoardEnum::blue;
        logic_board[0][i][width - 1] = LogicBoardEnum::blue;
    }
}

void Board::initTileBoard()
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            tile_board[i][j].setRect(0 + (20 * j), 0 + (20 * i), 20, 20);
        }
    }
}

void Board::drawTileBoard()
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(logic_board[0][i][j] == LogicBoardEnum::blue)
                tile_board[i][j].setBrush(border_brush);
            else
                tile_board[i][j].setBrush(black_brush);

            scene->addItem(&tile_board[i][j]);
        }
    }
}

void Board::logicBoardToTileBoard(LogicBoardEnum tile, int y, int x)
{
    switch(tile)
    {
    case blue:
        tile_board[y][x].setBrush(blue_brush);
        break;
    case black:
        tile_board[y][x].setBrush(black_brush);
        break;
    case trace:
        tile_board[y][x].setBrush(trace_brush);
        break;
    }
}

void Board::rememberTrace(int y, int x)
{
    std::pair<int, int> cords;
    cords.first = y;
    cords.second = x;

    trace_cords.push_back(cords);
    //qDebug() << "pushed to trace_cords y: " << cords.first << ", x: " << cords.second;
}

void Board::changeTraceToBlue()
{
    for(int i = 0; i < trace_cords.size(); i++)
    {
        tile_board[trace_cords[i].first][trace_cords[i].second].setBrush(blue_brush);
    }

    if(trace_cords.size() != 0)
    {
        first_trace = trace_cords.front();
        indexToFill();
    }

    trace_cords.clear();
}

void Board::indexToFill()
{ 
    qDebug() << "indexToFill() calle for y: " << first_trace.first <<
                ", x: " << first_trace.second;

    fillArea2(first_trace.first + 1, first_trace.second + 1);
    debugBoard(0);
}

void Board::fillArea2(int y, int x)
{
    int help_y = y;
    int help_x = x;

    //get ghost position
    //if ghost position in fillArea -> abort

    //ghost cord kept in logic board

    logic_board[0][help_y][help_x] = LogicBoardEnum::blue;
    logicBoardToTileBoard(LogicBoardEnum::blue, help_y, help_x);

    if (logic_board[0][help_y + 1][help_x] == LogicBoardEnum::black)
    {
        help_y++;
        logic_board[0][help_y][help_x] = LogicBoardEnum::blue;
        logicBoardToTileBoard(LogicBoardEnum::blue, help_y, help_x);
        fillArea2(help_y, help_x);
    }
    if (logic_board[0][help_y - 1][help_x] == LogicBoardEnum::black)
    {
        help_y--;
        logic_board[0][help_y][help_x] = LogicBoardEnum::blue;
        logicBoardToTileBoard(LogicBoardEnum::blue, help_y, help_x);
        fillArea2(help_y, help_x);
    }
    if (logic_board[0][help_y][help_x + 1] == LogicBoardEnum::black)
    {
        help_x++;
        logic_board[0][help_y][help_x] = LogicBoardEnum::blue;
        logicBoardToTileBoard(LogicBoardEnum::blue, help_y, help_x);
        fillArea2(help_y, help_x);
    }
    if (logic_board[0][help_y][help_x - 1] == LogicBoardEnum::black)
    {
        help_x--;
        logic_board[0][help_y][help_x] = LogicBoardEnum::blue;
        logicBoardToTileBoard(LogicBoardEnum::blue, help_y, help_x);
        fillArea2(help_y, help_x);
    }
    else
    {
        return;
    }
}



void Board::updateBoard(int y_pos, int x_pos, int y_prev_pos, int x_prev_pos)
{
    logic_board[1][y_pos][x_pos] = LogicBoardEnum::player;
    logic_board[1][y_prev_pos][x_prev_pos] = LogicBoardEnum::none;

    if(logic_board[0][y_pos][x_pos] == LogicBoardEnum::blue)
    {
        drawing_trace = false;
    }

    if(logic_board[0][y_pos][x_pos] == LogicBoardEnum::black)
    {
        drawing_trace = true;
        rememberTrace(y_pos, x_pos);
    }

    if(!drawing_trace)
    {
        changeTraceToBlue();
        //debugBoard(1);
    }

    if(logic_board[0][y_pos][x_pos] != LogicBoardEnum::blue)
    {
        logicBoardToTileBoard(LogicBoardEnum::trace, y_pos, x_pos);
    }

    logic_board[0][y_pos][x_pos] = LogicBoardEnum::blue;


    emit boardUpdated();
}

void Board::checkBoard(int y_pos, int x_pos, int y_prev_pos, int x_prev_pos)
{
    logic_board[1][y_pos][x_pos] = LogicBoardEnum::ghost;
    logic_board[1][y_prev_pos][x_prev_pos] = LogicBoardEnum::none;

    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;

    if(logic_board[0][y_pos][x_pos-1] != LogicBoardEnum::black)
        left = true;
    if(logic_board[0][y_pos][x_pos+1] != LogicBoardEnum::black)
        right = true;
    if(logic_board[0][y_pos-1][x_pos] != LogicBoardEnum::black)
        up = true;
    if(logic_board[0][y_pos+1][x_pos] != LogicBoardEnum::black)
        down = true;

    emit borderHit(y_pos, x_pos, left, right, up, down);
}


void Board::debugBoard(int layer)
{
    std::cout << "debugBoard() called" << std::endl;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            switch(logic_board[layer][i][j])
            {
            case blue:
                std::cout << "1 ";
                break;
            case black:
                std::cout << "0 ";
                break;
            case trace:
                std::cout << "3 ";
                break;

            case player:
                std::cout << "1 ";
                break;
            case ghost:
                std::cout << "2 ";
                break;
            case fruit:
                std::cout << "3 ";
                break;
            case none:
                std::cout << "0 ";
                break;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}




