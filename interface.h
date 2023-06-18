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

private slots:
    //stasrtPage
    void on_startButton_clicked();
    void on_leadButton_clicked();
    void on_quitButton_clicked();

    //GamePage
    void on_menuButton_clicked();

    //leaderPage
    void on_backButton_clicked();
    void on_acceptButton_clicked();

public slots:
    void livesSlot(int lives);
    void scoreSlot(double score);
    void levelSlot(int level);
    void pauseSlot(bool pause);

private:
    Ui::Interface *ui;
    QGraphicsScene *scene;

    Leaderboard leaderboard;
    QString leaderboard_file = "test1.json";

    LevelManager level_manager;

    void uiSetup();
    void updateLevelView(int level);
    void displayLeaderboard();

    int achived_score = 0;
    int level = 1;
    int req_area = 20; //filled area required to finish the level

};

#endif // INTERFACE_H
