#include "boxinfowidget.h"
#include "ui_boxinfowidget.h"

BoxInfoWidget::BoxInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoxInfoWidget)
{
    ui->setupUi(this);
}

BoxInfoWidget::~BoxInfoWidget()
{
    delete ui;
}
