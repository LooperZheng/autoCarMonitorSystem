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
void MainWindow::tcpSeverInit()
{
    qDebug("start tcp server ini");
    tcpSever = new QTcpServer(this);
    tcpClient = new QTcpSocket(this);
    hostIP = getHostIP();
    if(hostIP == 0)
    {
        qDebug("get hostIP fail");
    }
    else
        qDebug()<<hostIP;
    //newConnection()用于当有客户端访问时发出信号，acceptConnection()信号处理函数
    connect(tcpSever, SIGNAL(newConnection()),this, SLOT(acceptConnection()));

}
void MainWindow::tcpListening()
{
    if(!tcpSever->listen(QHostAddress::Any, 6665))
    {
        qDebug()<<tcpSever->errorString();
        tcpSever->close();
        return;
    }
    qDebug("start listening");
}
void MainWindow::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<tcpClient->errorString();
    tcpClient->close();
    qDebug("Status: connect error! open client and retry");
}
void MainWindow::acceptConnection()
{
    qDebug("acceptConnection");
    //当有客户来访时将tcpSocket接受tcpServer建立的socket
    tcpClient = tcpSever->nextPendingConnection();
    //????
    //tcpSever->close();
    //端口数据接收成功时，就会发送readyRead()信号
    connect(tcpClient, SIGNAL(readyRead()), this , SLOT(readMessageFromTcpClient()));
    // 当有数据发送成功时，就会发送bytesWritten()信号
    //connect(tcpClient, SIGNAL(bytesWritten(qint64)), this, SLOT(updateClientProgress(qint64)));
    // 绑定错误处理
    connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
}
void MainWindow::readMessageFromTcpClient()
{
    qDebug("readMessageFromTcpClient");
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
    QString str = "test from sever";
    tcpClient->write(str.toStdString().c_str(),strlen(str.toStdString().c_str()));
}

QString MainWindow::getHostIP()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list)
    {
        //我们使用IPv4地址
       if(address.protocol() == QAbstractSocket::IPv4Protocol)
            return address.toString();
    }
    return 0;
}
