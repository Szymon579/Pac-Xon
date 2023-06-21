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

signals:
    void positionChanged(int y_pos, int x_pos, int y_prev_pos, int x_prev_pos);
    void pause();

public slots:
    void movePlayer();
    void drawingTraceSlot(bool drawing);
    void traceCrossedSlot();

private:
    MoveDirection direction;

    QPixmap player_texture;
    qreal player_size = 20;

    //textures of player
//    QPixmap pacman_left;
//    QPixmap pacman_right;
//    QPixmap pacman_up;
//    QPixmap pacman_down;

    QPixmap pacman_left = QPixmap(":/assets/pacman_left.png");
    QPixmap pacman_right = QPixmap(":/assets/pacman_right.png");
    QPixmap pacman_up = QPixmap(":/assets/pacman_up.png");
    QPixmap pacman_down = QPixmap(":/assets/pacman_down.png");

    int x_pos      = 0;
    int y_pos      = 0;
    int x_prev_pos = 0;
    int y_prev_pos = 0;

    bool buffer_left    = false;
    bool buffer_right   = false;
    bool buffer_up      = false;
    bool buffer_down    = false;

    bool drawing_trace  = false;

};

#endif // PLAYER_H
