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
    blue_brush = QBrush(blue_tile_texture);

    black_tile_texture = QPixmap(":/assets/tile_black.png");
    black_brush = QBrush(black_tile_texture);

    border_tile_texture = QPixmap(":/assets/tile_border.png");
    border_brush = QBrush(border_tile_texture);

    trace_tile_texture = QPixmap(":/assets/tile_red.png");
    trace_brush = QBrush(trace_tile_texture);
}

//setting tile burshes based on enum value
void Board::drawTileBoard()
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(logic_board[i][j][0] == LogicBoardEnum::border)
                tile_board[i][j].setBrush(border_brush);
            else
                tile_board[i][j].setBrush(black_brush);

            scene->addItem(&tile_board[i][j]);
        }
    }

    qDebug() << "drawTileBoard called";
}

void Board::initLogicBoard()
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            logic_board[i][j][0] = LogicBoardEnum::black;

            //top and bottom border
            logic_board[0][j][0] = LogicBoardEnum::border;
            logic_board[height - 1][j][0] = LogicBoardEnum::border;
        }

        //left and right border
        logic_board[i][0][0] = LogicBoardEnum::border;
        logic_board[i][width - 1][0] = LogicBoardEnum::border;
    }

    //debugBoard();
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
    case border:
        tile_board[y][x].setBrush(border_brush);
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

    fillArea(first_trace.first + 1, first_trace.second + 1);
    debugBoard();
}

void Board::fillArea(int y, int x)
{
    int help_y = y;
    int help_x = x;

    //get ghost position
    //if ghost position in fillArea -> abort

    //ghost cord kept in logic board

    logic_board[help_y][help_x][0] = LogicBoardEnum::blue;
    logicBoardToTileBoard(LogicBoardEnum::blue, help_y, help_x);

    if (logic_board[help_y + 1][help_x][0] == LogicBoardEnum::black)
    {
        help_y++;
        logic_board[help_y][help_x][0] = LogicBoardEnum::blue;
        logicBoardToTileBoard(LogicBoardEnum::blue, help_y, help_x);
        fillArea(help_y, help_x);
    }
    if (logic_board[help_y - 1][help_x][0] == LogicBoardEnum::black)
    {
        help_y--;
        logic_board[help_y][help_x][0] = LogicBoardEnum::blue;
        logicBoardToTileBoard(LogicBoardEnum::blue, help_y, help_x);
        fillArea(help_y, help_x);
    }
    if (logic_board[help_y][help_x + 1][0] == LogicBoardEnum::black)
    {
        help_x++;
        logic_board[help_y][help_x][0] = LogicBoardEnum::blue;
        logicBoardToTileBoard(LogicBoardEnum::blue, help_y, help_x);
        fillArea(help_y, help_x);
    }
    if (logic_board[help_y][help_x - 1][0] == LogicBoardEnum::black)
    {
        help_x--;
        logic_board[help_y][help_x][0] = LogicBoardEnum::blue;
        logicBoardToTileBoard(LogicBoardEnum::blue, help_y, help_x);
        fillArea(help_y, help_x);
    }
    else
    {
        return;
    }
}



void Board::updateBoard(int y_pos, int x_pos)
{
    if(logic_board[y_pos][x_pos][0] == LogicBoardEnum::border ||
       logic_board[y_pos][x_pos][0] == LogicBoardEnum::blue)
    {
        drawing_trace = false;
    }

    if(logic_board[y_pos][x_pos][0] == LogicBoardEnum::black)
    {
        drawing_trace = true;
        rememberTrace(y_pos, x_pos);
    }

    if(!drawing_trace)
    {
        //qDebug() << "drawing_trace = false";
        changeTraceToBlue();
    }

    if(logic_board[y_pos][x_pos][0] != LogicBoardEnum::border &&
       logic_board[y_pos][x_pos][0] != LogicBoardEnum::blue)
    {
        logicBoardToTileBoard(LogicBoardEnum::trace, y_pos, x_pos);
    }


    logic_board[y_pos][x_pos][0] = LogicBoardEnum::blue;

    emit boardUpdated();
}

void Board::checkBoard(int y_pos, int x_pos)
{
    //qDebug() << "checkBoard()";

    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;

    if(logic_board[y_pos][x_pos-1][0] != LogicBoardEnum::black)
        left = true;
    if(logic_board[y_pos][x_pos+1][0] != LogicBoardEnum::black)
        right = true;
    if(logic_board[y_pos-1][x_pos][0] != LogicBoardEnum::black)
        up = true;
    if(logic_board[y_pos+1][x_pos][0] != LogicBoardEnum::black)
        down = true;

    emit borderHit(y_pos, x_pos, left, right, up, down);

}


void Board::debugBoard()
{
    std::cout << "debugBoard() called" << std::endl;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            switch(logic_board[i][j][0])
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
            case border:
                std::cout << "4 ";
                break;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}




