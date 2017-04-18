#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <string>
#include <vector>
#define TEXT_COLOR  QColor(255,255,255)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui=new Ui::MainWindow();
    myRobot=new Robot(this);
    initData();
    initUi();//初始化界面参数
    initConnect();//初始化信号和槽连接

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initData()
{
    myRobot->getPathPointFromTopoMap();
    myRobot->getPathMapFromTopoMap();
    myRobot->getTaskSeqFromLogisticDB();
}
void MainWindow::initConnect()
{
     connect(ui->webView->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),this, SLOT(addJavaScriptObject()));//地图刷新调取
     QObject::connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
     QObject::connect(timer_mapRefresh,SIGNAL(timeout()),this,SLOT(addJavaScriptObject()));
     //不同类对象之间通信
     connect( &(this->teleoperation), SIGNAL(signal_showTaskQueryWidget()), SLOT (teleoperationWidget_TaskAskShow()));
     connect( &(this->teleoperation), SIGNAL(signal_showBoxQueryWidget()), SLOT (teleoperationWidget_BoxAskShow()));
     connect( &(this->teleoperation), SIGNAL(signal_showVehicleQueryWidget()), SLOT (teleoperationWidget_VehicleAskShow()));

     connect( &(this->teleoperation), SIGNAL(signal_vehicleControlTurnLeft()), SLOT (teleoperationWidget_VehicleTurnLeft()));
     connect( &(this->teleoperation), SIGNAL(signal_vehicleControlTurnRight()), SLOT (teleoperationWidget_VehicleTurnRight()));
     connect( &(this->teleoperation), SIGNAL(signal_vehicleControlTurnForward()), SLOT (teleoperationWidget_VehicleForward()));
     connect( &(this->teleoperation), SIGNAL(signal_vehicleControlTurnBackward()), SLOT (teleoperationWidget_VehicleBackward()));
     connect( &(this->teleoperation), SIGNAL(signal_vehicleControlStop()), SLOT (teleoperationWidget_VehicleStop()));
     connect( &(this->teleoperation), SIGNAL(signal_vehicleControlStart()), SLOT (teleoperationWidget_VehicleStart()));
     connect( &(this->teleoperation), SIGNAL(signal_vehicleControlHorn()), SLOT (teleoperationWidget_VehicleHorn()));
     connect( &(this->teleoperation), SIGNAL(signal_vehicleControlLight()), SLOT (teleoperationWidget_VehicleLight()));

}

void MainWindow::initUi()
{
    ui->setupUi(this);
    this->setWindowTitle("物流配送监控");
    timer = new QTimer();
    timer->start(1000);
    timer_mapRefresh = new QTimer();
    timer_mapRefresh->start(5000);
    //加载百度地图
    ui->webView->settings()->setAttribute(QWebSettings::JavascriptEnabled,true);//使能javascript
    ui->webView->settings()->setAttribute(QWebSettings::PluginsEnabled,true);//Qt窗口部件嵌入到网页
    addJavaScriptObject();
    ui->webView->setUrl(QUrl("file:///home/zlp/qt_test/test1/htmlapi/baiduapi.html"));
    ui->webView->show();
    //设置背景颜色
    this->setAutoFillBackground(true);//这个语句很重要，没有的话，子widget背景色修改不成功
    QPalette myPalette;
    myPalette.setBrush(backgroundRole(),QColor(10,20,35));
    this->setPalette(myPalette);
    //设置信息显示框的透明度，字体颜色
    ui->tabWidget->setStyleSheet("QTabWidget:pane {border-top:0px solid #e8f3f9;background:  transparent; }"
                                 "QTabBar::tab { height: 30px; width:90px;background-color:rgb(20,20,20); color: rgb(230,230,255);   border-radius: 1px; }"
                                 "QTabBar::tab:selected { background-color:rgb(125, 125, 125);   border: rgb(15 , 150 , 255); padding-left:-1px;  padding-top:-1px } ");
    ui->tabWidget->setCurrentIndex(0);
    ui->textBrowser_task->setStyleSheet("background-color:rgba(50,50,50,80)");
    ui->textBrowser_task->setTextColor(TEXT_COLOR);
    ui->textBrowser_task->setText( QString (""));
    ui->textBrowser_parcel->setStyleSheet("background-color:rgba(50,50,50,80)");
    ui->textBrowser_parcel->setTextColor(TEXT_COLOR);
    ui->textBrowser_parcel->setText( QString ("包裹信息"));

    ui->tabWidget_2->setStyleSheet("QTabWidget:pane {border-top:0px solid #e8f3f9;background:  transparent; }"
                                   "QTabBar::tab { height: 30px; width:80px;background-color:rgb(20,20,20); color: rgb(230,230,255);   border-radius: 1px; }"
                                   "QTabBar::tab:selected { background-color:rgb(125, 125, 125);   border: rgb(15 , 150 , 255); padding-left:-1px;  padding-top:-1px } ");
    ui->tabWidget_2->setCurrentIndex(0);
    ui->textBrowser_vehicle->setStyleSheet("background-color:rgba(50,50,50,80)");
    ui->textBrowser_vehicle->setTextColor(TEXT_COLOR);
    ui->textBrowser_vehicle->setText( QString("车辆信息"));
    ui->textBrowser_road->setStyleSheet("background-color:rgba(50,50,50,80)");
    ui->textBrowser_road->setTextColor(TEXT_COLOR);
    ui->textBrowser_road->setText(QString ("路况信息"));
    ui->textBrowser_system->setStyleSheet("background-color:rgba(50,50,50,80)");
    ui->textBrowser_system->setTextColor(TEXT_COLOR);
    ui->textBrowser_system->setText(QString ("系统信息"));


    //设置按钮风格
    QString button_style="QPushButton{background-color:rgb(20,20,20); color: rgb(230,230,255);   border-radius: 2px;  border: 1px solid rgb(183 , 183 , 183);}"
                                         "QPushButton:hover{background-color:rgb(40,40,40); color: rgb(230,230,255);  border: 1px solid rgb(15 , 150 , 255);}"
                                        "QPushButton:pressed{background-color:rgb(30, 30, 30);    border: 1px solid rgb(15 , 150 , 255); padding-left:1px;  padding-top:1px;}";
    ui->button_cameraSet->setStyleSheet(button_style);
    ui->button_cameraSet->setFocusPolicy(Qt::NoFocus);
    ui->button_operationExchange->setStyleSheet(button_style);
    ui->button_operationExchange->setFocusPolicy(Qt::NoFocus);
    ui->button_parcelQuery->setStyleSheet(button_style);
    ui->button_parcelQuery->setFocusPolicy(Qt::NoFocus);
    ui->button_sysRestart->setStyleSheet(button_style);
    ui->button_sysRestart->setFocusPolicy(Qt::NoFocus);
    ui->button_taskQuery->setStyleSheet(button_style);
    ui->button_taskQuery->setFocusPolicy(Qt::NoFocus);
    ui->button_taskSet->setStyleSheet(button_style);
    ui->button_taskSet->setFocusPolicy(Qt::NoFocus);
    //设置弹出窗口的位置（在屏幕中央）
    QDesktopWidget *deskdop=QApplication::desktop();
    this->move((deskdop->width()-this->width())/2,(deskdop->height()-this->height())/2);


}
//JavaScript和Qt对象交互
void MainWindow::addJavaScriptObject()
{
    //myRobot->taskPointCluster.pop_back();
    myRobot->getVehicelCoor();
    //将本地的QObject对象暴露给webkit和JavaScript,javascript可以通过对象名***,访问***对象。
    //JavaScript调用Qt对象
    this->ui->webView->page()->mainFrame()->addToJavaScriptWindowObject(QString("myRobot"),this->myRobot);
    //Qt对象调用JavaScript
    this->ui->webView->page()->mainFrame()->evaluateJavaScript("taskPathRefresh();");
}
void MainWindow::showTime()
{
    //获取系统时间
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式
    QPalette fontColor;
    fontColor.setColor(QPalette::WindowText, Qt::white);
    ui->label_time->setPalette(fontColor);
    ui->label_time->setText(str);//在标签上显示时间
}
//子窗口设置
void MainWindow::on_button_operationExchange_clicked()
{
    teleoperation.show();
    //this->close();
}
void MainWindow::on_button_cameraSet_clicked()
{
    cameraSetWidget.show();
}
void MainWindow::on_button_taskQuery_clicked()
{
    taskQueryWidget.show();
}
void MainWindow::on_button_parcelQuery_clicked()
{
    parcelQueryWidget.show();
}


void MainWindow::on_button_taskSet_clicked()
{
    taskSetWidget.show();
}

void MainWindow::on_button_sysRestart_clicked()
{

}
 //不同类对象之间通信
void MainWindow::teleoperationWidget_TaskAskShow()
{
    taskQueryWidget.show();
}
void MainWindow::teleoperationWidget_BoxAskShow()
{
    boxInfoWidget.show();
}
void MainWindow::teleoperationWidget_VehicleAskShow()
{
    vehicleInfoWidget.show();
}

void MainWindow::teleoperationWidget_VehicleTurnLeft()
{

}
void MainWindow::teleoperationWidget_VehicleTurnRight()
{

}
void MainWindow::teleoperationWidget_VehicleForward()
{

}
void MainWindow::teleoperationWidget_VehicleBackward()
{

}
void MainWindow::teleoperationWidget_VehicleStop()
{

}
void MainWindow::teleoperationWidget_VehicleStart()
{

}
void MainWindow::teleoperationWidget_VehicleHorn()
{

}void MainWindow::teleoperationWidget_VehicleLight()
{

}

