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
#include "teleoperation.h"
#include "camerasetwidget.h"
#include "taskquerywidget.h"
#include "parcelquerywidget.h"
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
    ~MainWindow();

public slots:
    void addJavaScriptObject();

    void on_button_sysRestart_clicked();
    void on_button_cameraSet_clicked();
    void on_button_operationExchange_clicked();
    void on_button_taskSet_clicked();
    void on_button_taskQuery_clicked();
    void on_button_parcelQuery_clicked();
private:
    Ui::MainWindow *ui;
    Robot *myRobot;
    Teleoperation teleoperation;
    CameraSetWidget cameraSetWidget;
    TaskQueryWidget taskQueryWidget;
    ParcelQueryWidget parcelQueryWidget;
};

#endif // MAINWINDOW_H
