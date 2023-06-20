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
    void addToScene();
    void givePower(Fruit::Power power, int effect_time);
    void disablePower(Fruit::Power power);

public slots:
    void setOnBoard();
    void eraseFromBoard();
    void eaten(int y_pos, int x_pos);
    void endOfPower();

private:
    QPixmap fruit_texture;
    qreal fruit_size = 20;
    QTimer spawn_timer;
    QTimer effect_timer;


    Power power;

    int y_pos;
    int x_pos;
    bool is_active = true;
    int time_to_spawn = 0;
    int effect_time = 5;

};

#endif // FRUIT_H
