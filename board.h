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

    void drawBoard();


private:
    void initBoard();

    QGraphicsScene *scene;
    static const int width = 45; //45
    static const int height = 30; //30

    int board[height][width];
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

    QPixmap blue_tile_texture;
    QPixmap black_tile_texture;

    QBrush blue_brush;
    QBrush black_brush;



};

#endif // BOARD_H
