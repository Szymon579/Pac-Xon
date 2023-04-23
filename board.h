#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QBrush>

class Board : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Board(QGraphicsScene *scene, QObject *parent = nullptr);

    enum LogicBoardEnum
    {
        blue,   //blue area
        black,  //black area
        border, //trace after filling marked area
        trace   //trace drawn by the player before closing with border
    };

    void drawTileBoard();

public slots:
    void updateBoard(int y_pos, int x_pos);

private:
    void initLogicBoard();
    void initTileBoard();
    void logicBoardToTileBoard(LogicBoardEnum tile, int y, int x);

    void rememberTrace(int y, int x);
    void changeTraceToBlue();

    void indexToFill();
    void fillAreaLogic(int y, int x);
    void fillArea(int y, int x);

    QGraphicsScene *scene;
    static const int width = 45; //45
    static const int height = 30; //30

    LogicBoardEnum logic_board[height][width];
//    {
//        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
//    };

    QGraphicsRectItem tile_board[height][width];


    bool drawing_trace;
    std::vector<std::pair<int, int>> trace_cords;
    std::pair<int, int> first_trace;


    QPixmap blue_tile_texture;
    QBrush blue_brush;

    QPixmap black_tile_texture;
    QBrush black_brush;

    QPixmap border_tile_texture;
    QBrush border_brush;

    QPixmap trace_tile_texture;
    QBrush trace_brush;

    void debugBoard();

};

#endif // BOARD_H
