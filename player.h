#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QTimer>
#include <QObject>
#include <QPixmap>

class Player : public QObject, public QGraphicsRectItem
{

public:
    Player();

    qreal step = 1;
    enum MoveDirection {
        left,
        right,
        up,
        down,
        none
    };

    void keyPressEvent(QKeyEvent *event);
    void checkDirectionChange();
    void borderControl();
    void positionOnBoard();

public slots:
    void movePlayer();

private:
    MoveDirection direction;

    int x_pos;
    int y_pos;

    QPixmap player_texture;
    qreal player_size = 20;


    //hold textures of player
    QPixmap pacman_left;
    QPixmap pacman_right;
    QPixmap pacman_up;
    QPixmap pacman_down;

    //hold information about keyPressEvent to change direction when
    //player model lines up with center of column or row
    bool buffer_left;
    bool buffer_right;
    bool buffer_up;
    bool buffer_down;

};

#endif // PLAYER_H
