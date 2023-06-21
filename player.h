#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QTimer>
#include <QObject>
#include <QPixmap>

class Player : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Player();

    qreal step = 1;

    enum MoveDirection
    {
        left,
        right,
        up,
        down,
        none
    };

    void keyPressEvent(QKeyEvent *event);
    void alignDirectionChange();
    void borderControl();
    void updatePosOnBoard();
    void neverGoBack();

    void resetAfterKilled();

public slots:
    void movePlayer();
    void drawingTraceSlot(bool drawing);

signals:
    void positionChanged(int y_pos, int x_pos, int y_prev_pos, int x_prev_pos);
    void pause();

private:
    MoveDirection direction;

    QPixmap player_texture;
    qreal player_size = 20;

    //textures of player
    QPixmap pacman_left;
    QPixmap pacman_right;
    QPixmap pacman_up;
    QPixmap pacman_down;

    //player's x and y cords
    int x_pos = 0;
    int y_pos = 0;
    int x_prev_pos = 0;
    int y_prev_pos = 0;

    //hold information about keyPressEvent to change direction when
    //player model lines up with center of column or row
    bool buffer_left;
    bool buffer_right;
    bool buffer_up;
    bool buffer_down;

    bool drawing_trace = false;

};

#endif // PLAYER_H
