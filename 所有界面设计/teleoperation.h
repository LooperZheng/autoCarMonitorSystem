#ifndef TELEOPERATION_H
#define TELEOPERATION_H

#include <QWidget>
#include "boxinfowidget.h"
#include "vehicleinfowidget.h"
#include "taskquerywidget.h"
#include <QGraphicsView>
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

    void on_button_adas_clicked();
    void on_button_taskAsk_clicked();
    void on_button_boxSelect_clicked();
    void on_button_vehicleInfo_clicked();

    void on_button_changeViewport_left_clicked();
    void on_button_changeViewport_back_clicked();
    void on_button_changeViewport_right_clicked();
    void on_button_changeViewport_front_clicked();
    void on_button_changeViewport_map_clicked();
signals:
    void signal_showTaskQueryWidget();
    void signal_showBoxQueryWidget();
    void signal_showVehicleQueryWidget();

    void signal_vehicleControlTurnLeft();
    void signal_vehicleControlTurnRight();
    void signal_vehicleControlTurnForward();
    void signal_vehicleControlTurnBackward();
    void signal_vehicleControlStop();
    void signal_vehicleControlStart();
    void signal_vehicleControlHorn();
    void signal_vehicleControlLight();

private:
    void initUi();//初始化界面参数
    void initConnect();//初始化信号和槽连接

private:
    Ui::Teleoperation *ui;

    QGraphicsScene scene_front ;
    QPixmap image_frontRed;
    QPixmap image_frontGreen;
    QPixmap image_frontYellow;
    QGraphicsScene scene_left;
    QPixmap image_leftRed;
    QPixmap image_leftGreen;
    QPixmap image_leftYellow;
    QGraphicsScene scene_right;
    QPixmap image_rightRed;
    QPixmap image_rightGreen;
    QPixmap image_rightYellow;
    QGraphicsScene scene_back ;
    QPixmap image_backRed;
    QPixmap image_backGreen;
    QPixmap image_backYellow;
    QGraphicsScene scene_lidar ;
    QPixmap image_lidar;
    bool adasFlag;
    bool mapFlag;


};

#endif // TELEOPERATION_H
