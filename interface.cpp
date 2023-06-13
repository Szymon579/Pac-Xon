#include "interface.h"
#include "ui_interface.h"

#include <QDebug>
#include <QGraphicsView>
#include <QWidget>
#include <QStackedWidget>

Interface::Interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interface)
{
    ui->setupUi(this);
    ui->stackView->setCurrentIndex(0);

    uiSetup();

    QObject::connect(&level_manager, &LevelManager::livesSignal, this, &Interface::livesSlot);
    QObject::connect(&level_manager, &LevelManager::scoreSignal, this, &Interface::scoreSlot);
    QObject::connect(&level_manager, &LevelManager::levelSignal, this, &Interface::levelSlot);
    QObject::connect(&level_manager, &LevelManager::pauseSignal, this, &Interface::pauseSlot);


    ui->textEdit->setReadOnly(true);
    ui->textEdit->setFocusPolicy(Qt::NoFocus);
    ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

Interface::~Interface()
{
    delete ui;
}

void Interface::on_startButton_clicked()
{
    ui->stackView->setCurrentIndex(1);

    updateLevelView(level);
}

//main page
void Interface::on_leadButton_clicked()
{
    ui->stackView->setCurrentIndex(2);

    QString text = leaderboard.formatForDisplay();
    ui->textEdit->setText(text);

    QTextDocument* doc = ui->textEdit->document();
    doc->setDefaultTextOption(QTextOption(Qt::AlignCenter));
    ui->textEdit->setDocument(doc);

    //displayLeaderboard();
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
void Interface::livesSlot(int lives)
{
    std::string s_lives = std::to_string(lives);
    QString label = "lives: " + QString::fromStdString(s_lives);
    ui->livesLabel->setText(label);

    if(lives < 1)
    {
        ui->stackView->setCurrentIndex(2);
    }
}

void Interface::scoreSlot(double score)
{
    score = round(score);
    int scr = int(score);

    if(score > req_area)
    {
        updateLevelView(++level);
    }

    std::string s_lives = std::to_string(scr);

    QString label = "score: " + QString::fromStdString(s_lives) + "%";
    ui->scoreLabel->setText(label);
}

void Interface::levelSlot(int level)
{
    std::string s_lives = std::to_string(level);
    QString label = "level: " + QString::fromStdString(s_lives);
    ui->levelLabel->setText(label);
}

void Interface::pauseSlot(bool pause)
{
    ui->pauseWidget->setVisible(pause);
}

void Interface::uiSetup()
{
    //main page
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

    //leaderboard page
    QPixmap back_pixmap(":/assets/back60.png");
    QIcon back_icon(back_pixmap);
    ui->backButton->setIcon(back_icon);
    ui->backButton->setIconSize(back_pixmap.rect().size()/2);


    //game page
    ui->pauseWidget->setVisible(false);

//    QPixmap resume_pixmap(":/assets/resume60.png");
//    QIcon resume_icon(resume_pixmap);
//    ui->resumeButton->setIcon(resume_icon);
//    ui->resumeButton->setIconSize(resume_pixmap.rect().size()/2);

    QPixmap menu_pixmap(":/assets/quit.png");
    QIcon menu_icon(menu_pixmap);
    ui->menuButton->setIcon(menu_icon);
    ui->menuButton->setIconSize(menu_pixmap.rect().size()/2);

}

void Interface::updateLevelView(int level)
{
    level_manager.createLevel(level);
    this->scene = level_manager.scene;

    ui->graphicsView->setScene(scene);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Interface::displayLeaderboard()
{
    QString text;

    for(int i = 0; i < leaderboard.results_vec.size(); i++)
    {
        QString pos = QString::number(i+1);
        text += pos + ". " + leaderboard.results_vec.at(i).name + '\n';
    }

    ui->textEdit->setText(text);
}


void Interface::on_menuButton_clicked()
{
    ui->stackView->setCurrentIndex(0);
}



