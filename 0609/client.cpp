#include <iostream>
#include <stdio.h>
#include "client.h"
#include <string>
#include "io.h"

Client::Client(QObject *parent):
    QObject(parent)
{

}

Client::~Client()
{

}

void Client::tcpClientInit()
{
    qDebug("start to tcp client init");
    tcpClient = new QTcpSocket(this);
    // sever IP
    tcpClient->connectToHost(QHostAddress("10.181.21.247"),6665);
    connect(tcpClient,SIGNAL(readyRead()),this, SLOT(readMessageFromTcpSever()));
}
void Client::readMessageFromTcpSever()
{
    QByteArray qba = tcpClient->readAll();
    QString data = qba.data();
    if(data.mid(0,1)!="t")
    {
        QString lo = data.mid(0,10);
        QString la = data.mid(10,9);
        longitude = lo.toDouble();
        latitude = la.toDouble();
        printf("%lf %lf\n", longitude, latitude);
        //test
        QString taskID = data.mid(19,data.size()-19);
        currentTaskID = taskID.toInt();
        printf("taskID %d\n", currentTaskID);
    }
    else
    {
        QString taskID = data.mid(1,data.size()-1);
        currentTaskID = taskID.toInt();
        printf("taskID %d\n", currentTaskID);
    }
}
void Client::sendMessage(QString str)
{
    qDebug("sendMessage");
    //QString str = "121.123456;31.123456";
    tcpClient->write(str.toStdString().c_str(),strlen(str.toStdString().c_str()));
}
