#ifndef MAINGAME_H
#define MAINGAME_H

#include <QMainWindow>

class MainGame : public QMainWindow
{
    Q_OBJECT

public:
    MainGame(QWidget *parent = nullptr);
    ~MainGame();

public slots:
    void update();

private:
    QTimer *timer;
    int board[10][10];
};
#endif // MAINGAME_H
