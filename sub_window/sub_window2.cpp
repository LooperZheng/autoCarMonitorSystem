#include "sub_window2.h"
#include "ui_sub_window2.h"

Sub_window2::Sub_window2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sub_window2)
{
    ui->setupUi(this);
}

Sub_window2::~Sub_window2()
{
    delete ui;
}
void Sub_window2::on_pushButton_clicked()
{
    this->close();
}
