#include "teleoperation.h"
#include "ui_teleoperation.h"
#include <QDesktopWidget>
#include <QPaintDevice>
#include <QPaintEngine>
#include <QPainter>
#include <QFont>
#define TEXT_COLOR  QColor(5,170,255)
Teleoperation::Teleoperation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Teleoperation)
{
    ui->setupUi(this);


    initUi();//初始化界面参数
    initConnect();//初始化信号和槽连接

    //vedio
    ui->image_label->setScaledContents(true);
    tcpServer = new QTcpServer(this);
    if(!tcpServer->listen(QHostAddress::Any,6667))
    {
        QMessageBox::critical(this,tr("Fortune Server"),tr("Unable to start the server:%l.").arg(tcpServer->errorString()));
        close();
        return;
    }
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(sendFortune()));

}

Teleoperation::~Teleoperation()
{
    delete ui;
}
void Teleoperation::initUi()
{
    this->setWindowTitle("远程控制界面");
    // 固定窗口的大小
    this->setFixedSize(this->width(), this->height());
    //设置背景颜色
    this->setAutoFillBackground(true);//这个语句很重要，没有的话，子widget背景色修改不成功
    QPalette myPalette;
    myPalette.setBrush(backgroundRole(),QColor(10,20,35));
    this->setPalette(myPalette);
    ui->textBrowser->setStyleSheet("background-color:rgba(10,20,35,1)");
    ui->textBrowser->setTextColor(TEXT_COLOR);
    ui->textBrowser->setText("前相机");
    //设置按钮风格
    QString button_style="QPushButton{background-color:rgb(20,20,20); color: rgb(230,230,255);   border-radius: 2px;  border: 1px solid rgb(183 , 183 , 183);}"
                                         "QPushButton:hover{background-color:rgb(40,40,40); color: rgb(230,230,255);  border: 1px solid rgb(15 , 150 , 255);}"
                                        "QPushButton:pressed{background-color:rgb(30, 30, 30);    border: 1px solid rgb(15 , 150 , 255); padding-left:1px;  padding-top:1px;}";
    ui->button_backward ->setStyleSheet(button_style);
    ui->button_backward->setFocusPolicy(Qt::NoFocus);
    ui->button_boxSelect ->setStyleSheet(button_style);
    ui->button_boxSelect->setFocusPolicy(Qt::NoFocus);
    ui->button_forward ->setStyleSheet(button_style);
    ui->button_forward->setFocusPolicy(Qt::NoFocus);
    ui->button_horn ->setStyleSheet(button_style);
    ui->button_horn->setFocusPolicy(Qt::NoFocus);
    ui->button_light ->setStyleSheet(button_style);
    ui->button_light->setFocusPolicy(Qt::NoFocus);
    ui->button_start ->setStyleSheet(button_style);
    ui->button_start->setFocusPolicy(Qt::NoFocus);
    ui->button_stop ->setStyleSheet(button_style);
    ui->button_stop->setFocusPolicy(Qt::NoFocus);
    ui->button_taskAsk ->setStyleSheet(button_style);
    ui->button_taskAsk->setFocusPolicy(Qt::NoFocus);
    ui->button_adas ->setStyleSheet(button_style);
    ui->button_adas->setFocusPolicy(Qt::NoFocus);
    ui->button_turnLeft ->setStyleSheet(button_style);
    ui->button_turnLeft->setFocusPolicy(Qt::NoFocus);
    ui->button_turnRight ->setStyleSheet(button_style);
    ui->button_turnRight->setFocusPolicy(Qt::NoFocus);
    ui->button_vehicleInfo ->setStyleSheet(button_style);
    ui->button_vehicleInfo->setFocusPolicy(Qt::NoFocus);
    ui->button_lightClose->setStyleSheet(button_style);
    ui->button_lightClose->setFocusPolicy(Qt::NoFocus);
    ui->button_operationExchange->setStyleSheet(button_style);
    ui->button_operationExchange->setFocusPolicy(Qt::NoFocus);

    ui->button_changeViewport_back->setStyleSheet(button_style);
    ui->button_changeViewport_back->setFocusPolicy(Qt::NoFocus);
    ui->button_changeViewport_front->setStyleSheet(button_style);
    ui->button_changeViewport_front->setFocusPolicy(Qt::NoFocus);
    ui->button_changeViewport_left->setStyleSheet(button_style);
    ui->button_changeViewport_left->setFocusPolicy(Qt::NoFocus);
    ui->button_changeViewport_map->setStyleSheet(button_style);
    ui->button_changeViewport_map->setFocusPolicy(Qt::NoFocus);
    ui->button_changeViewport_right->setStyleSheet(button_style);
    ui->button_changeViewport_right->setFocusPolicy(Qt::NoFocus);
    //设置弹出窗口的位置（在屏幕中央）
    QDesktopWidget *deskdop=QApplication::desktop();
    this->move((deskdop->width()-this->width())/2,(deskdop->height()-this->height())/2);
     //设置每个webview的背景颜色
    ui->webView_main->setStyleSheet("background-color:rgb(40,40,40); padding: 7px ; color:rgb(255,255,255)");
    ui->webView_left->setStyleSheet("background-color:rgb(30,30,30); padding: 7px ; color:rgb(255,255,255)");
    ui->webView_back->setStyleSheet("background-color:rgb(30,30,30); padding: 7px ; color:rgb(255,255,255)");
    ui->webView_map->setStyleSheet("background-color:rgb(30,30,30); padding: 7px ; color:rgb(255,255,255)");
    ui->webView_right->setStyleSheet("background-color:rgb(30,30,30); padding: 7px ; color:rgb(255,255,255)");
    ui->webView_front->setStyleSheet("background-color:rgb(30,30,30); padding: 7px ; color:rgb(255,255,255)");

    //设置每个graphicView为透明
    ui->graphicsView_backAR->setStyleSheet("background-color:rgba(255,255,255,0); border-style:hidden");
    ui->graphicsView_frontAR->setStyleSheet("background-color:rgba(255,255,255,0); border-style:hidden");
    ui->graphicsView_leftAR->setStyleSheet("background-color:rgba(255,255,255,0); border-style:hidden");
    ui->graphicsView_rightAR->setStyleSheet("background-color:rgba(255,255,255,0); border-style:hidden");
    ui->graphicsView_lidar->setStyleSheet("background-color:rgba(255,255,255,0); border-style:hidden");

    image_frontGreen.load(":/images/222.png");
    image_frontRed.load(":/images/666.png");
    image_frontYellow.load(":/images/444.png");
    image_leftGreen.load(":/images/11.png");
    image_leftRed.load(":/images/44.png");
    image_leftYellow.load(":/images/66.png");
    image_rightGreen.load(":/images/6.png");
    image_rightRed.load(":/images/2.png");
    image_rightYellow.load(":/images/4.png");
    image_lidar.load(":/images/lidar.png");
//    image_frontGreen.load(":/images/topGreen.png");
//    image_frontRed.load(":/images/topRed.png");
//    image_frontYellow.load(":/images/topYellow.png");
//    image_leftGreen.load(":/images/leftGreen.png");
//    image_leftRed.load(":/images/leftRed.png");
//    image_leftYellow.load(":/images/leftYellow.png");
//    image_rightGreen.load(":/images/rightGreen.png");
//    image_rightRed.load(":/images/rightRed.png");
//    image_rightYellow.load(":/images/rightYellow.png");
    adasFlag = true;
    mapFlag = false;

    QMatrix matrixLidar;
    matrixLidar.scale(0.25,0.2);
    matrixLidar.rotate(90);
    scene_lidar.addPixmap(image_lidar);
    ui->graphicsView_lidar->setScene(&scene_lidar);
    ui->graphicsView_lidar->setMatrix(matrixLidar);
    ui->graphicsView_lidar->show();

    //加载视频
    QString frontCameraHtmlUrlMain = "file:///home/zlp/qt_test/test1/vediohtml/frontcameramain.html";
    ui->webView_main->load(frontCameraHtmlUrlMain);

    QString leftCameraHtmlUrl = "file:///home/zlp/qt_test/test1/vediohtml/leftcamera1.html";
    ui->webView_left->load(leftCameraHtmlUrl);

    QString rightCmeraHtmlUrl = "file:///home/zlp/qt_test/test1/vediohtml/rightcamera1.html";
    ui->webView_right->load(rightCmeraHtmlUrl);

    QString backCameraHtmlUrl = "file:///home/zlp/qt_test/test1/vediohtml/backcamera1.html";
    ui->webView_back->load(backCameraHtmlUrl);

    QString frontCameraHtmlUrl = "file:///home/zlp/qt_test/test1/vediohtml/frontcamera1.html";
    ui->webView_front->load(frontCameraHtmlUrl);

    QString mapHtmlUrl = "file:///home/zlp/qt_test/test1/htmlapi/baiduapi.html";
    ui->webView_map->load(mapHtmlUrl);

}
void Teleoperation::initConnect()
{

}
//切换视角
void Teleoperation::on_button_changeViewport_left_clicked()
{
    ui->textBrowser->setText("左相机");
    QString leftCameraHtmlUrlMain = "file:///home/zlp/qt_test/test1/vediohtml/leftcameramain.html";
    ui->webView_main->load(leftCameraHtmlUrlMain);
    mapFlag = false;
}
void Teleoperation::on_button_changeViewport_back_clicked()
{
    ui->textBrowser->setText("后相机");
    QString backCameraHtmlUrlMain = "file:///home/zlp/qt_test/test1/vediohtml/backcameramain.html";
    ui->webView_main->load(backCameraHtmlUrlMain);
    mapFlag = false;
}
void Teleoperation::on_button_changeViewport_right_clicked()
{
    ui->textBrowser->setText("右相机");
    QString rightCameraHtmlUrlMain = "file:///home/zlp/qt_test/test1/vediohtml/rightcameramain.html";
    ui->webView_main->load(rightCameraHtmlUrlMain);
    mapFlag = false;
}
void Teleoperation::on_button_changeViewport_front_clicked()
{
    ui->textBrowser->setText("前相机");
    QString frontCameraHtmlUrlMain = "file:///home/zlp/qt_test/test1/vediohtml/frontcameramain.html";
    ui->webView_main->load(frontCameraHtmlUrlMain);
    mapFlag = false;
}
void Teleoperation::on_button_changeViewport_map_clicked()
{
    ui->textBrowser->setText("地图");
    QString mapHtmlUrlMain = "file:///home/zlp/qt_test/test1/htmlapi/baiduapi.html";
    ui->webView_main->load(mapHtmlUrlMain);

    scene_front.clear();
    scene_back.clear();
    scene_left.clear();
    scene_right.clear();
    mapFlag = true;
}
//车辆操作
void Teleoperation::on_button_turnLeft_clicked()
{
    emit signal_vehicleControlTurnLeft();
}
void Teleoperation::on_button_turnRight_clicked()
{
    emit signal_vehicleControlTurnRight();
}
void Teleoperation::on_button_forward_clicked()
{
    emit signal_vehicleControlTurnForward();
}
void Teleoperation::on_button_backward_clicked()
{
    emit signal_vehicleControlTurnBackward();
}
void Teleoperation::on_button_stop_clicked()
{
    emit signal_vehicleControlStop();
}
void Teleoperation::on_button_start_clicked()
{
    emit signal_vehicleControlStart();
}
void Teleoperation::on_button_horn_clicked()
{
    emit signal_vehicleControlHorn();
}
void Teleoperation::on_button_light_clicked()
{
    emit signal_vehicleControlLight();
}
void Teleoperation::on_button_lightClose_clicked()
{
    emit signal_vehicleControlLightClose();
}
void Teleoperation::on_button_operationExchange_clicked()
{
    emit signal_operationExchange();
    ui->textBrowser_sysState ->setTextColor(QColor(255,0,0));
    ui->textBrowser_sysState->setText("已切换为自动驾驶...");
    ui->textBrowser_sysState->setTextColor(QColor(0,0,0));

    ui->button_forward->setDisabled(true);
    ui->button_start->setDisabled(true);
    ui->button_stop->setDisabled(true);
    ui->button_backward->setDisabled(true);
    ui->button_turnLeft->setDisabled(true);
    ui->button_turnRight->setDisabled(true);
}
//为了mainwindow中点击 “操作切换”按钮，对遥操作界面的信息进行更改（显示、按钮使能）
void Teleoperation::setSysState()
{
    ui->textBrowser_sysState ->setTextColor(QColor(255,0,0));
    ui->textBrowser_sysState->setText("已切换为手动驾驶...");
    ui->textBrowser_sysState->setTextColor(QColor(0,0,0));

    ui->button_forward->setDisabled(false);
    ui->button_start->setDisabled(false);
    ui->button_stop->setDisabled(false);
    ui->button_backward->setDisabled(false);
    ui->button_turnLeft->setDisabled(false);
    ui->button_turnRight->setDisabled(false);
}
//物流任务操作
void Teleoperation::on_button_adas_clicked()
{
    if(adasFlag == true && mapFlag == false)
    {
        adasFlag = false;

        QMatrix matrixFront;
//        matrixFront.scale(0.25,0.2);
//        matrixFront.rotate(0.0);
        matrixFront.scale(0.7,0.7);
        matrixFront.rotate(-2.0);
        scene_front.addPixmap(image_frontGreen);
        ui->graphicsView_frontAR->setScene(&scene_front);
        ui->graphicsView_frontAR->setMatrix(matrixFront);
        //ui->graphicsView_frontAR->mapFromGlobal(QPoint(0.2,0.5));
        ui->graphicsView_frontAR->show();

        QMatrix matrixLeft;
//        matrixLeft.scale(0.2,0.17);
//        matrixLeft.rotate(0.0);
        matrixLeft.scale(0.7,0.7);
        matrixLeft.rotate(0.0);
        scene_left.addPixmap(image_leftRed);
        ui->graphicsView_leftAR->setScene(&scene_left);
        ui->graphicsView_leftAR->setMatrix(matrixLeft);
        ui->graphicsView_leftAR->show();

        QMatrix matrixRight;
//        matrixRight.scale(0.2,0.17);
//        matrixRight.rotate(0.0);
        matrixRight.scale(0.7,0.7);
        matrixRight.rotate(0.0);
        scene_right.addPixmap(image_rightYellow);
        ui->graphicsView_rightAR->setScene(&scene_right);
        ui->graphicsView_rightAR->setMatrix(matrixRight);
        ui->graphicsView_rightAR->show();
    }
    else
    {
        adasFlag = true;
        scene_front.clear();
        scene_back.clear();
        scene_left.clear();
        scene_right.clear();
//        ui->graphicsView_backAR->close();
//        ui->graphicsView_frontAR->close();
//        ui->graphicsView_leftAR->close();
//        ui->graphicsView_rightAR->close();
    }
}
void Teleoperation::on_button_taskAsk_clicked()
{
    emit signal_showTaskQueryWidget();
}
void Teleoperation::on_button_boxSelect_clicked()
{
    emit signal_showBoxQueryWidget();
}
void Teleoperation::on_button_vehicleInfo_clicked()
{
    emit signal_showVehicleQueryWidget();
}

//vedio
/*
1.创建tcpServer ，tcpServer = new QTcpServer(this);使之监听本机的某个端口，tcpServer->listen(QHostAddress("192.168.1.100"),6666)
2,关联信号newConnection和槽函数sendMessage， connect(tcpServer,SIGNAL(newConnection()),this,SLOT(sendMessage()));其中信号newConnection在有客户端的连接请求（即客户端执行tcpSocket->connectToHost）时发射
3.实现槽函数sendMessage，在里面从tcpServer取得已经建立但挂起的QTcpSocket连接
QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
用clientConnection 传输数据给客户
 QByteArray block;
 clientConnection->write(block);
*/

void Teleoperation::sendFortune()
{
    basize=0;

    tcpServerConnection = tcpServer->nextPendingConnection();
    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_4_6);
    out<<(quint16) 0;
    out<<tr("OK");//当有连接时则发送一个OK信号给客户端，通知其发送数据

    out.device()->seek(0); //定位到第一个16位， 是写入的数据的大小
    out<<(quint16)(message.size()-sizeof(quint16));


    //connect(tcpServerConnection,SIGNAL(disconnected()),
    //        tcpServerConnection,SLOT(deleteLater()));
    tcpServerConnection->write(message); //写入发送的数据

    connect(tcpServerConnection,SIGNAL(readyRead()),
            this,SLOT(ReadMyData()));//当有数据到来时，读取图像数据
    connect(tcpServerConnection,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(DisplayError(QAbstractSocket::SocketError)));

}
/*
QByteArray Server::GetPicData(QString fromPic)
{
    QImage img(fromPic);
    QByteArray block;
    QBuffer buf(&block);
    img.save(&buf,"JPEG");//按照JPG解码保存数据
    QByteArray cc = qCompress(block,1);
    QByteArray hh;
    hh=cc.toBase64();//base64数据
    return hh;
}*/
void Teleoperation::DisplayError(QAbstractSocket::SocketError socketError)
{
    tcpServerConnection->close();
}
void Teleoperation::ReadMyData()
{
    QByteArray message;//存放从服务器接收到的字符串
    QDataStream in(tcpServerConnection);
    in.setVersion(QDataStream::Qt_4_6);
    if (basize==0)
    {
        //判断接收的数据是否有两字节（文件大小信息）
        //如果有则保存到basize变量中，没有则返回，继续接收数据
        if (tcpServerConnection->bytesAvailable()<(int)sizeof(quint64))
        {
            return;
        }
        in>>basize;
    }
    //如果没有得到全部数据，则返回继续接收数据
    if (tcpServerConnection->bytesAvailable()<basize)
    {
        return;
    }
    in>>message;//将接收到的数据存放到变量中
    ShowImage(message);
}

void Teleoperation::ShowImage(QByteArray ba)
{
    QString ss=QString::fromLatin1(ba.data(),ba.size());
    QByteArray rc;
    rc=QByteArray::fromBase64(ss.toLatin1());
    QByteArray rdc=qUncompress(rc);
    QImage img;
    img.loadFromData(rdc);
    ui->image_label->setPixmap(QPixmap::fromImage(img));
    ui->image_label->resize(img.size());
    update();
}
