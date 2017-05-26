#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <QObject>
#include "QtNetwork"
#include<QtNetwork/QTcpSocket>
#include <string>

class Client: public QObject
{
     Q_OBJECT
public:
     explicit Client(QObject *parent=0);
     ~Client();

public:
    QTcpSocket *tcpClient;
    double longitude;
    double latitude;
    int currentTaskID;
    void tcpClientInit();

public slots:
    void readMessageFromTcpSever();
    void sendMessage(QString data);

};
#endif // CLIENT_H
