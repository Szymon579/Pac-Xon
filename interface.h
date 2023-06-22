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
    //startPage
    void on_startButton_clicked();
    void on_leadButton_clicked();
    void on_quitButton_clicked();

    //GamePage
    void on_menuButton_clicked();

    //leaderPage
    void on_backButton_clicked();
    void on_acceptButton_clicked();

public slots:
    void levelSlot(int level);
    void livesSlot(int lives);
    void areaSlot(double area);
    void scoreSlot(int score);

    void pauseSlot(bool pause);
    void gameOverSlot();

signals:
    void scoreSignal(int score);

private:
    Ui::Interface *ui;
    QGraphicsScene *scene;

    LevelManager level_manager;

    Leaderboard leaderboard;
    QString leaderboard_file = "leaderboard.json";

    int total_score = 0;
    int level = 1;
    int lives = 3;
    int required_area = 80; //filled area required to finish the level

    void uiSetup();
    void updateLevelView(int level);
    void displayLeaderboard();

};

#endif // INTERFACE_H
