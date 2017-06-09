#include "taskquerywidget.h"
#include "ui_taskquerywidget.h"
#include <QDesktopWidget>

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
    // 固定窗口的大小
    this->setFixedSize(this->width(), this->height());
    //设置背景颜色和按钮风格
    this->setWindowTitle("任务查看");
    this->setWindowOpacity(0.9);
    //ui->textBrowser->setText("task: 10 \n currrent task: 2");
    //设置弹出窗口的位置（在屏幕中央）
    QDesktopWidget *deskdop=QApplication::desktop();
    this->move((deskdop->width()-this->width())/2,(deskdop->height()-this->height())/2);
    //初始化下拉列表
    int taskNum = 5;
    for(int i=0; i<taskNum; i++)
    {

        QString  itemText = "task_";
        itemText += QString::number(i);
        ui->comboBox_taskSelect->insertItem(i,itemText);
    }
    int parcelNum =3;
    for(int j=0; j<parcelNum; j++)
    {
        QString  itemText = "parcel_";
        itemText += QString::number(j);
        ui->comboBox_parcelSelect->insertItem(j,itemText);
    }
    QString  itemText = "预约为班次1的订单";
    ui->comboBox_schedule->insertItem(0,itemText);
    QString  itemText_1 = "预约为班次2的订单";
    ui->comboBox_schedule->insertItem(1,itemText_1);
    QString  itemText_2 = "预约为班次3的订单";
    ui->comboBox_schedule->insertItem(2,itemText_2);
    QString  itemText_3 = "预约为班次4的订单";
    ui->comboBox_schedule->insertItem(3,itemText_3);
    QString  itemText_4 = "未预约的订单";
    ui->comboBox_schedule->insertItem(4,itemText_4);

    QString  itemText_rankways = "按照预约时间排列";
    ui->comboBox_rankWays->insertItem(0,itemText_rankways);
    QString  itemText_rankways_1 = "按照预约班次排列";
    ui->comboBox_rankWays->insertItem(1,itemText_rankways_1);
    //所有任务信息
    QString allTaskInfo = "所有任务： 10\n当前任务： 2\n完成任务： 2\n后续任务： 7";
    ui->textBrowser_allTask->setText(allTaskInfo);

}
void TaskQueryWidget::initConnect()
{
    connect(ui->comboBox_parcelSelect, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(parcelSelectCombox_clicked(const QString &)));
    connect(ui->comboBox_taskSelect, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(taskSelectCombox_clicked(const QString &)));
    connect(ui->comboBox_schedule, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(scheduleCombox_clicked(const QString &)));
    connect(ui->comboBox_rankWays, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(rankWaysCombox_clicked(const QString &)));
}
void TaskQueryWidget::parcelSelectCombox_clicked(const QString &text)
{
    QString str;
    str = text;
    ui->textBrowser_oneParcel->setText(text);

}
void TaskQueryWidget::taskSelectCombox_clicked(const QString &text)
{
    QString str;
    str = text;
    ui->textBrowser_oneTask->setText(text);

}
void TaskQueryWidget::scheduleCombox_clicked(const QString &text)
{
    QString str;
    str = text;
    ui->textBrowser_schedule->setText(text);
}
void TaskQueryWidget::rankWaysCombox_clicked(const QString &text)
{
    QString str;
    str = text;
    ui->textBrowser_rankWays->setText(text);
}
