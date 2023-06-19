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
    enum Power
    {
        slow_ghost,
        fast_player,
        add_life
    };

    Fruit(int y, int x, int time, Fruit::Power power);


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

    Power power;

    int y_pos;
    int x_pos;
    bool is_active = true;
    int sec_active = 0;

};

#endif // FRUIT_H
