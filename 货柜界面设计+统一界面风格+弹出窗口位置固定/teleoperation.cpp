#include "teleoperation.h"
#include "ui_teleoperation.h"
#include <QDesktopWidget>
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
    ui->button_taskSelect ->setStyleSheet(button_style);
    ui->button_taskSelect->setFocusPolicy(Qt::NoFocus);
    ui->button_turnLeft ->setStyleSheet(button_style);
    ui->button_turnLeft->setFocusPolicy(Qt::NoFocus);
    ui->button_turnRight ->setStyleSheet(button_style);
    ui->button_turnRight->setFocusPolicy(Qt::NoFocus);
    ui->button_vehicleInfo ->setStyleSheet(button_style);
    ui->button_vehicleInfo->setFocusPolicy(Qt::NoFocus);
    //设置弹出窗口的位置（在屏幕中央）
    QDesktopWidget *deskdop=QApplication::desktop();
    this->move((deskdop->width()-this->width())/2,      (deskdop->height()-this->height())/2);
}
void Teleoperation::initConnect()
{

}
//车辆操作
void Teleoperation::on_button_turnLeft_clicked()
{

}
void Teleoperation::on_button_turnRight_clicked()
{

}
void Teleoperation::on_button_forward_clicked()
{

}
void Teleoperation::on_button_backward_clicked()
{

}
void Teleoperation::on_button_stop_clicked()
{

}
void Teleoperation::on_button_start_clicked()
{

}
void Teleoperation::on_button_horn_clicked()
{

}
void Teleoperation::on_button_light_clicked()
{

}
//物流任务操作
void Teleoperation::on_button_taskSelect_clicked()
{

}
void Teleoperation::on_button_taskAsk_clicked()
{
    taskQueryWidget.show();
}
void Teleoperation::on_button_boxSelect_clicked()
{
    boxInfoWidget.show();
}
void Teleoperation::on_button_vehicleInfo_clicked()
{
    vehicleInfoWidget.show();
}

