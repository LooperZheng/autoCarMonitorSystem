#include "parcelquerywidget.h"
#include "ui_parcelquerywidget.h"

ParcelQueryWidget::ParcelQueryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParcelQueryWidget)
{
    ui->setupUi(this);
}

ParcelQueryWidget::~ParcelQueryWidget()
{
    delete ui;
}
