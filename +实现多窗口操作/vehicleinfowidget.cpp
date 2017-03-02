#include "vehicleinfowidget.h"
#include "ui_vehicleinfowidget.h"

VehicleInfoWidget::VehicleInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VehicleInfoWidget)
{
    ui->setupUi(this);
}

VehicleInfoWidget::~VehicleInfoWidget()
{
    delete ui;
}
