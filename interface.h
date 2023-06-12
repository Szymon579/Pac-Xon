#ifndef INTERFACE_H
#define INTERFACE_H

#include "levelmanager.h"
#include "leaderboard.h"


#include <QWidget>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QStackedWidget>

namespace Ui
{
    class Interface;
}

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    Interface(QWidget *parent = nullptr);
    ~Interface();

    LevelManager level_manager;

private slots:
    void on_startButton_clicked();
    void on_leadButton_clicked();
    void on_backButton_clicked();
    void on_quitButton_clicked();


    void on_menuButton_clicked();

public slots:
    void livesSlot(int lives);
    void scoreSlot(double score);
    void levelSlot(int level);
    void pauseSlot(bool pause);

private:
    Ui::Interface *ui;
    QGraphicsScene *scene;

    Leaderboard leaderboard;

    void uiSetup();

    int level = 1;
    void updateLevelView(int level);

    int req_area = 20; //defalut 80
};

#endif // INTERFACE_H
