#ifndef SEVER_H
#define SEVER_H

#include <iostream>
#include <QObject>
#include "QtNetwork"
#include<QtNetwork/QTcpSocket>
#include<QtNetwork/QTcpServer>
#include <string>

class Sever: public QObject
{
     Q_OBJECT
public:
     explicit Sever(QObject *parent=0);
     ~Sever();

public:
    QTcpServer *tcpSever;
    QTcpSocket *tcpClient;
    QString hostIP;

    double longitude;
    double latitude;

    void tcpSeverInit();
    void tcpListening();
    void sendMessage(const std::string);

    QString getHostIP();
signals:
    void signal_acceptMsgFromClient();
public  slots:
    void acceptConnection();
    void acceptMsgFromClient();
    std::string readMessageFromTcpClient();
    void displayError(QAbstractSocket::SocketError); //显示错误
};
#endif // SEVER
