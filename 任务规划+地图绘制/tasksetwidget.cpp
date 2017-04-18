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
        QString  itemText = "task_";
        itemText += QString::number(i);
        ui->comboBox_addTask->insertItem(i,itemText);
    }

    for(int i=0; i<taskNum; i++)
    {
        QString  itemText = "task_";
        itemText += QString::number(i);
        ui->comboBox_deleTask->insertItem(i,itemText);
    }

}

void TaskSetWidget::initConnect()
{
    connect(ui->comboBox_addTask, SIGNAL(currentIndexChanged(const QString &)), this,SLOT(addTaskCombox_clicked(const QString &)));
    connect(ui->comboBox_deleTask, SIGNAL(currentIndexChanged(const QString &)), this,SLOT(deleTaskCombox_clicked(const QString &)));
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
