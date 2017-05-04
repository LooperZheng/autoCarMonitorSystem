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
    this->setWindowTitle("对话框");
    //设置弹出窗口的位置（在屏幕中央）
    QDesktopWidget *deskdop=QApplication::desktop();
    this->move((deskdop->width()-this->width())/2,(deskdop->height()-this->height())/2);

    ui->radioButton->setFocusPolicy(Qt::NoFocus);
    ui->radioButton_2->setFocusPolicy(Qt::NoFocus);
    ui->radioButton_3->setFocusPolicy(Qt::NoFocus);
    ui->radioButton_4->setFocusPolicy(Qt::NoFocus);

    m_pButtonGroup = new QButtonGroup(this);
    m_pButtonGroup->addButton(ui->radioButton);
    m_pButtonGroup->addButton(ui->radioButton_2);
    m_pButtonGroup->addButton(ui->radioButton_3);
    m_pButtonGroup->addButton(ui->radioButton_4);
}
void RefuseDialog::initConnect()
{
    connect(m_pButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(refuseButtonGroup_clicked(QAbstractButton*)));
}
void RefuseDialog::refuseButtonGroup_clicked(QAbstractButton *button)
{
    QString refuseReason = QString("%1").arg(button->text());
    ui->lineEdit_question->setText(refuseReason);
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
