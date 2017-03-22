#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QtNetwork"
#include<QtNetwork/QTcpSocket>
#include<QtNetwork/QTcpServer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QTcpServer *tcpSever;
    QTcpSocket *tcpClient;
    QString hostIP;
    void tcpSeverInit();
    void tcpListening();
    void sendMessage();

    QString getHostIP();
public  slots:
    void acceptConnection();
    void readMessageFromTcpClient();
    void displayError(QAbstractSocket::SocketError); //显示错误

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
