#include "vehicleinfowidget.h"
#include "ui_vehicleinfowidget.h"
#include <QDesktopWidget>
#define TEXT_COLOR  QColor(5,170,255)
VehicleInfoWidget::VehicleInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VehicleInfoWidget)
{
    ui->setupUi(this);
    initUi();//初始化界面参数
    initConnect();//初始化信号和槽连接
}

VehicleInfoWidget::~VehicleInfoWidget()
{
    delete ui;
}
void VehicleInfoWidget::initUi()
{
    //设置背景颜色和按钮风格
    this->setWindowTitle("车辆信息查看");
    this->setWindowOpacity(0.8);
    ui->textBrowser->setStyleSheet("background-color:rgba(255,255,255,80)");
    ui->textBrowser->setTextColor(TEXT_COLOR);
    ui->textBrowser->setText( QString ("包裹信息"));
    //ui->textBrowser->setText("task: 10 \n currrent task: 2");
    //设置弹出窗口的位置（在屏幕中央）
    QDesktopWidget *deskdop=QApplication::desktop();
    this->move((deskdop->width()-this->width())/2,      (deskdop->height()-this->height())/2);
}
void VehicleInfoWidget::initConnect()
{

}
