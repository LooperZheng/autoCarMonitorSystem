#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "QtNetwork"
#include<QtNetwork/QTcpSocket>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTcpSocket *tcpClient;

    void tcpClientInit();
    void sendMessage();
public slots:
    void readMessageFromTcpSever();

    void on_pushButton_clicked();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
