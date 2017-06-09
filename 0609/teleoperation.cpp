#include "teleoperation.h"
#include "ui_teleoperation.h"
#include <QDesktopWidget>
#include <QPaintDevice>
#include <QPaintEngine>
#include <QPainter>
#include <QFont>
#include <iostream>
#include <unistd.h>
#include <QWebFrame>
#include <QMessageBox>

using namespace std;
#define TEXT_COLOR  QColor(5,170,255)
#define PEN_COLOR QColor(250,250,250)
#define BRUSH_COLOR QColor(200,35,5)
Teleoperation::Teleoperation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Teleoperation)
{
    ui->setupUi(this);
    myRobot=new Robot(this);

    initUi();//初始化界面参数
    initConnect();//初始化信号和槽连接

    enable = false;
    mousePressNum = 0;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    lastPoint.setX(0);
    lastPoint.setY(0);
    endPoint.setX(0);
    endPoint.setY(0);// 初始化位置，这里不初始化也行，不过初始化是个好习惯.
    path.addEllipse(440,650,20,20);     // 向path 中添加图形
    painter.setPen(PEN_COLOR);
    painter.setBrush(BRUSH_COLOR);
    painter.drawPath(path);   // 绘制前面创建的path
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
    ui->button_changeViewport_right->setStyleSheet(button_style);
    ui->button_changeViewport_right->setFocusPolicy(Qt::NoFocus);

    ui->button_playVideo->setStyleSheet(button_style);
    ui->button_playVideo->setFocusPolicy(Qt::NoFocus);
    ui->button_stopVideo->setStyleSheet(button_style);
    ui->button_stopVideo->setFocusPolicy(Qt::NoFocus);
    //设置弹出窗口的位置（在屏幕中央）
    QDesktopWidget *deskdop=QApplication::desktop();
    this->move((deskdop->width()-this->width())/2,(deskdop->height()-this->height())/2);
     //设置每个webview的背景颜色

    ui->webView_map->setStyleSheet("background-color:rgb(30,30,30); padding: 7px ; color:rgb(255,255,255)");


    //设置每个graphicView为透明
    //ui->graphicsView_backAR->setStyleSheet("background:transparent");
    //ui->graphicsView_backAR->setStyleSheet(" border:0px");
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

    //hkws
    frame_left = ui->frame_left;
    frame_right = ui->frame_right;
    frame_front = ui->frame_front;
    frame_main = ui->frame_main;

    frames[0] = new CFramePlayWnd(ui->frame_left);
    frames[0]->setParent(ui->frame_left);
    frames[0]->setGeometry(0,0,211, 141);

    frames[1] = new CFramePlayWnd(ui->frame_right);
    frames[1]->setParent(ui->frame_right);
    frames[1]->setGeometry(0,0,211, 141);

    frames[2] = new CFramePlayWnd(ui->frame_front);
    frames[2]->setParent(ui->frame_front);
    frames[2]->setGeometry(0,0,211, 141);

    frames[3] = new CFramePlayWnd(ui->frame_main);
    frames[3]->setParent(ui->frame_main);
    frames[3]->setGeometry(0,0,771, 531);

    ui->webView_map->settings()->setAttribute(QWebSettings::JavascriptEnabled,true);//使能javascript
    ui->webView_map->settings()->setAttribute(QWebSettings::PluginsEnabled,true);//Qt窗口部件嵌入到网页
    addJavaScriptObject();
    QString mapHtmlUrl = "file:///home/zlp/qt_test/test1/htmlapi/baiduapi_tele.html";
    ui->webView_map->load(mapHtmlUrl);

    timer = new QTimer();
    timer_refreshMap = new QTimer();
}
void Teleoperation::initConnect()
{
    connect(ui->webView_map->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),this, SLOT(addJavaScriptObject()));//地图刷新调取
    connect(timer,SIGNAL(timeout()),this,SLOT(slot_sendVehicleCmd()));
    connect(timer_refreshMap,SIGNAL(timeout()),this,SLOT(refreshMap()));
}
void Teleoperation::updateRobotInfo(Robot *robot)
{
    myRobot->pathAll = robot->pathAll;
    myRobot->vehicleCoor = robot->vehicleCoor;
    myRobot->taskPointCluster = robot->taskPointCluster;
    myRobot->pathSeq = robot->pathSeq;
    myRobot->pathPointID2Coordinate = robot->pathPointID2Coordinate;
    myRobot->pathPointID2CoordinateAll = robot->pathPointID2CoordinateAll;
    myRobot->currentTaskID = robot->currentTaskID;
}
void Teleoperation::refreshMap()
{
  this->ui->webView_map->page()->mainFrame()->evaluateJavaScript("refreshDataVehicle();");
}
void Teleoperation::addJavaScriptObject()
{
    this->ui->webView_map->page()->mainFrame()->addToJavaScriptWindowObject(QString("myRobot"), this->myRobot);
}
//hkws
int Teleoperation::init_nvr()
{
    NET_DVR_Init();
//    Demo_SDK_Version();
    NET_DVR_SetLogToFile(3, "./sdkLog");
    char cUserChoose = 'r';

    //Login device
    NET_DVR_DEVICEINFO_V30 struDeviceInfo = {0};
    //LONG lUserID = NET_DVR_Login_V30("172.9.204.5", 8000, "admin", "12345", &struDeviceInfo);
    lUserID = NET_DVR_Login_V30("192.168.8.177", 8000, "admin", "1234567.", &struDeviceInfo);
    if (lUserID < 0)
    {
        qDebug()  << "pyd---Login error, %d\n" << NET_DVR_GetLastError();
        qDebug()  << "Press any key to quit...\n";
        cin>>cUserChoose;

        NET_DVR_Cleanup();
        return HPR_ERROR;
    }
}
int Teleoperation::StopNVR()
{
    NET_DVR_Logout_V30(lUserID);
    NET_DVR_Cleanup();
}
void CALLBACK g_RealDataCallBack_V30(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,void* dwUser)
{
    qDebug() <<"pyd---(private_v30)Get data,the size is %d,%d.\n", time(NULL), dwBufSize;
}
int Teleoperation::StartGetStream(LONG lUserID, int c_id, int f_id)
{
    if(c_id < 1 || c_id > 4)
        return -1;
    if(f_id < 0 || f_id > 3)
        return -1;

    //Set callback function of getting stream.
    long lRealPlayHandle;
    NET_DVR_CLIENTINFO ClientInfo = {0};

    ClientInfo.hPlayWnd     = frames[f_id]->GetPlayWndId();

    ClientInfo.lChannel     = c_id;  //channel NO.
    //ClientInfo.lLinkMode    = 0x40000000; //Record when breaking network.
    ClientInfo.lLinkMode    = 0;
    ClientInfo.sMultiCastIP = NULL;

    lRealPlayHandle = NET_DVR_RealPlay_V30(lUserID, &ClientInfo, g_RealDataCallBack_V30, NULL, 0);
    //lRealPlayHandle = NET_DVR_RealPlay_V30(lUserID, &ClientInfo, NULL, NULL, 0);
    if (lRealPlayHandle < 0)
    {
        qDebug() <<"pyd1---NET_DVR_RealPlay_V30 error\n";
        return HPR_ERROR;
    }
}
void Teleoperation::Demo_SDK_Version()
{
    unsigned int uiVersion = NET_DVR_GetSDKBuildVersion();

    qDebug()  << "HCNetSDK V%d.%d.%d.%d\n" << \
        (0xff000000 & uiVersion)/0x1000000 << \
        (0x00ff0000 & uiVersion)/0x10000 << \
        (0x0000ff00 & uiVersion)/0x100 << \
        (0x000000ff & uiVersion);
}
void Teleoperation::on_button_playVideo_clicked()
{
    init_nvr();

    StartGetStream(lUserID, 2, 0);
    StartGetStream(lUserID, 3, 1);
    StartGetStream(lUserID, 1, 2);
    StartGetStream(lUserID, 1, 3);
}
void Teleoperation::on_button_stopVideo_clicked()
{
    StopNVR();
}
//切换视角
void Teleoperation::on_button_changeViewport_left_clicked()
{
    ui->textBrowser->setText("左相机");
    StopNVR();
    init_nvr();

    StartGetStream(lUserID, 2, 0);
    StartGetStream(lUserID, 3, 1);
    StartGetStream(lUserID, 1, 2);
    StartGetStream(lUserID, 2, 3);

    mapFlag = false;
}
void Teleoperation::on_button_changeViewport_back_clicked()
{
    ui->textBrowser->setText("后相机");

    mapFlag = false;
}
void Teleoperation::on_button_changeViewport_right_clicked()
{
    ui->textBrowser->setText("右相机");
    StopNVR();
    init_nvr();

    StartGetStream(lUserID, 2, 0);
    StartGetStream(lUserID, 3, 1);
    StartGetStream(lUserID, 1, 2);
    StartGetStream(lUserID, 3, 3);
    mapFlag = false;
}
void Teleoperation::on_button_changeViewport_front_clicked()
{
    ui->textBrowser->setText("前相机");
    StopNVR();
    init_nvr();

    StartGetStream(lUserID, 2, 0);
    StartGetStream(lUserID, 3, 1);
    StartGetStream(lUserID, 1, 2);
    StartGetStream(lUserID, 1, 3);
    mapFlag = false;
}

//车辆操作

void Teleoperation::on_button_turnLeft_clicked()
{
    QMessageBox::StandardButton rb=QMessageBox::information(NULL, "Title", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(rb == QMessageBox::Yes)
        qDebug()<<"yes";
    else
        qDebug()<<"no";
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

    enableOperation = false;

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
    //由mainwindow切换到遥操作界面，更新一下遥操作界面的所有地图信息
    this->ui->webView_map->page()->mainFrame()->evaluateJavaScript("refreshDataAll();");
    timer_refreshMap->start(1000);

    ui->textBrowser_sysState ->setTextColor(QColor(255,0,0));
    ui->textBrowser_sysState->setText("已切换为手动驾驶...");
    ui->textBrowser_sysState->setTextColor(QColor(0,0,0));

    enableOperation = true;

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

//vehicle control
void Teleoperation::slot_sendVehicleCmd()
{
    QPointF point = path.currentPosition();
    float deta_x = point.x() - 460;
    float deta_y = point.y() - 660;
    double dis = sqrt(deta_x*deta_x + deta_y*deta_y);
    double vel;
    dis<60? vel=dis : vel=60;
    double alpha;
    alpha = asin( (660-point.y()) / dis );
    if ( deta_x < 0 && deta_y <0)
        alpha = 3.141593 - alpha;
    if(deta_x <0 && deta_y >0)
        alpha = -3.141593 - alpha;
    emit signal_vehicleControlCmd(vel, alpha);
    qDebug()<<vel;
    qDebug()<<alpha;
}

bool Teleoperation::isInCircle(QPointF centerPoint, float r, QPointF mouseCurPoint)
{
    float deta_x = centerPoint.x() - mouseCurPoint.x();
    float deta_y = centerPoint.y() - mouseCurPoint.y();
    double dis = sqrt(deta_x*deta_x + deta_y*deta_y);
    if(dis <= r)
        return true;
    else
        return false;
}
void Teleoperation::mousePressEvent(QMouseEvent *event)
{
    mouseReleaseNum = 0;
    mouseMove = true;
    if(event->button() == Qt::LeftButton && enableOperation == true)
    {
        if (isInCircle(QPoint(event->x(),event->y()),20,QPoint(450,650)))
        {
            enable = true;

            timer->start(100);
        }
        else
            enable = false;
        lastPoint = event->pos();
    }

}
void Teleoperation::mouseReleaseEvent(QMouseEvent *event)
{
    mousePressNum = 0;
    mouseReleaseNum++;
    mouseMove = false;
    if(event->button() == Qt::LeftButton && enable == true && enableOperation == true)
    {
        lastPoint = path.currentPosition();
        endPoint.setX(460);
        endPoint.setY(660);
        update();

        timer->stop();
        emit signal_vehicleControlCmd(0, 0);
    }
}
void Teleoperation::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton && enableOperation == true)
    {
        endPoint = event->pos();
        update();//拖动时有痕迹
    }
}
void Teleoperation::paintEvent(QPaintEvent *event)
{
    if(enableOperation == true)
    {
        //mouse release
        if(mouseReleaseNum == 1 && enable == true)
        {
            QPainter painter(this);
            painter.setPen(PEN_COLOR);
            painter.setBrush(BRUSH_COLOR);
            path.translate(endPoint.x()-lastPoint.x(),endPoint.y()-lastPoint.y());//移动(可理解为向量移动)
            //        qDebug()<<"last "<<lastPoint;
            //        qDebug()<<"end "<<endPoint;
            //        qDebug()<<"cur "<<path.currentPosition();//移动后的位置
            painter.drawPath(path);//画出移动后的图形
            lastPoint = endPoint;
        }
        //mouse move
        if(mouseMove == true  && enable == true && isInCircle(QPoint(460,660),60,QPoint(path.currentPosition().x(),path.currentPosition().y())))
        {
            QPainter painter(this);
            painter.setPen(PEN_COLOR);
            painter.setBrush(BRUSH_COLOR);
            path.translate(endPoint.x()-lastPoint.x(),endPoint.y()-lastPoint.y());//移动(可理解为向量移动)
            //        qDebug()<<"last "<<lastPoint;
            //        qDebug()<<"end "<<endPoint;
            //        qDebug()<<"cur "<<path.currentPosition();//移动后的位置
            painter.drawPath(path);//画出移动后的图形
            lastPoint = endPoint;
        }
        else
        {
            QPainter painter(this);
            painter.setPen(PEN_COLOR);
            painter.setBrush(BRUSH_COLOR);
            path.translate(0,0);//移动(可理解为向量移动)
            painter.drawPath(path);//画出移动后的图形
        }

        //mouse press
        if(mousePressNum<4  && enable == true)
        {
            mousePressNum ++;
            QPainter painter(this);
            painter.setPen(PEN_COLOR);
            painter.setBrush(BRUSH_COLOR);
            path.translate(endPoint.x()-lastPoint.x(),endPoint.y()-lastPoint.y());//移动(可理解为向量移动)
            //        qDebug()<<"last "<<lastPoint;
            //        qDebug()<<"end "<<endPoint;
            //        qDebug()<<"cur "<<path.currentPosition();//移动后的位置
            painter.drawPath(path);//画出移动后的图形
            lastPoint = endPoint;
        }
    }
    //轮廓
    QPainter painter(this);
    // 反走样
    painter.setRenderHint(QPainter::Antialiasing, true);
    // 设置画笔颜色、宽度
    painter.setPen(QPen(QColor(0, 160, 230), 2));
    // 绘制椭圆
    painter.drawEllipse(QPointF(450, 660), 60, 60);

    QPainter painter1(this);
    painter1.setRenderHint(QPainter::Antialiasing, true);
    painter1.setPen(QPen(QColor(0, 160, 230), 1));
    painter1.drawLine(QPointF(390,660), QPointF(510,660));

    QPainter painter2(this);
    painter2.setRenderHint(QPainter::Antialiasing, true);
    painter2.setPen(QPen(QColor(0, 160, 230), 1));
    painter2.drawLine(QPointF(450,600), QPointF(450,720));

}
