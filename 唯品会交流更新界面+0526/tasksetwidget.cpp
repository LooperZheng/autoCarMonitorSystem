#include "tasksetwidget.h"
#include "ui_tasksetwidget.h"
#include <QDesktopWidget>

TaskSetWidget::TaskSetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskSetWidget)
{
    ui->setupUi(this);
    initUi();//初始化界面参数
    initConnect();//初始化信号和槽连接
}

TaskSetWidget::~TaskSetWidget()
{
    delete ui;
}

void TaskSetWidget::initUi()
{
    this->setWindowTitle("任务设置");
    this->setWindowOpacity(0.9);

    //设置弹出窗口的位置（在屏幕中央）
    QDesktopWidget *deskdop=QApplication::desktop();
    this->move((deskdop->width()-this->width())/2,(deskdop->height()-this->height())/2);

    //初始化下拉列表
    int taskNum = 5;
    for(int i=0; i<taskNum; i++)
    {
        QString  itemText = "taskParcel_";
        itemText += QString::number(i);
        ui->comboBox_addTask->insertItem(i,itemText);
    }

    for(int i=0; i<taskNum; i++)
    {
        QString  itemText = "taskParcel_";
        itemText += QString::number(i);
        ui->comboBox_deleTask->insertItem(i,itemText);
    }

    ui->comboBox_schedule->insertItem(0,"0");
    ui->comboBox_schedule->insertItem(1,"1");
    ui->comboBox_distributionTime->insertItem(0,"9:30");
    ui->comboBox_distributionTime->insertItem(1,"10:30");
    ui->comboBox_distributionWays->insertItem(0,"man");
    ui->comboBox_distributionWays->insertItem(1,"robot");
    ui->comboBox_distributionDestination->insertItem(0,"SEEE");
    ui->comboBox_distributionDestination->insertItem(1,"Air");

}

void TaskSetWidget::initConnect()
{
    connect(ui->comboBox_addTask, SIGNAL(currentIndexChanged(const QString &)), this,SLOT(addTaskCombox_clicked(const QString &)));
    connect(ui->comboBox_deleTask, SIGNAL(currentIndexChanged(const QString &)), this,SLOT(deleTaskCombox_clicked(const QString &)));
    connect(ui->comboBox_schedule, SIGNAL(currentIndexChanged(const QString &)), this,SLOT(changeDistributionSchedule_clicked(const QString &)));
    connect(ui->comboBox_distributionTime, SIGNAL(currentIndexChanged(const QString &)), this,SLOT(changeDistributionTime_clicked(const QString &)));
    connect(ui->comboBox_distributionWays, SIGNAL(currentIndexChanged(const QString &)), this,SLOT(changeDistributionWays_clicked(const QString &)));
    connect(ui->comboBox_distributionDestination, SIGNAL(currentIndexChanged(const QString &)), this,SLOT(changeDistributionDestination_clicked(const QString &)));
}

void TaskSetWidget::addTaskCombox_clicked(const QString &text)
{
    QString str;
    str = text;
    ui->textBrowser_taskSeq->setText(text);
}

void TaskSetWidget::deleTaskCombox_clicked(const QString &text)
{
    QString str;
    str = text;
    ui->textBrowser_taskSeq->setText(text);
}
void TaskSetWidget::changeDistributionSchedule_clicked(const QString &text)
{
    QString str;
    str = text;
    ui->textBrowser_state->setText(text);
}
void TaskSetWidget::changeDistributionTime_clicked(const QString &text)
{
    QString str;
    str = text;
    ui->textBrowser_state->setText(text);
}
void TaskSetWidget::changeDistributionWays_clicked(const QString &text)
{
    QString str;
    str = text;
    ui->textBrowser_state->setText(text);
}
void TaskSetWidget::changeDistributionDestination_clicked(const QString &text)
{
    QString str;
    str = text;
    ui->textBrowser_state->setText(text);
}
//
void TaskSetWidget::on_pushButton_addTask_clicked()
{
    QString str = "text";
}
void TaskSetWidget::on_pushButton_deleTask_clicked()
{
    QString str = "text";

}
void TaskSetWidget::on_pushButton_startPlan_clicked()
{
    QString str = "text";

}

void TaskSetWidget::on_pushButton_parcelQuery_clicked()
{
    ui->textBrowser_state->setTextColor(QColor(165,73,43));
    ui->textBrowser_state->setText("query");
    ui->textBrowser_state->setTextColor(QColor(0,0,0));
}
void TaskSetWidget::on_pushButton_changeSchedule_clicked()
{
    ui->textBrowser_state->setTextColor(QColor(165,73,43));
    ui->textBrowser_state->setText("包裹配送班次已修改");
    ui->textBrowser_state->setTextColor(QColor(0,0,0));
}
void TaskSetWidget::on_pushButton_changeDistributionWays_clicked()
{
    ui->textBrowser_state->setTextColor(QColor(165,73,43));
    ui->textBrowser_state->setText("包裹配送方式已修改");
    ui->textBrowser_state->setTextColor(QColor(0,0,0));
}
void TaskSetWidget::on_pushButton_changeDistributionTime_clicked()
{
    ui->textBrowser_state->setTextColor(QColor(165,73,43));
    ui->textBrowser_state->setText("包裹配送时间已修改");
    ui->textBrowser_state->setTextColor(QColor(0,0,0));
}
void TaskSetWidget::on_pushButton_changeDistributionDestination_clicked()
{
    ui->textBrowser_state->setTextColor(QColor(165,73,43));
    ui->textBrowser_state->setText("包裹配送目标站点已修改");
    ui->textBrowser_state->setTextColor(QColor(0,0,0));
}
