#include "interface.h"
#include "ui_interface.h"

#include <QDebug>
#include <QGraphicsView>
#include <QWidget>
#include <QStackedWidget>

Interface::Interface(QGraphicsScene *scene, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interface)
{
    ui->setupUi(this);
    ui->stackView->setCurrentIndex(0);
    this->scene = scene;

    QPixmap start_pixmap(":/assets/play.png");
    QIcon start_icon(start_pixmap);
    ui->startButton->setIcon(start_icon);
    ui->startButton->setIconSize(start_pixmap.rect().size());

    QPixmap leader_pixmap(":/assets/results.png");
    QIcon leader_icon(leader_pixmap);
    ui->leadButton->setIcon(leader_icon);
    ui->leadButton->setIconSize(leader_pixmap.rect().size());

    QPixmap quit_pixmap(":/assets/quit.png");
    QIcon quit_icon(quit_pixmap);
    ui->quitButton->setIcon(quit_icon);
    ui->quitButton->setIconSize(quit_pixmap.rect().size());

    lives(3);
    score(0);

}

Interface::~Interface()
{
    delete ui;
}


void Interface::on_startButton_clicked()
{
    ui->stackView->setCurrentIndex(1);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

//main page
void Interface::on_leadButton_clicked()
{
    ui->stackView->setCurrentIndex(2);
}

void Interface::on_backButton_clicked()
{
    ui->stackView->setCurrentIndex(0);
}

void Interface::on_quitButton_clicked()
{
    QCoreApplication::quit();
}


//game page
void Interface::lives(int lives)
{
    std::string s_lives = std::to_string(lives);
    QString label = "lives: " + QString::fromStdString(s_lives);
    ui->livesLabel->setText(label);
}

void Interface::score(double score)
{
    score = round(score);
    int scr = int(score);

    std::string s_lives = std::to_string(scr);

    QString label = "score: " + QString::fromStdString(s_lives) + "%";
    ui->scoreLabel->setText(label);
}






