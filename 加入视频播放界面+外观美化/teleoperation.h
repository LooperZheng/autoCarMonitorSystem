#ifndef TELEOPERATION_H
#define TELEOPERATION_H

#include <QWidget>
#include "boxinfowidget.h"
#include "vehicleinfowidget.h"
#include "taskquerywidget.h"
namespace Ui {
class Teleoperation;
}

class Teleoperation : public QWidget
{
    Q_OBJECT

public:
    explicit Teleoperation(QWidget *parent = 0);
    ~Teleoperation();
public slots:
    void on_button_turnLeft_clicked();
    void on_button_turnRight_clicked();
    void on_button_forward_clicked();
    void on_button_backward_clicked();
    void on_button_stop_clicked();
    void on_button_start_clicked();
    void on_button_horn_clicked();
    void on_button_light_clicked();

    void on_button_taskSelect_clicked();
    void on_button_taskAsk_clicked();
    void on_button_boxSelect_clicked();
    void on_button_vehicleInfo_clicked();
private:
    void initUi();//初始化界面参数
    void initConnect();//初始化信号和槽连接

private:
    Ui::Teleoperation *ui;
    BoxInfoWidget boxInfoWidget;
    VehicleInfoWidget vehicleInfoWidget;
    TaskQueryWidget taskQueryWidget;

};

#endif // TELEOPERATION_H
