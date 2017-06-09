#ifndef TELEOPERATION_H
#define TELEOPERATION_H

#include <QWidget>
#include "boxinfowidget.h"
#include "vehicleinfowidget.h"
#include "taskquerywidget.h"
#include <QGraphicsView>

//hkws
#include <QFrame>
#include "HCNetSDK.h"
#include "FramePlayWnd.h"
#include "robot.h"

#include <QPainter>
#include <QPoint>
#include <QMouseEvent>
#ifndef HPR_OK
#define HPR_OK 0
#endif

#ifndef HPR_ERROR
#define HPR_ERROR -1
#endif

namespace Ui {
class Teleoperation;
}

class Teleoperation : public QWidget
{
    Q_OBJECT

public:
    explicit Teleoperation(QWidget *parent = 0);
    ~Teleoperation();
    void setSysState();

    //hkws
    QFrame *frame_left;
    QFrame *frame_right;
    QFrame *frame_back;
    QFrame *frame_front;
    QFrame *frame_main;

    CFramePlayWnd *frames[4];
    LONG lUserID;

    int init_nvr();
    int Demo_GetStream_V30(LONG lUserID);
    int StartGetStream(LONG lUserID, int c_id, int f_id);
    int StopNVR();
    void Demo_SDK_Version();

public slots:
    void on_button_playVideo_clicked();
    void on_button_stopVideo_clicked();

public slots:
    void on_button_turnLeft_clicked();
    void on_button_turnRight_clicked();
    void on_button_forward_clicked();
    void on_button_backward_clicked();
    void on_button_stop_clicked();
    void on_button_start_clicked();
    void on_button_horn_clicked();
    void on_button_light_clicked();
    void on_button_lightClose_clicked();
    void on_button_operationExchange_clicked();

    void on_button_adas_clicked();
    void on_button_taskAsk_clicked();
    void on_button_boxSelect_clicked();
    void on_button_vehicleInfo_clicked();

    void on_button_changeViewport_left_clicked();
    void on_button_changeViewport_back_clicked();
    void on_button_changeViewport_right_clicked();
    void on_button_changeViewport_front_clicked();

    void slot_sendVehicleCmd();
    void updateRobotInfo(Robot *);
    void refreshMap();
    void addJavaScriptObject();

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
    void signal_vehicleControlLightClose();
    void signal_operationExchange();


    void signal_vehicleControlCmd(double vel, double alpha);

private:
    void initUi();//初始化界面参数
    void initConnect();//初始化信号和槽连接

private:
    Ui::Teleoperation *ui;
    Robot *myRobot;

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
    QTimer *timer;
    QTimer *timer_refreshMap;

    //vehicle con
    QPointF lastPoint;
    QPointF endPoint;
    QPainterPath path;
    int mouseReleaseNum;
    int mousePressNum;
    bool mouseMove;
    bool enable;
    bool enableOperation;
    bool isInCircle(QPointF centerPoint, float r , QPointF mouseCurPoint);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

};

#endif // TELEOPERATION_H
