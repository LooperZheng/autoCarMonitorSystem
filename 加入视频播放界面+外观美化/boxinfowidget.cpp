#include "boxinfowidget.h"
#include "ui_boxinfowidget.h"

BoxInfoWidget::BoxInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoxInfoWidget)
{
    ui->setupUi(this);
    initUi();//初始化界面参数
    initConnect();//初始化信号和槽连接
}

BoxInfoWidget::~BoxInfoWidget()
{
    delete ui;
}
 void BoxInfoWidget::initUi()
 {

 }
 void BoxInfoWidget::initConnect()
 {

 }
