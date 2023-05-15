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

            if(logic_board[0][i][j] == LogicBoardEnum::blue)
                tile_board[i][j].setBrush(border_brush);
            else
                tile_board[i][j].setBrush(black_brush);

            scene->addItem(&tile_board[i][j]);
        }
    }
}

void Board::renderTileBoard()
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(logic_board[0][i][j] == LogicBoardEnum::blue)
                tile_board[i][j].setBrush(border_brush);
            else
                tile_board[i][j].setBrush(black_brush);
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

    int y = first_trace.first;
    int x = first_trace.second;

    debugBoard(0);
    debugBoard(1);


    ghost_found = false;
    rememberBoardState();

    if (logic_board[0][y + 1][x] == LogicBoardEnum::black)
    {
        tryForIndex(y + 1, x);
    }

    ghost_found = false;
    rememberBoardState();

    if (logic_board[0][y - 1][x] == LogicBoardEnum::black)
    {
        tryForIndex(y - 1, x);
    }

    ghost_found = false;
    rememberBoardState();

    if (logic_board[0][y][x - 1] == LogicBoardEnum::black)
    {
        tryForIndex(y, x - 1);
    }

    ghost_found = false;
    rememberBoardState();

    if (logic_board[0][y][x + 1] == LogicBoardEnum::black)
    {
        tryForIndex(y, x + 1);
    }

    ghost_found = false;

    renderTileBoard();
    debugBoard(0);
}

void Board::fillArea(int y, int x)
{
    int help_y = y;
    int help_x = x;

    if (logic_board[1][help_y][help_x] == LogicBoardEnum::ghost)
    {
        ghost_found = true;
    }

    if (logic_board[0][help_y + 1][help_x] == LogicBoardEnum::black)
    {
        help_y++;
        logic_board[0][help_y][help_x] = LogicBoardEnum::blue;
        logicBoardToTileBoard(LogicBoardEnum::blue, help_y, help_x);
        fillArea(help_y, help_x);
    }
    if (logic_board[0][help_y - 1][help_x] == LogicBoardEnum::black)
    {
        help_y--;
        logic_board[0][help_y][help_x] = LogicBoardEnum::blue;
        logicBoardToTileBoard(LogicBoardEnum::blue, help_y, help_x);
        fillArea(help_y, help_x);
    }
    if (logic_board[0][help_y][help_x + 1] == LogicBoardEnum::black)
    {
        help_x++;
        logic_board[0][help_y][help_x] = LogicBoardEnum::blue;
        logicBoardToTileBoard(LogicBoardEnum::blue, help_y, help_x);
        fillArea(help_y, help_x);
    }
    if (logic_board[0][help_y][help_x - 1] == LogicBoardEnum::black)
    {
        help_x--;
        logic_board[0][help_y][help_x] = LogicBoardEnum::blue;
        logicBoardToTileBoard(LogicBoardEnum::blue, help_y, help_x);
        fillArea(help_y, help_x);
    }
    else
    {
        return;
    }
}

void Board::rememberBoardState()
{
    for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                helper_board[y][x] = logic_board[0][y][x];
            }
    }
}

void Board::tryForIndex(int y, int x)
{
    fillArea(y, x);

    if (ghost_found == true)
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                logic_board[0][y][x] = helper_board[y][x];
            }
        }
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
    qDebug() << "checkBoard called for y:" << y_pos << ", x: " << x_pos;
    logic_board[1][y_pos][x_pos] = LogicBoardEnum::ghost;

    if(y_pos != y_prev_pos || x_pos != x_prev_pos)
        logic_board[1][y_prev_pos][x_prev_pos] = LogicBoardEnum::none;

    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;
    bool left_up = false;
    bool left_down = false;
    bool right_up = false;
    bool right_down = false;

    if(logic_board[0][y_pos][x_pos-1] != LogicBoardEnum::black)
        left = true;
    if(logic_board[0][y_pos][x_pos+1] != LogicBoardEnum::black)
        right = true;
    if(logic_board[0][y_pos-1][x_pos] != LogicBoardEnum::black)
        up = true;
    if(logic_board[0][y_pos+1][x_pos] != LogicBoardEnum::black)
        down = true;

    if(logic_board[0][y_pos-1][x_pos-1] != LogicBoardEnum::black)
        left_up = true;
    if(logic_board[0][y_pos+1][x_pos-1] != LogicBoardEnum::black)
        left_down = true;
    if(logic_board[0][y_pos-1][x_pos+1] != LogicBoardEnum::black)
        right_up = true;
    if(logic_board[0][y_pos+1][x_pos+1] != LogicBoardEnum::black)
        right_down = true;

    emit borderHit(y_pos, x_pos, left, right, up, down,
                   left_up, left_down, right_up, right_down);
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
                std::cout << "P ";
                break;
            case ghost:
                std::cout << "G ";
                break;
            case fruit:
                std::cout << "3 ";
                break;
            case none:
                std::cout << "0 ";
                break;
            default:
                std::cout << "0 ";
                break;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}




