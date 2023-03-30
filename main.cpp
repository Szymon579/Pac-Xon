#include "maingame.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 1000, 600);

    QGraphicsView view(&scene);
    view.setWindowTitle("Pac-Xon");
    view.setBackgroundBrush(Qt::blue);
    view.show();


    MainGame window;
    //window.show();
    return app.exec();
}
