#include "logic.h"
#include "interface.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/assets/window_icon.png"));

    //Interface interface;
    //interface.show();

    Logic logic(3);

    return a.exec();
}
