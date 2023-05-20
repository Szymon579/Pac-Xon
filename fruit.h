#ifndef FRUIT_H
#define FRUIT_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QPixmap>

class Fruit : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Fruit(int y, int x);

private:
    QPixmap fruit_texture;
    qreal fruit_size = 20;

    int y_pos;
    int x_pos;


};

#endif // FRUIT_H
