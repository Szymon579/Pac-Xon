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






