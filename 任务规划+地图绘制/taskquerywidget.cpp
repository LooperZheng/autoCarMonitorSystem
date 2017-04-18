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
    //设置背景颜色和按钮风格
    this->setWindowTitle("任务查看");
    this->setWindowOpacity(0.9);
    ui->textBrowser_taskTime->setText( QString ("空天院 ： 9:45\n电信楼 ： 9:59"));
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
    //所有任务信息
    QString allTaskInfo = "所有任务： 10\n当前任务： 2\n完成任务： 2\n后续任务： 7";
    ui->textBrowser_allTask->setText(allTaskInfo);

}
void TaskQueryWidget::initConnect()
{
    connect(ui->comboBox_parcelSelect, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(parcelSelectCombox_clicked(const QString &)));
    connect(ui->comboBox_taskSelect, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(taskSelectCombox_clicked(const QString &)));
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
