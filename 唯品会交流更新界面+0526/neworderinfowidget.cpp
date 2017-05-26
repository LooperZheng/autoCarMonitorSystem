#include "neworderinfowidget.h"
#include "ui_neworderinfowidget.h"
#include <QDesktopWidget>
NewOrderInfoWidget::NewOrderInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewOrderInfoWidget)
{
    ui->setupUi(this);
    initUi();//初始化界面参数
    initConnect();//初始化信号和槽连接
}

NewOrderInfoWidget::~NewOrderInfoWidget()
{
    delete ui;
}
void NewOrderInfoWidget::initUi()
{
    this->setWindowTitle("订单信息更新界面");
    //设置弹出窗口的位置（在屏幕中央）
    QDesktopWidget *deskdop=QApplication::desktop();
    this->move((deskdop->width()-this->width())/2,(deskdop->height()-this->height())/2);
}
void NewOrderInfoWidget::initConnect()
{

}
