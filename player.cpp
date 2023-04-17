#include "player.h"

#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <QObject>
#include <QPixmap>
#include <QPen>
#include <QBrush>

#include <cmath>

Player::Player()
{
    pacman_left = QPixmap(":/assets/pacman_left.png");
    pacman_right = QPixmap(":/assets/pacman_right.png");
    pacman_up = QPixmap(":/assets/pacman_up.png");
    pacman_down = QPixmap(":/assets/pacman_down.png");

    player_texture = pacman_right;
    QBrush player_brush(player_texture);

    direction = MoveDirection::none;

    buffer_left = false;
    buffer_right = false;
    buffer_up = false;
    buffer_down = false;

    this->setRect(0, 0, player_width, player_height);
    this->setBrush(player_brush);
    this->setPen(Qt::NoPen);
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();

}

void Player::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left) {
        qDebug() << "left";
        buffer_left = true;
    }
    if(event->key() == Qt::Key_Right) {
        qDebug() << "right";
        buffer_right = true;
    }
    if(event->key() == Qt::Key_Up) {
        qDebug() << "up";
        buffer_up = true;
    }
    if(event->key() == Qt::Key_Down) {
        qDebug() << "down";
        buffer_down = true;
    }

    if(event->key() == Qt::Key_P) {
        qDebug() << "stop";
        direction = MoveDirection::none;
    }

}

void Player::checkDirectionChange()
{
    if(buffer_left && fmod(this->y(), 20) == 0) {
        qDebug() << "left";
        direction = MoveDirection::left;
        player_texture = pacman_left;
        buffer_left = false;
    }
    if(buffer_right && fmod(this->y(), 20) == 0) {
        qDebug() << "right";
        direction = MoveDirection::right;
        player_texture = pacman_right;
        buffer_right = false;
    }
    if(buffer_up && fmod(this->x(), 20) == 0) {
        qDebug() << "up";
        direction = MoveDirection::up;
        player_texture = pacman_up;
        buffer_up = false;
    }
    if(buffer_down && fmod(this->x(), 20) == 0) {
        qDebug() << "down";
        direction = MoveDirection::down;
        player_texture = pacman_down;
        buffer_down = false;
    }

    QBrush brush(player_texture);
    this->setBrush(brush);
}

void Player::borderControl()
{
    if(direction == MoveDirection::left && this->x() == 0) {
        direction = MoveDirection::none;
    }
    if(direction == MoveDirection::right && this->x() == 900 - player_width) {
        direction = MoveDirection::none;
    }
    if(direction == MoveDirection::up && this->y() == 0) {
        direction = MoveDirection::none;
    }
    if(direction == MoveDirection::down && this->y() == 600 - player_height) {
        direction = MoveDirection::none;
    }

}

void Player::movePlayer()
{
    borderControl();
    checkDirectionChange();

    if(direction == MoveDirection::left) {
        setPos(x() - step, y());
    }
    if(direction == MoveDirection::right) {
        setPos(x() + step, y());
    }
    if(direction == MoveDirection::up) {
        setPos(x(), y() - step);
    }
    if(direction == MoveDirection::down) {
        setPos(x(), y() + step);
    }
    if(direction == MoveDirection::none) {
        //dont move;
    }

}

