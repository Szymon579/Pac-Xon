#include "interface.h"

#include <QApplication>
#include <QGraphicsScene>
//#include <fstream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/assets/window_icon.png"));

    Interface interface;
    interface.show();

//    std::fstream outfile;
//    outfile.open("leaderboard.txt", std::ios::out);
//    if(outfile.is_open())
//    {
//        outfile << "test";
//    }
//    outfile.close();

    return a.exec();
}
