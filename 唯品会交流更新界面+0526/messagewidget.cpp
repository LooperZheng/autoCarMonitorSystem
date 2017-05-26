#include "messagewidget.h"
#include "ui_messagewidget.h"
#include <QDesktopWidget>
MessageWidget::MessageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageWidget)
{
    ui->setupUi(this);
    initUi();//初始化界面参数
    initConnect();//初始化信号和槽连接
}

MessageWidget::~MessageWidget()
{
    delete ui;
}
void MessageWidget::initUi()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    QIcon ico(":/images/close.png");
    ui->pushButton_close->setIcon(ico);
    ui->pushButton_close->setIconSize(QSize(10,10));

    //设置弹出窗口的位置（在屏幕中央）
    QDesktopWidget *deskdop=QApplication::desktop();
    this->move((deskdop->width()-this->width())/2,(deskdop->height()-this->height())/2);

    ui->pushButton_msg->setText("您有16条新的订单信息");
}
void MessageWidget::initConnect()
{

}
void MessageWidget::on_pushButton_msg_clicked()
{
    newOrderInfoWidget.show();
}
void MessageWidget::on_pushButton_close_clicked()
{
    this->close();
}
