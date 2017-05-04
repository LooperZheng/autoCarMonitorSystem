#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QStackedWidget>
#include <QListWidget>
#include <QtWebKitWidgets/QWebView>
#include <QtWebKitWidgets/QWebFrame>
#include <QHBoxLayout>
#include <QPalette>
#include <QTimer>
#include <QTime>
#include "teleoperation.h"
#include "camerasetwidget.h"
#include "taskquerywidget.h"
#include "parcelquerywidget.h"
#include "tasksetwidget.h"
#include "scannerwidget.h"
#include "remainingparcelwidget.h"
#include "rejectionwidget.h"
#include "robot.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //普通构造函数能够被隐式调用,explicit构造函数只能被显式调用。
    explicit MainWindow(QWidget *parent = 0);
    void initConnect();
    void initUi();
    void initData();
    ~MainWindow();

    void sleep(unsigned int msec)
    {
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

public slots:
    void addJavaScriptObject();
    void refreshBaiduMapAll();
    void refreshBaiduMapVehicle();
    void refreshBaiduMapTask();
    void on_button_sysRestart_clicked();
    void on_button_cameraSet_clicked();
    void on_button_operationExchange_clicked();
    void on_button_taskSet_clicked();
    void on_button_taskQuery_clicked();
    void on_button_parcelQuery_clicked();
    void on_button_scanner_clicked();
    void on_button_monitorStart_clicked();
    void on_button_vehicleStart_clicked();
    void on_button_remainingHandle_clicked();

    void showTime();
     //不同类对象之间通信
    void teleoperationWidget_TaskAskShow();
    void teleoperationWidget_BoxAskShow();
    void teleoperationWidget_VehicleAskShow();

    void teleoperationWidget_VehicleTurnLeft();
    void teleoperationWidget_VehicleTurnRight();
    void teleoperationWidget_VehicleForward();
    void teleoperationWidget_VehicleBackward();
    void teleoperationWidget_VehicleStop();
    void teleoperationWidget_VehicleStart();
    void teleoperationWidget_VehicleHorn();
    void teleoperationWidget_VehicleLight();

private:
    Ui::MainWindow *ui;
    Robot *myRobot;
    QTimer *timer;
    QTimer *timer_mapRefresh;
    Teleoperation teleoperation;
    CameraSetWidget cameraSetWidget;
    TaskQueryWidget taskQueryWidget;
    ParcelQueryWidget parcelQueryWidget;
    TaskSetWidget taskSetWidget;
    VehicleInfoWidget vehicleInfoWidget;
    BoxInfoWidget boxInfoWidget;
    ScannerWidget scannerWidget;
    RemainingParcelWidget remainingParcelWidget;
    RejectionWidget rejectionWidget;
};

#endif // MAINWINDOW_H
