#include "gamebuilder.h"
#include "interface.h"

#include <QApplication>
#include <QGraphicsScene>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/assets/window_icon.png"));

    Interface interface;
    interface.show();

//    Logic logic(3);
//    Interface interface(logic.scene);
//    interface.show();

//    QObject::connect(&logic, &Logic::livesSignal, &interface, &Interface::lives);
//    QObject::connect(&logic, &Logic::scoreSignal, &interface, &Interface::score);

    return a.exec();
}
