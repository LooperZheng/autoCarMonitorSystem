#include "boxinfowidget.h"
#include "ui_boxinfowidget.h"
#include <QGridLayout>
#include <QButtonGroup>
#include <QRadioButton>
#include <QDebug>
#include <QString>
#include <QDesktopWidget>
BoxInfoWidget::BoxInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoxInfoWidget)
{
    ui->setupUi(this);
    initUi();//初始化界面参数
    initConnect();//初始化信号和槽连接
}

BoxInfoWidget::~BoxInfoWidget()
{
    delete ui;
}
 void BoxInfoWidget::initUi()
 {
     this->setWindowTitle("货柜信息界面");
     //设置弹出窗口的位置（在屏幕中央）
     QDesktopWidget *deskdop=QApplication::desktop();
     this->move((deskdop->width()-this->width())/2,      (deskdop->height()-this->height())/2);

    //设置分割线的颜色和每个RadioButton的聚焦点，每个RadioButton的样式在界面设计器中的样式表中设计
     ui->line->setStyleSheet("border-top: 1px solid grey; background-color: grey") ;
     ui->line_2->setStyleSheet("border-top: 1px solid grey; background-color: grey") ;
     ui->radioButton_1->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_2->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_3->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_4->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_5->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_6->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_7->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_8->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_9->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_10->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_11->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_12->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_13->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_14->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_15->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_16->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_17->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_18->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_19->setFocusPolicy(Qt::NoFocus);
     ui->radioButton_20->setFocusPolicy(Qt::NoFocus);

     m_pButtonGroup = new QButtonGroup(this);
     m_pButtonGroup->addButton(ui->radioButton_1);
     m_pButtonGroup->addButton(ui->radioButton_2);
     m_pButtonGroup->addButton(ui->radioButton_3);
     m_pButtonGroup->addButton(ui->radioButton_4);
     m_pButtonGroup->addButton(ui->radioButton_5);
     m_pButtonGroup->addButton(ui->radioButton_6);
     m_pButtonGroup->addButton(ui->radioButton_7);
     m_pButtonGroup->addButton(ui->radioButton_8);
     m_pButtonGroup->addButton(ui->radioButton_9);
     m_pButtonGroup->addButton(ui->radioButton_10);
     m_pButtonGroup->addButton(ui->radioButton_11);
     m_pButtonGroup->addButton(ui->radioButton_12);
     m_pButtonGroup->addButton(ui->radioButton_13);
     m_pButtonGroup->addButton(ui->radioButton_14);
     m_pButtonGroup->addButton(ui->radioButton_15);
     m_pButtonGroup->addButton(ui->radioButton_16);
     m_pButtonGroup->addButton(ui->radioButton_17);
     m_pButtonGroup->addButton(ui->radioButton_18);
     m_pButtonGroup->addButton(ui->radioButton_19);
     m_pButtonGroup->addButton(ui->radioButton_20);

  }
 void BoxInfoWidget::initConnect()
 {
     connect(m_pButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(on_boxButtonGroup_Clicked(QAbstractButton*)));

 }
void BoxInfoWidget::on_boxButtonGroup_Clicked(QAbstractButton *button)
{
    // 当前点击的按钮
     QString boxNum = QString("货柜编号：%1").arg(button->text());
     ui->textBrowser->setText(boxNum);

}
