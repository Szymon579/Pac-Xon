#ifndef MAINGAME_H
#define MAINGAME_H

#include <QMainWindow>

class MainGame : public QMainWindow
{
    Q_OBJECT

public:
    MainGame(QWidget *parent = nullptr);
    ~MainGame();
};
#endif // MAINGAME_H
