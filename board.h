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
        // depth = 0 enums
        blue,
        black,
        trace,
        // depth = 1 enums
        player,
        ghost,
        fruit,
        none
    };

    void renderTileBoard();

public slots:
    void updateBoard(int y_pos, int x_pos, int y_prev_pos, int x_prev_pos);
    void checkBoard(int y_pos, int x_pos, int y_prev_pos, int x_prev_pos); //checks surroundings

signals:
    void boardUpdated();
    void borderHit(int y_pos, int x_pos, bool left, bool right, bool up, bool down,
                   bool left_up, bool left_down, bool right_up, bool right_down);
    void coloredArea(double filled);

private:
    QGraphicsScene *scene;

    static const int height = 30;//30
    static const int width = 45; //45
    static const int depth = 2;

    LogicBoardEnum logic_board[depth][height][width];
    LogicBoardEnum helper_board[height][width];

    QGraphicsRectItem tile_board[height][width];

    void initLogicBoard();
    void initTileBoard(); //setting size and position of tiles
    void logicBoardToTileBoard(LogicBoardEnum tile, int y, int x);

    void rememberTrace(int y, int x);
    void changeTraceToBlue();

    void indexToFill();
    void fillArea2(int y, int x);
    void fillArea(int y, int x);
    void rememberBoardState();
    void tryForIndex(int y, int x);
    bool ghost_found;

    bool drawing_trace;
    std::vector<std::pair<int, int>> trace_cords;
    std::pair<int, int> first_trace;

    void howMuchFilled();

    QPixmap blue_tile_texture;
    QPixmap black_tile_texture;
    QPixmap border_tile_texture;
    QPixmap trace_tile_texture;

    QBrush black_brush;
    QBrush blue_brush;
    QBrush border_brush;
    QBrush trace_brush;

    void debugBoard(int layer);

};

#endif // BOARD_H
