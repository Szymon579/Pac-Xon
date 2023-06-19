#include "interface.h"

#include <QApplication>
#include <QGraphicsScene>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/assets/window_icon.png"));

    Interface interface;
    interface.show();

    return app.exec();
}
