#include "logic.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/assets/window_icon.png"));

    Logic logic(3);

    return a.exec();
}
