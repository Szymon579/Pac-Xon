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
    Board(QGraphicsScene *scene, QObject *parent = nullptr);
    ~Board();

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

signals:
    void boardUpdated();
    void borderHit(int y_pos, int x_pos, bool left, bool right, bool up, bool down,
                   bool left_up, bool left_down, bool right_up, bool right_down, bool game_over);
    void coloredArea(double filled);
    void fruitEaten(int y_pos, int x_pos);
    void drawingTraceSignal(bool drawing);
    void suicide();

public slots:
    void updateBoardSlot(int y_pos, int x_pos, int y_prev_pos, int x_prev_pos);
    void handleGhostSlot(int y_pos, int x_pos, int y_prev_pos, int x_prev_pos); //checks surroundings
    void handleFruitSlot(int y_pos, int x_pos, bool active);


private:
    QGraphicsScene *scene;

    static const int height = 30;
    static const int width = 45;
    static const int depth = 2;

    LogicBoardEnum logic_board[depth][height][width];
    LogicBoardEnum helper_board[height][width];

    QGraphicsRectItem tile_board[height][width];

    void initLogicBoard();
    void initTileBoard(); //setting size and position of tiles
    void logicBoardToTileBoard(LogicBoardEnum tile, int y, int x);

    void rememberTrace(int y, int x);
    void traceDrawingSucceeded();
    void traceDrawingFailed();

    //algo
    void indexToFill();
    void tryForIndex(int y, int x);
    void fillArea(int y, int x);
    void rememberBoardState();
    void restoreBoardState();

    bool ghost_found;

    bool drawing_trace;
    std::vector<std::pair<int, int>> trace_cords;
    std::pair<int, int> first_trace;

    void howMuchFilled();

    QBrush black_brush;
    QBrush blue_brush;
    QBrush border_brush;
    QBrush trace_brush;

    void debugBoard(int layer);

};

#endif // BOARD_H
