#include "teleoperation.h"
#include "ui_teleoperation.h"

Teleoperation::Teleoperation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Teleoperation)
{
    ui->setupUi(this);
}

Teleoperation::~Teleoperation()
{
    delete ui;
}
//车辆操作
void Teleoperation::on_button_turnLeft_clicked()
{

}
void Teleoperation::on_button_turnRight_clicked()
{

}
void Teleoperation::on_button_forward_clicked()
{

}
void Teleoperation::on_button_backward_clicked()
{

}
void Teleoperation::on_button_stop_clicked()
{

}
void Teleoperation::on_button_start_clicked()
{

}
void Teleoperation::on_button_horn_clicked()
{

}
void Teleoperation::on_button_light_clicked()
{

}
//物流任务操作
void Teleoperation::on_button_taskSelect_clicked()
{

}
void Teleoperation::on_button_taskAsk_clicked()
{
    taskQueryWidget.show();
}
void Teleoperation::on_button_boxSelect_clicked()
{
    boxInfoWidget.show();
}
void Teleoperation::on_button_vehicleInfo_clicked()
{
    vehicleInfoWidget.show();
}

