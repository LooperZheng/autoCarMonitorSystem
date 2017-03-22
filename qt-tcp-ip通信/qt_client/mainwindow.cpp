#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtNetwork"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::tcpClientInit()
{
    qDebug("start to tcp client  inet 地址:192.168.1.109 init");
    tcpClient = new QTcpSocket(this);

    tcpClient->connectToHost(QHostAddress("127.0.0.1"),6665);
    connect(tcpClient,SIGNAL(readyRead()),this, SLOT(readMessageFromTcpSever()));
}
void MainWindow::readMessageFromTcpSever()
{
    QByteArray qba = tcpClient->readAll();
    ui->textBrowser->setText(qba);
}
void MainWindow::on_pushButton_clicked()
{
    sendMessage();
}
void MainWindow::sendMessage()
{
    qDebug("sendMessage");
    QString str = "test form client";
    tcpClient->write(str.toStdString().c_str(),strlen(str.toStdString().c_str()));
}
