#include <iostream>
#include <stdio.h>
#include "sever.h"
#include <string>
#include "io.h"
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>

Sever::Sever(QObject *parent):
    QObject(parent)
{

}

Sever::~Sever()
{

}

void Sever::tcpSeverInit()
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
void Sever::tcpListening()
{
    if(!tcpSever->listen(QHostAddress::Any, 6666))
    {
        qDebug()<<tcpSever->errorString();
        tcpSever->close();
        return;
    }
    qDebug("start listening");
}

void Sever::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<tcpClient->errorString();
    tcpClient->close();
    qDebug("Status: connect error! open client and retry");
}
void Sever::acceptConnection()
{
    qDebug("acceptConnection");
    //当有客户来访时将tcpSocket接受tcpServer建立的socket
    tcpClient = tcpSever->nextPendingConnection();
    //????
    //tcpSever->close();
    //端口数据接收成功时，就会发送readyRead()信号
    connect(tcpClient, SIGNAL(readyRead()), this , SLOT(acceptMsgFromClient()));
    // 当有数据发送成功时，就会发送bytesWritten()信号
    //connect(tcpClient, SIGNAL(bytesWritten(qint64)), this, SLOT(updateClientProgress(qint64)));
    // 绑定错误处理
    connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
}
void Sever::acceptMsgFromClient()
{
    emit signal_acceptMsgFromClient();
    //qDebug("emit signal_acceptMsgFromClient();");
}
std::string Sever::readMessageFromTcpClient()
{
    qDebug("readMessageFromTcpClient");
    QByteArray qba = tcpClient->readAll();
    QString data = qba.data();
    std::string data_str = data.toStdString();
    qDebug()<<data;
    return data_str;
//    Json::Reader read;
//    Json::Value root;
//    if(read.parse(data_str.c_str(), root))
//    {
//        std::string name = root["Name"].asString();
//        qDebug()<<QString::fromStdString(name);
//    }
}
void Sever::sendMessage(const std::string str_msg)
{
//    Json::Value root;
//    Json::FastWriter fast;
//    root["DateTime"]=(23);
//    root["Name"]=("Hello");
//    root["Class"]=("13");
//    std::string aa=fast.write(root) ;
//    QString ss = QString::fromStdString(aa);
//    QString str = ss;

    qDebug("tcpsever sendMessage");
    tcpClient->write(str_msg.c_str(),strlen(str_msg.c_str()));
}
QString Sever::getHostIP()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list)
    {
        //我们使用IPv4地址
       if (address.protocol() == QAbstractSocket::IPv4Protocol)
            return address.toString();
    }
    return 0;
}
