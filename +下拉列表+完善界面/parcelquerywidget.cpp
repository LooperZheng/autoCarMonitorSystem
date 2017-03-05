#include "parcelquerywidget.h"
#include "ui_parcelquerywidget.h"
#include <QDesktopWidget>
#include <QColor>
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
    this->setWindowTitle("包裹查看");
    this->setWindowOpacity(0.9);
    ui->textBrowser->setTextColor(QColor(0,0,0));
    ui->textBrowser->setText( QString ("包裹信息"));
    //ui->textBrowser->setText("task: 10 \n currrent task: 2");

    //设置弹出窗口的位置（在屏幕中央）
    QDesktopWidget *deskdop=QApplication::desktop();
    this->move((deskdop->width()-this->width())/2,(deskdop->height()-this->height())/2);
}
void ParcelQueryWidget::initConnect()
{

}
bool ParcelQueryWidget::checkParcelNum(QString parcelNum)
{
    if(parcelNum.length()!= 12)
        return false;
    else
    {
        for(int i=0; i<parcelNum.length(); i++)
        {
            if(parcelNum[i]>='0' && parcelNum[i]<='9');
            else
                return false;
        }
    }
    return true;
}
bool ParcelQueryWidget::isParcelExist(QString ParcelNum)
{
    if( 1==1 )
        return false;
    else
        return true;
}
void ParcelQueryWidget::on_pushButton_parcelQuery_clicked()
{
    QString parcelNum = ui->playerEdit->text();
    if(checkParcelNum(parcelNum))
    {
        if(isParcelExist(parcelNum))
        {
            ui->textBrowser->setText(parcelNum);
        }
        else
        {
            ui->textBrowser->setTextColor(QColor(165,73,43));
            ui->textBrowser->setText("您查询的包裹不存在。\n请核运单号。");
            ui->textBrowser->setTextColor(QColor(0,0,0));
        }
    }
    else
    {
        if(parcelNum.length() == 0)
        {
            ui->textBrowser->setTextColor(QColor(255,0,0));
            ui->textBrowser->setText("输入运单号不能为空！");
            ui->textBrowser->setTextColor(QColor(0,0,0));
        }
            else
        {
            ui->textBrowser->setTextColor(QColor(255,0,0));
            ui->textBrowser->setText("输入运单号不合法（12位数字）！\n请核对后重新输入！");
            ui->textBrowser->setTextColor(QColor(0,0,0));
        }
    }
}
