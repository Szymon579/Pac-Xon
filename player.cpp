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

    this->setRect(0, 0, player_size, player_size);
    this->setBrush(player_brush);
    this->setPen(Qt::NoPen);
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();

}

void Player::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left) {
        qDebug() << "left pressed";
        buffer_left = true;
    }
    if(event->key() == Qt::Key_Right) {
        qDebug() << "right pressed";
        buffer_right = true;
    }
    if(event->key() == Qt::Key_Up) {
        qDebug() << "up pressed";
        buffer_up = true;
    }
    if(event->key() == Qt::Key_Down) {
        qDebug() << "down pressed";
        buffer_down = true;
    }

    if(event->key() == Qt::Key_Escape) {
        qDebug() << "pause pressed";
        emit pause();
    }

}

void Player::allignDirectionChange()
{
    if(buffer_left && fmod(this->y(), player_size) == 0) {
        direction = MoveDirection::left;
        player_texture = pacman_left;
        buffer_left = false;
    }
    if(buffer_right && fmod(this->y(), player_size) == 0) {
        direction = MoveDirection::right;
        player_texture = pacman_right;
        buffer_right = false;
    }
    if(buffer_up && fmod(this->x(), player_size) == 0) {
        direction = MoveDirection::up;
        player_texture = pacman_up;
        buffer_up = false;
    }
    if(buffer_down && fmod(this->x(), player_size) == 0) {
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
    if(direction == MoveDirection::right && this->x() == 900 - player_size) {
        direction = MoveDirection::none;
    }
    if(direction == MoveDirection::up && this->y() == 0) {
        direction = MoveDirection::none;
    }
    if(direction == MoveDirection::down && this->y() == 600 - player_size) {
        direction = MoveDirection::none;
    }

}

void Player::positionOnBoard()
{
    x_prev_pos = x_pos;
    y_prev_pos = y_pos;

    if(fmod(this->x(), player_size) == 0)
        x_pos = this->x() / player_size;

    if(fmod(this->y(), player_size) == 0)
        y_pos = this->y() / player_size;

    if(y_prev_pos != y_pos || x_prev_pos != x_pos)
        emit positionChanged(y_pos, x_pos, y_prev_pos, x_prev_pos); //to be received in board.cpp

}

void Player::setMoveDirection(MoveDirection dir)
{
    direction = dir;
}

void Player::movePlayer()
{
    borderControl();
    allignDirectionChange();
    positionOnBoard();

    if(direction == MoveDirection::left) {
        if(x_pos == 0)
            return;
        setPos(x() - step, y());
    }
    if(direction == MoveDirection::right) {
        if(x_pos == 44)
            return;
        setPos(x() + step, y());
    }
    if(direction == MoveDirection::up) {
        if(y_pos == 0)
            return;
        setPos(x(), y() - step);
    }
    if(direction == MoveDirection::down) {
        if(y_pos == 29)
            return;
        setPos(x(), y() + step);
    }
    if(direction == MoveDirection::none) {
        //do not move;
    }

}

