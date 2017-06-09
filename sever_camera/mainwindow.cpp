#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_1->setScaledContents(false);
    ui->label_2->setScaledContents(false);
    ui->label_3->setScaledContents(false);
    ui->label_4->setScaledContents(false);
    tcpServer_1 = new QTcpServer(this);
    tcpServer_2 = new QTcpServer(this);
    tcpServer_3 = new QTcpServer(this);
    tcpServer_4 = new QTcpServer(this);

    basize_1=0;
    basize_2=0;
    basize_3=0;
    basize_4=0;
    connect(tcpServer_1, SIGNAL(newConnection()),this, SLOT(acceptConnection_1()));
    connect(tcpServer_2, SIGNAL(newConnection()),this, SLOT(acceptConnection_2()));
    connect(tcpServer_3, SIGNAL(newConnection()),this, SLOT(acceptConnection_3()));
    connect(tcpServer_4, SIGNAL(newConnection()),this, SLOT(acceptConnection_4()));
    qDebug()<<("tcpServer_1 start listening ");
    if(!tcpServer_1->listen(QHostAddress::Any,6661))
    {
        QMessageBox::critical(this,tr("Fortune Server"),tr("Unable to start the server:%l.").arg(tcpServer_1->errorString()));
        close();
        return;
    }
    qDebug()<<("tcpServer_2 start listening ");
    if(!tcpServer_2->listen(QHostAddress::Any,6662))
    {
        QMessageBox::critical(this,tr("Fortune Server"),tr("Unable to start the server:%l.").arg(tcpServer_2->errorString()));
        close();
        return;
    }
    qDebug()<<("tcpServer_3 start listening ");
    if(!tcpServer_3->listen(QHostAddress::Any,6663))
    {
        QMessageBox::critical(this,tr("Fortune Server"),tr("Unable to start the server:%l.").arg(tcpServer_3->errorString()));
        close();
        return;
    }
    qDebug()<<("tcpServer_4 start listening ");
    if(!tcpServer_4->listen(QHostAddress::Any,6664))
    {
        QMessageBox::critical(this,tr("Fortune Server"),tr("Unable to start the server:%l.").arg(tcpServer_4->errorString()));
        close();
        return;
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

/*
1.创建tcpServer ，tcpServer = new QTcpServer(this);使之监听本机的某个端口，tcpServer->listen(QHostAddress("192.168.1.100"),6666)
2,关联信号newConnection和槽函数sendMessage， connect(tcpServer,SIGNAL(newConnection()),this,SLOT(sendMessage()));其中信号newConnection在有客户端的连接请求（即客户端执行tcpSocket->connectToHost）时发射
3.实现槽函数sendMessage，在里面从tcpServer取得已经建立但挂起的QTcpSocket连接
QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
用clientConnection 传输数据给客户
 QByteArray block;
 clientConnection->write(block);
*/

void MainWindow::acceptConnection_1()
{
    qDebug()<<("tcpServer_1 start new accpet");
    tcpServer_1_Connection = tcpServer_1->nextPendingConnection();
    connect(tcpServer_1_Connection,SIGNAL(readyRead()),
            this,SLOT(ReadMyData_1()));//当有数据到来时，读取图像数据
}
void MainWindow::acceptConnection_2()
{
    qDebug()<<("tcpServer_2 start new accpet");
    tcpServer_2_Connection = tcpServer_2->nextPendingConnection();
    connect(tcpServer_2_Connection,SIGNAL(readyRead()),
            this,SLOT(ReadMyData_2()));//当有数据到来时，读取图像数据
}
void MainWindow::acceptConnection_3()
{
    qDebug()<<("tcpServer_3 start new accpet");
    tcpServer_3_Connection = tcpServer_3->nextPendingConnection();
    connect(tcpServer_3_Connection,SIGNAL(readyRead()),
            this,SLOT(ReadMyData_3()));//当有数据到来时，读取图像数据
}
void MainWindow::acceptConnection_4()
{
    qDebug()<<("tcpServer_4 start new accpet");
    tcpServer_4_Connection = tcpServer_4->nextPendingConnection();
    connect(tcpServer_4_Connection,SIGNAL(readyRead()),
            this,SLOT(ReadMyData_4()));//当有数据到来时，读取图像数据
}

void MainWindow::sendFortune()
{

}

void MainWindow::DisplayError(QAbstractSocket::SocketError socketError)
{
    tcpServer_1_Connection->close();
}
void MainWindow::ReadMyData_1()
{
    qDebug()<<("read data 1");
    QByteArray message;//存放从服务器接收到的字符串
    QDataStream in(tcpServer_1_Connection);
    in.setVersion(QDataStream::Qt_5_2);

    //判断接收的数据是否有两字节（文件大小信息）
    //如果有则保存到basize变量中，没有则返回，继续接收数据
    if (tcpServer_1_Connection->bytesAvailable()<(int)sizeof(quint64))
    {
        return;
    }
    in>>basize_1;

    qDebug()<<("accpte byte size");
    qDebug()<<basize_1;

    //如果没有得到全部数据，则返回继续接收数据
    if (tcpServer_1_Connection->bytesAvailable()<basize_1)
    {
        return;
    }

    //in>>message;//将接收到的数据存放到变量中
    //ShowImage_1(message);

    QByteArray block = tcpServer_1_Connection->read(basize_1);
    QImage aa = QImage::fromData(block,"JPEG");
    ui->label_1->setPixmap(QPixmap::fromImage(aa));
    ui->label_1->resize(aa.size());
    update();
}

void MainWindow::ShowImage_1(QByteArray ba)
{
    QString ss=QString::fromLatin1(ba.data(),ba.size());
    QByteArray rc;
    rc=QByteArray::fromBase64(ss.toLatin1());
    QByteArray rdc=qUncompress(rc);
    QImage img;
    img.loadFromData(rdc);
    ui->label_1->setPixmap(QPixmap::fromImage(img));
    ui->label_1->resize(img.size());
    update();
}

void MainWindow::ReadMyData_2()
{
    qDebug()<<("read data 2");
    QByteArray message;//存放从服务器接收到的字符串
    QDataStream in(tcpServer_2_Connection);
    in.setVersion(QDataStream::Qt_5_2);

    //判断接收的数据是否有两字节（文件大小信息）
    //如果有则保存到basize变量中，没有则返回，继续接收数据
    if (tcpServer_2_Connection->bytesAvailable()<(int)sizeof(quint64))
    {
        return;
    }
    else
        in>>basize_2;

    //如果没有得到全部数据，则返回继续接收数据
    if (tcpServer_2_Connection->bytesAvailable()<basize_2)
    {
        return;
    }
    in>>message;//将接收到的数据存放到变量中
    ShowImage_2(message);
}

void MainWindow::ShowImage_2(QByteArray ba)
{
    QString ss=QString::fromLatin1(ba.data(),ba.size());
    QByteArray rc;
    rc=QByteArray::fromBase64(ss.toLatin1());
    QByteArray rdc=qUncompress(rc);
    QImage img;
    img.loadFromData(rdc);
    ui->label_2->setPixmap(QPixmap::fromImage(img));
    ui->label_2->resize(img.size());
    update();
}

void MainWindow::ReadMyData_3()
{
    qDebug()<<("read data 3");
    QByteArray message;//存放从服务器接收到的字符串
    QDataStream in(tcpServer_3_Connection);
    in.setVersion(QDataStream::Qt_5_2);

    //判断接收的数据是否有两字节（文件大小信息）
    //如果有则保存到basize变量中，没有则返回，继续接收数据
    if (tcpServer_3_Connection->bytesAvailable()<(int)sizeof(quint64))
    {
        return;
    }
    else
        in>>basize_3;

    //如果没有得到全部数据，则返回继续接收数据
    if (tcpServer_3_Connection->bytesAvailable()<basize_3)
    {
        return;
    }
    in>>message;//将接收到的数据存放到变量中
    ShowImage_3(message);
}

void MainWindow::ShowImage_3(QByteArray ba)
{
    QString ss=QString::fromLatin1(ba.data(),ba.size());
    QByteArray rc;
    rc=QByteArray::fromBase64(ss.toLatin1());
    QByteArray rdc=qUncompress(rc);
    QImage img;
    img.loadFromData(rdc);
    ui->label_3->setPixmap(QPixmap::fromImage(img));
    ui->label_3->resize(img.size());
    update();
}

void MainWindow::ReadMyData_4()
{
    qDebug()<<("read data 4");
    QByteArray message;//存放从服务器接收到的字符串
    QDataStream in(tcpServer_4_Connection);
    in.setVersion(QDataStream::Qt_5_2);

    //判断接收的数据是否有两字节（文件大小信息）
    //如果有则保存到basize变量中，没有则返回，继续接收数据
    if (tcpServer_4_Connection->bytesAvailable()<(int)sizeof(quint64))
    {
        return;
    }
    else
        in>>basize_4;

    //如果没有得到全部数据，则返回继续接收数据
    if (tcpServer_4_Connection->bytesAvailable()<basize_4)
    {
        return;
    }
    in>>message;//将接收到的数据存放到变量中
    ShowImage_4(message);
}

void MainWindow::ShowImage_4(QByteArray ba)
{
    QString ss=QString::fromLatin1(ba.data(),ba.size());
    QByteArray rc;
    rc=QByteArray::fromBase64(ss.toLatin1());
    QByteArray rdc=qUncompress(rc);
    QImage img;
    img.loadFromData(rdc);
    ui->label_4->setPixmap(QPixmap::fromImage(img));
    ui->label_4->resize(img.size());
    update();
}
