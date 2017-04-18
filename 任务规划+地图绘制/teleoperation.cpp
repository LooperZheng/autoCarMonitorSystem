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
}

Teleoperation::~Teleoperation()
{
    delete ui;
}
void Teleoperation::initUi()
{
    this->setWindowTitle("远程控制界面");
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
    this->move((deskdop->width()-this->width())/2,      (deskdop->height()-this->height())/2);
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
    image_frontGreen.load(":/images/222.png");
    image_frontRed.load(":/images/666.png");
    image_frontYellow.load(":/images/444.png");
    image_leftGreen.load(":/images/11.png");
    image_leftRed.load(":/images/44.png");
    image_leftYellow.load(":/images/66.png");
    image_rightGreen.load(":/images/6.png");
    image_rightRed.load(":/images/2.png");
    image_rightYellow.load(":/images/4.png");
    adasFlag = true;
    mapFlag = false;

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
//物流任务操作
void Teleoperation::on_button_adas_clicked()
{
    if(adasFlag == true && mapFlag == false)
    {
        adasFlag = false;

        QMatrix matrixFront;
        matrixFront.scale(0.7,0.7);
        matrixFront.rotate(-2.0);
        scene_front.addPixmap(image_frontGreen);
        ui->graphicsView_frontAR->setScene(&scene_front);
        ui->graphicsView_frontAR->setMatrix(matrixFront);
        //ui->graphicsView_frontAR->mapFromGlobal(QPoint(0.2,0.5));
        ui->graphicsView_frontAR->show();

        QMatrix matrixLeft;
        matrixLeft.scale(0.7,0.7);
        matrixLeft.rotate(0.0);
        scene_left.addPixmap(image_leftRed);
        ui->graphicsView_leftAR->setScene(&scene_left);
        ui->graphicsView_leftAR->setMatrix(matrixLeft);
        ui->graphicsView_leftAR->show();

        QMatrix matrixRight;
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

