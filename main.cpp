#include "logic.h"
#include "interface.h"

#include <QApplication>
#include <QGraphicsScene>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/assets/window_icon.png"));

    Logic logic(3);

    Interface interface(logic.scene);
    interface.show();

    return a.exec();
}
