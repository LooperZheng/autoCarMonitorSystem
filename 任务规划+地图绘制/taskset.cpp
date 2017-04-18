#include "taskset.h"
#include "ui_taskset.h"

taskset::taskset(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::taskset)
{
    ui->setupUi(this);
}

taskset::~taskset()
{
    delete ui;
}
