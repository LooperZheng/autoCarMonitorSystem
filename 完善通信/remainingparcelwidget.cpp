#include "remainingparcelwidget.h"
#include "ui_remainingparcelwidget.h"
#include <QDesktopWidget>
RemainingParcelWidget::RemainingParcelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RemainingParcelWidget)
{
    ui->setupUi(this);
    initUi();//初始化界面参数
    initConnect();//初始化信号和槽连接
}

RemainingParcelWidget::~RemainingParcelWidget()
{
    delete ui;
}
void RemainingParcelWidget::initUi()
{
    // 固定窗口的大小
    this->setFixedSize(this->width(), this->height());

    this->setWindowTitle("余货处理");
    this->setWindowOpacity(0.9);

    //设置弹出窗口的位置（在屏幕中央）
    QDesktopWidget *deskdop=QApplication::desktop();
    this->move((deskdop->width()-this->width())/2,(deskdop->height()-this->height())/2);
}
void RemainingParcelWidget::initConnect()
{

}
void RemainingParcelWidget::on_pushButton_openAllDoor_clicked()
{
    ui->textBrowser_state->setTextColor(QColor(165,73,43));
    ui->textBrowser_state->setText("货柜所有箱门已经打开...");
    ui->textBrowser_state->setTextColor(QColor(0,0,0));
}
void RemainingParcelWidget::on_pushButton_updateParcelState_clicked()
{
    ui->textBrowser_state->setTextColor(QColor(165,73,43));
    ui->textBrowser_state->setText("余货状态已经更新...");
    ui->textBrowser_state->setTextColor(QColor(0,0,0));
}
