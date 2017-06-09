#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include<QTcpSocket>
#include<QTcpServer>
#include<QString>
#include<QtNetwork>
#include<QMessageBox>
#include<QImage>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTcpServer *tcpServer_1;
    QTcpServer *tcpServer_2;
    QTcpServer *tcpServer_3;
    QTcpServer *tcpServer_4;

    QTcpSocket *tcpServer_1_Connection;
    QTcpSocket *tcpServer_2_Connection;
    QTcpSocket *tcpServer_3_Connection;
    QTcpSocket *tcpServer_4_Connection;
    QStringList *fortunes;
    QImage *img;
    quint64 basize_1;
    quint64 basize_2;
    quint64 basize_3;
    quint64 basize_4;

public slots:
    void sendFortune();

    void acceptConnection_1();
    void acceptConnection_2();
    void acceptConnection_3();
    void acceptConnection_4();
   // QByteArray GetPicData(QString fromPic);
    void DisplayError(QAbstractSocket::SocketError socketError);
    void ReadMyData_1();
    void ShowImage_1(QByteArray ba);

    void ReadMyData_2();
    void ShowImage_2(QByteArray ba);

    void ReadMyData_3();
    void ShowImage_3(QByteArray ba);

    void ReadMyData_4();
    void ShowImage_4(QByteArray ba);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
