#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 以下部分解决中文乱码
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    MainWindow w;
    w.show();

    return a.exec();
}
