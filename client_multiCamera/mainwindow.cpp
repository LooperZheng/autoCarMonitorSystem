#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include "QMessageBox"
#include "QFileDialog"
#include <qdebug.h>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer=new QTimer();
    camthread_1=new Camthread();
    camthread_2=new Camthread();
    camthread_3=new Camthread();
    camthread_4=new Camthread();

    connect(camthread_1,SIGNAL(sig_GetOneFrame(QImage)),this,SLOT(readFarme_1(QImage)));
    connect(camthread_2,SIGNAL(sig_GetOneFrame(QImage)),this,SLOT(readFarme_2(QImage)));
    connect(camthread_3,SIGNAL(sig_GetOneFrame(QImage)),this,SLOT(readFarme_3(QImage)));
    connect(camthread_4,SIGNAL(sig_GetOneFrame(QImage)),this,SLOT(readFarme_4(QImage)));

    tcpSocket_1=new QTcpSocket();
    tcpSocket_2=new QTcpSocket();
    tcpSocket_3=new QTcpSocket();
    tcpSocket_4=new QTcpSocket();

    tcpSocket_1->connectToHost(QHostAddress("202.120.37.100"),6661);
    tcpSocket_2->connectToHost(QHostAddress("202.120.37.100"),6662);
    tcpSocket_3->connectToHost(QHostAddress("202.120.37.100"),6663);
    tcpSocket_4->connectToHost(QHostAddress("202.120.37.100"),6664);

//    tcpSocket_1->connectToHost(QHostAddress::LocalHost,6661);
//    tcpSocket_2->connectToHost(QHostAddress::LocalHost,6662);
//    tcpSocket_3->connectToHost(QHostAddress::LocalHost,6663);
//    tcpSocket_4->connectToHost(QHostAddress::LocalHost,6664);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{
    //connect(camthread_1,SIGNAL(sig_err(QString)),this,SLOT( openCamErr(QString)));

    camthread_1->startPlay(4);
    camthread_2->startPlay(3);
    camthread_3->startPlay(2);
    camthread_4->startPlay(1);
}
void MainWindow::openCamErr(QString msg)
{
    QString errMsg;
    errMsg.append("can not open camera ");
    errMsg.append(msg);
    qDebug()<<(errMsg);
}
void MainWindow::readFarme_1(QImage image1)
{
    image_1 = image1;
    // 将图片显示到label上
    ui->label_1->setPixmap(QPixmap::fromImage(image_1));

    sendFrame_1();
}
void MainWindow::sendFrame_1()
{
    //send
    tcpSocket_1->abort();//取消已有链接
    //连接到某个ip的某个端口，
    tcpSocket_1->connectToHost(QHostAddress("202.120.37.100"),6661);
    //tcpSocket_1->connectToHost(QHostAddress::LocalHost,6661);

    QByteArray ba; //用于暂存要发送的数据
    QDataStream out(&ba,QIODevice::WriteOnly); //使用数据流写入数据
    out.setVersion(QDataStream::Qt_5_2);
    //设置数据流的版本，客户端和服务器端使用的版本要相同
    QByteArray byte;
    QBuffer buf(&byte);
    image_1.save(&buf,"JPEG");

    QByteArray ss=qCompress(byte,1);
    QByteArray vv=ss.toBase64();
    out<<(quint64)0;
    out<<vv;
    out.device()->seek(0);
    out<<(quint64)(ba.size()-sizeof(quint64));

    //发送数据
    tcpSocket_1->write(ba);

    qDebug()<<("data size of qint64");
    qDebug()<<(sizeof(quint64));

    qDebug()<<("data size before compress");
    qDebug()<<(quint64)(byte.size());

    qDebug()<<("data size after compress");
    qDebug()<<(quint64)(ss.size());

    qDebug()<<("data size after compress base64");
    qDebug()<<(quint64)(vv.size());
}

void MainWindow::readFarme_2(QImage image2)
{
    image_2 = image2;
    // 将图片显示到label上
    ui->label_2->setPixmap(QPixmap::fromImage(image_2));

    sendFrame_2();
}
void MainWindow::sendFrame_2()
{
    //send
    tcpSocket_2->abort();//取消已有链接
    //连接到某个ip的某个端口，
    tcpSocket_2->connectToHost(QHostAddress("202.120.37.100"),6662);
    //tcpSocket_2->connectToHost(QHostAddress::LocalHost,6662);

    QByteArray ba; //用于暂存要发送的数据
    QDataStream out(&ba,QIODevice::WriteOnly); //使用数据流写入数据
    out.setVersion(QDataStream::Qt_5_2);
    //设置数据流的版本，客户端和服务器端使用的版//    qDebug()<<("data size after compress");
    //    qDebug()<<(quint64)(ss.size());

    //    qDebug()<<("data size after compress base64");
    //    qDebug()<<(quint64)(vv.size());本要相同
    QByteArray byte;
    QBuffer buf(&byte);
    image_2.save(&buf,"JPEG");
    QByteArray ss=qCompress(byte,1);
    QByteArray vv=ss.toBase64();
    out<<(quint64)0;
    out<<vv;
    out.device()->seek(0);
    out<<(quint64)(ba.size()-sizeof(quint64));
    //发送数据
    tcpSocket_2->write(ba);
}
void MainWindow::readFarme_3(QImage image3)
{
    image_3 = image3;
    // 将图片显示到label上
    ui->label_3->setPixmap(QPixmap::fromImage(image_3));

    sendFrame_3();
}
void MainWindow::sendFrame_3()
{
    //send
    tcpSocket_3->abort();//取消已有链接
    //连接到某个ip的某个端口，
    tcpSocket_3->connectToHost(QHostAddress("202.120.37.100"),6663);
    //tcpSocket_3->connectToHost(QHostAddress::LocalHost,6663);

    QByteArray ba; //用于暂存要发送的数据
    QDataStream out(&ba,QIODevice::WriteOnly); //使用数据流写入数据
    out.setVersion(QDataStream::Qt_5_2);
    //设置数据流的版本，客户端和服务器端使用的版本要相同
    QByteArray byte;
    QBuffer buf(&byte);
    image_3.save(&buf,"JPEG");
    QByteArray ss=qCompress(byte,1);
    QByteArray vv=ss.toBase64();
    out<<(quint64)0;
    out<<vv;
    out.device()->seek(0);
    out<<(quint64)(ba.size()-sizeof(quint64));
    //发送数据
    tcpSocket_3->write(ba);
}
void MainWindow::readFarme_4(QImage image4)
{
    image_4 = image4;
    // 将图片显示到label上
    ui->label_4->setPixmap(QPixmap::fromImage(image_4));

    sendFrame_4();
}
void MainWindow::sendFrame_4()
{
    //send
    tcpSocket_4->abort();//取消已有链接
    //连接到某个ip的某个端口，
    tcpSocket_4->connectToHost(QHostAddress("202.120.37.100"),6664);
    //tcpSocket_4->connectToHost(QHostAddress::LocalHost,6664);

    QByteArray ba; //用于暂存要发送的数据
    QDataStream out(&ba,QIODevice::WriteOnly); //使用数据流写入数据
    out.setVersion(QDataStream::Qt_5_2);
    //设置数据流的版本，客户端和服务器端使用的版本要相同
    QByteArray byte;
    QBuffer buf(&byte);
    image_4.save(&buf,"JPEG");
    QByteArray ss=qCompress(byte,1);
    QByteArray vv=ss.toBase64();
    out<<(quint64)0;
    out<<vv;
    out.device()->seek(0);
    out<<(quint64)(ba.size()-sizeof(quint64));
    //发送数据
    tcpSocket_4->write(ba);
}
