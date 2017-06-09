#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "camthread.h"
#include<QtNetwork>
#include<QTcpServer>
#include<QTcpSocket>

#include <highgui.h>  //包含opencv库头文件
#include <cv.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_pushButton_clicked();
    void openCamErr(QString);
    void readFarme_1(QImage);
    void readFarme_2(QImage);
    void readFarme_3(QImage);
    void readFarme_4(QImage);

    void sendFrame_1();
    void sendFrame_2();
    void sendFrame_3();
    void sendFrame_4();
private:
    Camthread *camthread_1;
    Camthread *camthread_2;
    Camthread *camthread_3;
    Camthread *camthread_4;

    QTimer *timer;

    QImage image_1;
    QImage image_2;
    QImage image_3;
    QImage image_4;

    QTcpSocket* tcpSocket_1; //创建tcpsocket
    QTcpSocket* tcpSocket_2; //创建tcpsocket
    QTcpSocket* tcpSocket_3; //创建tcpsocket
    QTcpSocket* tcpSocket_4; //创建tcpsocket
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
