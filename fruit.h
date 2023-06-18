#ifndef FRUIT_H
#define FRUIT_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QPixmap>
#include <QTimer>

class Fruit : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Fruit(int y, int x);

    enum Power
    {
        slow_ghost,
        fast_player,
        add_life
    };

signals:
    void setPosOnBoard(int y_pos, int x_pos, bool active);
    void deleteFromScene();

public slots:
    void setOnBoard();
    void eraseFromBoard();

private:
    QPixmap fruit_texture;
    qreal fruit_size = 20;
    QTimer timer;

    int y_pos;
    int x_pos;
    bool active = true;
    int sec_active = 10;

    qreal fruit_timer = 50000;


};

#endif // FRUIT_H
