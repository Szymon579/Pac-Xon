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
    QObject::connect(&level_manager, &LevelManager::areaSignal, this, &Interface::areaSlot);
    QObject::connect(&level_manager, &LevelManager::levelSignal, this, &Interface::levelSlot);
    QObject::connect(&level_manager, &LevelManager::pauseSignal, this, &Interface::pauseSlot);
    QObject::connect(this, &Interface::scoreSignal, this, &Interface::scoreSlot);

    leaderboard.parseJson(leaderboard_file);
}

Interface::~Interface()
{
    delete ui;
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

    QPixmap accept_pixmap(":/assets/accept.png");
    QIcon accept_icon(accept_pixmap);
    ui->acceptButton->setIcon(accept_icon);
    ui->acceptButton->setIconSize(accept_pixmap.rect().size()/2);

    ui->leaderEdit->setReadOnly(true);
    ui->leaderEdit->setFocusPolicy(Qt::NoFocus);
    ui->leaderEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->leaderEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->nameEdit->setPlaceholderText(" Your nickname:");

    //game page
    QPixmap menu_pixmap(":/assets/quit.png");
    QIcon menu_icon(menu_pixmap);
    ui->menuButton->setIcon(menu_icon);
    ui->menuButton->setIconSize(menu_pixmap.rect().size()/2);

    ui->pauseWidget->setVisible(false);

}

//main page
void Interface::on_startButton_clicked()
{
    ui->stackView->setCurrentIndex(1);
    updateLevelView(1);
}

void Interface::on_leadButton_clicked()
{
    ui->nameEdit->setVisible(false);
    ui->acceptButton->setVisible(false);

    ui->stackView->setCurrentIndex(2);

    displayLeaderboard();
}

void Interface::on_quitButton_clicked()
{
    QCoreApplication::quit();
}

//game page
void Interface::on_menuButton_clicked()
{
    ui->stackView->setCurrentIndex(0);
}

void Interface::updateLevelView(int level)
{
    level_manager.createLevel(level);
    this->scene = level_manager.scene;

    ui->graphicsView->setScene(scene);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

//leader page
void Interface::displayLeaderboard()
{
    leaderboard.sort();

    QString text = leaderboard.formatForDisplay();
    ui->leaderEdit->setText(text);

    QTextDocument* doc = ui->leaderEdit->document();
    doc->setDefaultTextOption(QTextOption(Qt::AlignCenter));
    ui->leaderEdit->setDocument(doc);
}

void Interface::on_acceptButton_clicked()
{
    leaderboard.addResult(ui->nameEdit->text(), achived_score);
    ui->nameEdit->clear();

    displayLeaderboard();
}

void Interface::on_backButton_clicked()
{
    ui->stackView->setCurrentIndex(0);
    leaderboard.saveToJsonFile(leaderboard_file);
}

//slots
void Interface::livesSlot(int lives)
{
    std::string s_lives = std::to_string(lives);
    QString label = "LIVES: " + QString::fromStdString(s_lives);
    ui->livesLabel->setText(label);

    if(lives < 1)
    {
        ui->stackView->setCurrentIndex(2);
        ui->nameEdit->setVisible(true);
        ui->acceptButton->setVisible(true);
        displayLeaderboard();
    }
}

void Interface::areaSlot(double area)
{
    if(area > required_area)
    {
        updateLevelView(++level);
    }

    area = round(area);

    QString label = "AREA: " + QString::number(area) + "%";
    ui->areaLabel->setText(label);

    emit scoreSignal(area);

}

void Interface::scoreSlot(int score)
{
    this->achived_score += score * level * 100;

    QString label = "SCORE: " + QString::number(achived_score);
    ui->scoreLabel->setText(label);
}

void Interface::levelSlot(int level)
{
    std::string s_lives = std::to_string(level);
    QString label = "LEVEL: " + QString::fromStdString(s_lives);
    ui->levelLabel->setText(label);
}

void Interface::pauseSlot(bool pause)
{
    ui->pauseWidget->setVisible(pause);
}




