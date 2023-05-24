#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QStackedWidget>

namespace Ui {
class Interface;
}

class Interface : public QMainWindow //QWidget
{
    Q_OBJECT

public:
    Interface(QGraphicsScene *scene, QWidget *parent = nullptr);
    ~Interface();

private slots:
    void on_startButton_clicked();
    void on_leadButton_clicked();
    void on_backButton_clicked();
    void on_quitButton_clicked();

private:
    Ui::Interface *ui;
    QGraphicsScene *scene;

};

#endif // INTERFACE_H
