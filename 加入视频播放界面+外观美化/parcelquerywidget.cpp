#include "parcelquerywidget.h"
#include "ui_parcelquerywidget.h"
#define TEXT_COLOR  QColor(5,170,255)
ParcelQueryWidget::ParcelQueryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParcelQueryWidget)
{
    ui->setupUi(this);
    initUi();//初始化界面参数
    initConnect();//初始化信号和槽连接
}

ParcelQueryWidget::~ParcelQueryWidget()
{
    delete ui;
}
void ParcelQueryWidget::initUi()
{
    //设置背景颜色和按钮风格
    this->setWindowTitle("任务查看");
    this->setWindowOpacity(0.8);
    ui->textBrowser->setStyleSheet("background-color:rgba(255,255,255,80)");
    ui->textBrowser->setTextColor(TEXT_COLOR);
    ui->textBrowser->setText( QString ("包裹信息"));
    //ui->textBrowser->setText("task: 10 \n currrent task: 2");
}
void ParcelQueryWidget::initConnect()
{

}
