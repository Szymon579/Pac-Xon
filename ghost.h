#ifndef GHOST_H
#define GHOST_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QPixmap>

class Ghost : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Ghost();

signals:

private:
    QPixmap ghost_texture;
    qreal ghost_size = 20;

};

#endif // GHOST_H
