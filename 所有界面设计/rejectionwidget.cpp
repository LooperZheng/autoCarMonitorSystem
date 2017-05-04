#include "rejectionwidget.h"
#include "ui_rejectionwidget.h"
#include <QDesktopWidget>
RejectionWidget::RejectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RejectionWidget)
{
    ui->setupUi(this);
    initUi();//初始化界面参数
    initConnect();//初始化信号和槽连接
}

RejectionWidget::~RejectionWidget()
{
    delete ui;
}
void RejectionWidget::initUi()
{
    this->setWindowTitle("拒收处理界面");
    this->setWindowOpacity(0.9);

    //设置弹出窗口的位置（在屏幕中央）
    QDesktopWidget *deskdop=QApplication::desktop();
    this->move((deskdop->width()-this->width())/2,(deskdop->height()-this->height())/2);
}
void RejectionWidget::initConnect()
{

}
void RejectionWidget::on_pushButton_agree_clicked()
{

}
void RejectionWidget::on_pushButton_disagree_clicked()
{
    refuseDialog.show();
}
