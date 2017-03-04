#include "taskquerywidget.h"
#include "ui_taskquerywidget.h"
#define TEXT_COLOR  QColor(5,170,255)
TaskQueryWidget::TaskQueryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskQueryWidget)
{
    ui->setupUi(this);
    initUi();//初始化界面参数
    initConnect();//初始化信号和槽连接
}

TaskQueryWidget::~TaskQueryWidget()
{
    delete ui;
}

void TaskQueryWidget::initUi()
{
    //设置背景颜色和按钮风格
    this->setWindowTitle("任务查看");
    this->setWindowOpacity(0.8);
    ui->textBrowser->setStyleSheet("background-color:rgba(255,255,255,80)");
    ui->textBrowser->setTextColor(TEXT_COLOR);
    ui->textBrowser->setText( QString ("包裹信息"));
    //ui->textBrowser->setText("task: 10 \n currrent task: 2");
}
void TaskQueryWidget::initConnect()
{

}
