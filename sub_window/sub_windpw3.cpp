#include "sub_windpw3.h"
#include "ui_sub_windpw3.h"

Sub_windpw3::Sub_windpw3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sub_windpw3)
{
    ui->setupUi(this);
}

Sub_windpw3::~Sub_windpw3()
{
    delete ui;
}
void Sub_windpw3::on_pushButton_clicked()
{
    this->close();
}
