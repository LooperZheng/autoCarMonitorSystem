#include "tasksetwidget.h"
#include "ui_tasksetwidget.h"
#include <QDesktopWidget>
#include <QDebug>
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
    // 固定窗口的大小
    this->setFixedSize(this->width(), this->height());

    this->setWindowTitle("任务设置");
    this->setWindowOpacity(0.9);

    //设置弹出窗口的位置（在屏幕中央）
    QDesktopWidget *deskdop=QApplication::desktop();
    this->move((deskdop->width()-this->width())/2,(deskdop->height()-this->height())/2);

    //初始化下拉列表
    int taskNum = 6;
    for(int i=0; i<taskNum; i++)
    {
        QString  itemText = "taskParcel_";
        itemText += QString::number(i+1);
        ui->comboBox_addTask->insertItem(i,itemText);
    }

    for(int i=0; i<taskNum; i++)
    {
        QString  itemText = "taskParcel_";
        itemText += QString::number(i+1);
        ui->comboBox_deleTask->insertItem(i,itemText);
    }
    //输出显示规划任务序列
    QString taskSeqText;
    for(int i =0; i<taskSeq.size();i++)
    {
        taskSeqText.append("task_");
        taskSeqText.append(QString::number(taskSeq[i]));
        taskSeqText.append("\n");
    }
    ui->textBrowser_taskSeq->setText(taskSeqText);


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
    //ui->textBrowser_taskSeq->setText(text);
}

void TaskSetWidget::deleTaskCombox_clicked(const QString &text)
{
    QString str;
    str = text;
    //ui->textBrowser_taskSeq->setText(text);
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

//任务规划设置
void TaskSetWidget::on_pushButton_addTask_clicked()
{
    int index =  ui->comboBox_addTask->currentIndex();
    //qDebug()<<index;
    if(std::find(taskSeq.begin(),taskSeq.end(),index+1) == taskSeq.end())
        taskSeq.push_back(index+1);

    //
    QString taskSeqText;
    for(int i =0; i<taskSeq.size();i++)
    {
        taskSeqText.append("task_");
        taskSeqText.append(QString::number(taskSeq[i]));
        taskSeqText.append("\n");
    }
    ui->textBrowser_taskSeq->setText(taskSeqText);

}
void TaskSetWidget::on_pushButton_deleTask_clicked()
{
    int index =  ui->comboBox_deleTask->currentIndex();
    if(std::find(taskSeq.begin(),taskSeq.end(),index+1) != taskSeq.end())
    {
        std::vector<int> temp;
        for(int i =0; i<taskSeq.size();i++)
        {
            if(taskSeq[i] != index+1)
                temp.push_back(taskSeq[i]);
        }
        taskSeq.clear();
        taskSeq=temp;
    }

    //
    QString taskSeqText;
    for(int i =0; i<taskSeq.size();i++)
    {
        taskSeqText.append("task_");
        taskSeqText.append(QString::number(taskSeq[i]));
        taskSeqText.append("\n");
    }
    ui->textBrowser_taskSeq->setText(taskSeqText);
}
void TaskSetWidget::on_pushButton_startPlan_clicked()
{
    emit signal_startTaskPlan(taskSeq);
    qDebug()<<"emit start task paln";
}
void TaskSetWidget::gettaskseq(std::vector<int> data)
{

    taskSeq= data;
    //
    QString taskSeqText;
    for(int i =0; i<taskSeq.size();i++)
    {
        taskSeqText.append("task_");
        taskSeqText.append(QString::number(taskSeq[i]));
        taskSeqText.append("\n");
    }
    ui->textBrowser_taskSeq->setText(taskSeqText);

}
void TaskSetWidget::TaskPlanInfoShow(result planRes)
{
    //输出显示规划结果
    QString text;
    text.append("规划结果");
    if( planRes.isValid == true)
    {
        text.append("成功");
        text.append("\n");
        text.append("规划路程：");
        text.append(QString::number(planRes.dis));
        text.append("m\n");
        text.append("预计行驶时间：");
        text.append(QString::number(planRes.dis/20));
        text.append("min\n");
        text.append("路径点个数：");
        text.append(QString::number(planRes.path.size()));
        text.append("\n");
        text.append("任务点个数：");
        text.append(QString::number(planRes.taskSeq.size()));
    }
    else
    {
        text.append("失败");
    }
    ui->textBrowser_planRes->setText(text);

    //输出显示规划任务序列
    QString taskSeqText;
    for(int i =0; i<planRes.taskSeq.size();i++)
    {
        taskSeqText.append("task_");
        taskSeqText.append(QString::number(planRes.taskSeq[i]));
        taskSeqText.append("\n");
    }
    ui->textBrowser_taskSeq->setText(taskSeqText);

}
//包裹修改
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
