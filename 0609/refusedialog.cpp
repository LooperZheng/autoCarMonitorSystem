#include "refusedialog.h"
#include "ui_refusedialog.h"
#include <QDesktopWidget>
RefuseDialog::RefuseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RefuseDialog)
{
    ui->setupUi(this);
    initUi();//初始化界面参数
    initConnect();//初始化信号和槽连接
}

RefuseDialog::~RefuseDialog()
{
    delete ui;
}
void RefuseDialog::initUi()
{
    // 固定窗口的大小
    this->setFixedSize(this->width(), this->height());

    this->setWindowTitle("对话框");
    //设置弹出窗口的位置（在屏幕中央）
    QDesktopWidget *deskdop=QApplication::desktop();
    this->move((deskdop->width()-this->width())/2,(deskdop->height()-this->height())/2);

    QString  itemText = "包裹已破损";
    ui->comboBox_refuseReason->insertItem(0,itemText);
    QString  itemText_1 = "与描述不符";
    ui->comboBox_refuseReason->insertItem(1,itemText_1);
    QString  itemText_2 = "运费问题";
    ui->comboBox_refuseReason->insertItem(2,itemText_2);
    QString  itemText_3 = "其他";
    ui->comboBox_refuseReason->insertItem(3,itemText_3);

}
void RefuseDialog::initConnect()
{

}

void RefuseDialog::on_pushButton_yes_clicked()
{
    this->close();
    ui->lineEdit_question->clear();
}
void RefuseDialog::on_pushButton_cancell_clicked()
{
    this->close();
    ui->lineEdit_question->clear();
}
