#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.tcpSeverInit();
    w.tcpListening();

    return a.exec();
}
