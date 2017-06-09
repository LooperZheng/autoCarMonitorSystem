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
    // 固定窗口的大小
    this->setFixedSize(this->width(), this->height());
    //设置背景颜色和按钮风格
    this->setWindowTitle("车辆信息查看");
    this->setWindowOpacity(0.9);
    ui->textBrowser_allVehicle->setText( QString ("所有车辆： 10\n运行车辆： 10\n故障车辆： 0"));
    //ui->textBrowser->setText("task: 10 \n currrent task: 2");
    //设置弹出窗口的位置（在屏幕中央）
    QDesktopWidget *deskdop=QApplication::desktop();
    this->move((deskdop->width()-this->width())/2,(deskdop->height()-this->height())/2);
    int vehiclelNum =3;
    for(int j=0; j<vehiclelNum; j++)
    {
        QString  itemText = "vehicle_";
        itemText += QString::number(j);
        ui->comboBox_vehicleSelect->insertItem(j,itemText);
    }
}
void VehicleInfoWidget::initConnect()
{
    connect(ui->comboBox_vehicleSelect, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(vehicleSelectCombox_clicked(const QString &)));
}
void VehicleInfoWidget::vehicleSelectCombox_clicked(const QString &text)
{
    QString str;
    str = text;
    ui->textBrowser_oneVehicle->setText(text);
}
