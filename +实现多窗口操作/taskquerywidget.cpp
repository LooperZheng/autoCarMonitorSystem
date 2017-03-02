#include "taskquerywidget.h"
#include "ui_taskquerywidget.h"

TaskQueryWidget::TaskQueryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskQueryWidget)
{
    ui->setupUi(this);
}

TaskQueryWidget::~TaskQueryWidget()
{
    delete ui;
}
