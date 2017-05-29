#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <string>
#include <vector>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>
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
    delete myRobot;
}

void MainWindow::initData()
{
    myRobot->getPathPointFromTopoMap();
    myRobot->getPathMapFromTopoMap();
    myRobot->getTaskSeqFromLogisticDB();



//    result res = myRobot->executeTaskPlan();
//    myRobot->sendMessageToVehicle();

//    //dispaly
//    cout<<"is Valid = "<<res.isValid<<endl;
//    cout<<"dis = "<<res.dis<<endl;
//    cout<<"node Num = "<<res.path.size()<<endl;
//    for(int i=0; i<res.path.size();i++)
//    {
//        cout<<res.path[i]<<" ";
//    }
//    cout<<endl;

}
void MainWindow::initConnect()
{
     //在跨页面的时候，该对象会被清除，所以要重新加回来
     //这一点跟GTK类似， 只要捕获WindowObjectCleared信号，在该信号处理函数里面执行addToJavaScriptWindowObject()
     connect(ui->webView->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),this, SLOT(addJavaScriptObject()));//地图刷新调取
     QObject::connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
     QObject::connect(timer_mapRefresh,SIGNAL(timeout()),this,SLOT(refreshBaiduMapVehicle()));

     QObject::connect(timer_InfoRefresh,SIGNAL(timeout()),this,SLOT(showVehicleInfo()));
     QObject::connect(timer_InfoRefresh,SIGNAL(timeout()),this,SLOT(showSysInfo()));
     QObject::connect(timer_InfoRefresh,SIGNAL(timeout()),this,SLOT(showRoadInfo()));
     QObject::connect(timer_InfoRefresh,SIGNAL(timeout()),this,SLOT(showTaskInfo()));
     QObject::connect(timer_InfoRefresh,SIGNAL(timeout()),this,SLOT(showParcelInfo()));

     //不同类对象之间通信
     connect( &(this->teleoperation), SIGNAL(signal_showTaskQueryWidget()), this,SLOT (teleoperationWidget_TaskAskShow()));
     connect( &(this->teleoperation), SIGNAL(signal_showBoxQueryWidget()), this,SLOT (teleoperationWidget_BoxAskShow()));
     connect( &(this->teleoperation), SIGNAL(signal_showVehicleQueryWidget()), this,SLOT (teleoperationWidget_VehicleAskShow()));

     connect( &(this->teleoperation), SIGNAL(signal_vehicleControlTurnLeft()), this,SLOT (teleoperationWidget_VehicleTurnLeft()));
     connect( &(this->teleoperation), SIGNAL(signal_vehicleControlTurnRight()), this,SLOT (teleoperationWidget_VehicleTurnRight()));
     connect( &(this->teleoperation), SIGNAL(signal_vehicleControlTurnForward()), this,SLOT (teleoperationWidget_VehicleForward()));
     connect( &(this->teleoperation), SIGNAL(signal_vehicleControlTurnBackward()), this,SLOT (teleoperationWidget_VehicleBackward()));
     connect( &(this->teleoperation), SIGNAL(signal_vehicleControlStop()), this,SLOT (teleoperationWidget_VehicleStop()));
     connect( &(this->teleoperation), SIGNAL(signal_vehicleControlStart()), this,SLOT (teleoperationWidget_VehicleStart()));
     connect( &(this->teleoperation), SIGNAL(signal_vehicleControlHorn()), this,SLOT (teleoperationWidget_VehicleHorn()));
     connect( &(this->teleoperation), SIGNAL(signal_vehicleControlLight()), this,SLOT (teleoperationWidget_VehicleLight()));
     connect( &(this->teleoperation), SIGNAL(signal_vehicleControlLightClose()), this,SLOT (teleoperationWidget_VehicleLightClose()));
     connect( &(this->teleoperation), SIGNAL(signal_operationExchange()), this,SLOT (teleoperationWidget_OperationExchange()));

     connect( &(this->taskSetWidget), SIGNAL(signal_startTaskPlan(std::vector<int>)), this,SLOT (taskSetWidget_startTaskPlan(std::vector<int>)));

     connect( &(this->boxInfoWidget), SIGNAL(signal_openBox(std::vector<int>)), this,SLOT (boxInfoWidget_openBox(std::vector<int>)));

     connect( this->myRobot, SIGNAL(signal_getCurrentTaskID()), this,SLOT(refreshBaiduMapTask()));
     connect( this->myRobot, SIGNAL(signal_completeAllTask()), this,SLOT(refreshBaiduMapAll()));

}

void MainWindow::initUi()
{
    ui->setupUi(this);
    this->setWindowTitle("物流配送监控");
    // 固定窗口的大小
    this->setFixedSize(this->width(), this->height());

    timer = new QTimer();
    timer->start(1000);
    timer_mapRefresh = new QTimer();
    timer_InfoRefresh = new QTimer();

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
    ui->textBrowser_task->setText( QString ("物流信息"));
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
    ui->button_scanner->setStyleSheet(button_style);
    ui->button_scanner->setFocusPolicy(Qt::NoFocus);
    ui->button_monitorStart->setStyleSheet(button_style);
    ui->button_monitorStart->setFocusPolicy(Qt::NoFocus);
    ui->button_remainingHandle->setStyleSheet(button_style);
    ui->button_remainingHandle->setFocusPolicy(Qt::NoFocus);
    ui->button_vehicleStart->setStyleSheet(button_style);
    ui->button_vehicleStart->setFocusPolicy(Qt::NoFocus);
    //设置弹出窗口的位置（在屏幕中央）
    QDesktopWidget *deskdop=QApplication::desktop();
    this->move((deskdop->width()-this->width())/2,(deskdop->height()-this->height())/2);

}
//JavaScript和Qt对象交互
void MainWindow::addJavaScriptObject()
{
    //将本地的QObject对象暴露给webkit和JavaScript,javascript可以通过对象名***,访问***对象。
    //JavaScript调用Qt对象
    //qDebug()<<"addJavaScriptObject";
    this->ui->webView->page()->mainFrame()->addToJavaScriptWindowObject(QString("myRobot"),this->myRobot);

}
void MainWindow::refreshBaiduMapAll()
{
    qDebug()<<"refreshBaiduMapAll";
    //Qt对象调用JavaScript
    QTime time;
    time.start();

    this->ui->webView->page()->mainFrame()->evaluateJavaScript("refreshDataAll();");
    int time_Diff = time.elapsed();
    qDebug()<<time_Diff;
}
void MainWindow::refreshBaiduMapVehicle()
{
    myRobot->getVehicelCoor();
    this->ui->webView->page()->mainFrame()->evaluateJavaScript("refreshDataVehicle();");
}
void MainWindow::refreshBaiduMapTask()
{
    qDebug()<<"refreshBaiduMapTask";
    this->ui->webView->page()->mainFrame()->evaluateJavaScript("refreshDataTask();");
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
    teleoperation.setSysState();

    ui->textBrowser_systemState ->setTextColor(QColor(255,0,0));
    ui->textBrowser_systemState->setText("已切换至手动驾驶...");
    ui->textBrowser_systemState->setTextColor(QColor(0,0,0));
    //send message
    Json::Value root;
    Json::FastWriter fast;
    root["Name"]=("operation_exchange");
    root["Cmd"]=("teleoperation");
    std::string str=fast.write(root) ;
    this->myRobot->tcpIpSever.sendMessage(str);
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
    //just text 6.6
    this->taskSetWidget.gettaskseq(this->myRobot->taskSeq);

    taskSetWidget.show();
}

void MainWindow::on_button_sysRestart_clicked()
{
    ui->textBrowser_systemState ->setTextColor(QColor(255,0,0));
    ui->textBrowser_systemState->setText("系统重启...");
    ui->textBrowser_systemState->setTextColor(QColor(0,0,0));

    //send message
    Json::Value root;
    Json::FastWriter fast;
    root["Name"]=("device_control");
    root["Cmd"]=("restart");
    std::string str=fast.write(root) ;
    this->myRobot->tcpIpSever.sendMessage(str);
}
void MainWindow::on_button_monitorStart_clicked()
{
    ui->textBrowser_systemState ->setTextColor(QColor(255,0,0));
    ui->textBrowser_systemState->setText("监控开始...");
    ui->textBrowser_systemState->setTextColor(QColor(0,0,0));

    refreshBaiduMapAll();

    timer_mapRefresh->start(1000);
    timer_InfoRefresh->start(2000);
}
void MainWindow::on_button_scanner_clicked()
{
    scannerWidget.show();
}
void MainWindow::on_button_remainingHandle_clicked()
{
    remainingParcelWidget.show();
}
void MainWindow::on_button_vehicleStart_clicked()
{
    //just test
//    rejectionWidget.show();
//    messageWidget.show();

    ui->textBrowser_systemState ->setTextColor(QColor(255,0,0));
    ui->textBrowser_systemState->setText("车辆启动...");
    ui->textBrowser_systemState->setTextColor(QColor(0,0,0));
    //send message
    Json::Value root;
    Json::FastWriter fast;
    root["Name"]=("vehicle_start");
    root["Cmd"]=("start");
    std::string str=fast.write(root) ;
    this->myRobot->tcpIpSever.sendMessage(str);
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
    Json::Value root;
    Json::FastWriter fast;
    root["Name"]=("vehicle_control");
    root["Cmd"]=("turn_left");
    std::string str=fast.write(root) ;
    this->myRobot->tcpIpSever.sendMessage(str);
}
void MainWindow::teleoperationWidget_VehicleTurnRight()
{
    Json::Value root;
    Json::FastWriter fast;
    root["Name"]=("vehicle_control");
    root["Cmd"]=("turn_right");
    std::string str=fast.write(root) ;
    this->myRobot->tcpIpSever.sendMessage(str);
}
void MainWindow::teleoperationWidget_VehicleForward()
{
    Json::Value root;
    Json::FastWriter fast;
    root["Name"]=("vehicle_control");
    root["Cmd"]=("forward");
    std::string str=fast.write(root) ;
    this->myRobot->tcpIpSever.sendMessage(str);
}
void MainWindow::teleoperationWidget_VehicleBackward()
{
    Json::Value root;
    Json::FastWriter fast;
    root["Name"]=("vehicle_control");
    root["Cmd"]=("backward");
    std::string str=fast.write(root) ;
    this->myRobot->tcpIpSever.sendMessage(str);
}
void MainWindow::teleoperationWidget_VehicleStop()
{
    Json::Value root;
    Json::FastWriter fast;
    root["Name"]=("vehicle_control");
    root["Cmd"]=("stop");
    std::string str=fast.write(root) ;
    this->myRobot->tcpIpSever.sendMessage(str);
}
void MainWindow::teleoperationWidget_VehicleStart()
{
    Json::Value root;
    Json::FastWriter fast;
    root["Name"]=("vehicle_control");
    root["Cmd"]=("start");
    std::string str=fast.write(root) ;
    this->myRobot->tcpIpSever.sendMessage(str);
}
void MainWindow::teleoperationWidget_VehicleHorn()
{
    Json::Value root;
    Json::FastWriter fast;
    root["Name"]=("vehicle_control");
    root["Cmd"]=("horn");
    std::string str=fast.write(root) ;
    this->myRobot->tcpIpSever.sendMessage(str);
}
void MainWindow::teleoperationWidget_VehicleLight()
{
    Json::Value root;
    Json::FastWriter fast;
    root["Name"]=("vehicle_control");
    root["Cmd"]=("light_open");
    std::string str=fast.write(root) ;
    this->myRobot->tcpIpSever.sendMessage(str);
}
void MainWindow::teleoperationWidget_VehicleLightClose()
{
    Json::Value root;
    Json::FastWriter fast;
    root["Name"]=("vehicle_control");
    root["Cmd"]=("light_close");
    std::string str=fast.write(root) ;
    this->myRobot->tcpIpSever.sendMessage(str);
}

void MainWindow::teleoperationWidget_OperationExchange()
{
    Json::Value root;
    Json::FastWriter fast;
    root["Name"]=("operation_exchange");
    root["Cmd"]=("auto");
    std::string str=fast.write(root) ;
    this->myRobot->tcpIpSever.sendMessage(str);

    ui->textBrowser_systemState ->setTextColor(QColor(255,0,0));
    ui->textBrowser_systemState->setText("已切换至自动驾驶...");
    ui->textBrowser_systemState->setTextColor(QColor(0,0,0));
}

void MainWindow::taskSetWidget_startTaskPlan(std::vector<int> taskSeq)
{
    //for test
    this->myRobot->taskSeq.clear();
    this->myRobot->taskSeq = taskSeq;
    this->myRobot->taskPointCluster.clear();
    for(int i =0;i<taskSeq.size();i++)
    {
        int taskID = taskSeq[i];
        QString taskInfo;
        taskInfo = "task " + QString::number(taskID);
        taskPoint taskPointTmp;
        taskPointTmp.ID = taskID;
        taskPointTmp.longitude = myRobot->pathPointID2Coordinate[taskID].first;
        taskPointTmp.latitude = myRobot->pathPointID2Coordinate[taskID].second;
        taskPointTmp.taskInfo = taskInfo;
        myRobot->taskPointCluster.push_back(taskPointTmp);
    }

    result res = myRobot->executeTaskPlan();
    myRobot->sendMessageToVehicle();

    //dispaly
    cout<<"is Valid = "<<res.isValid<<endl;
    cout<<"dis = "<<res.dis<<endl;
    cout<<"node Num = "<<res.path.size()<<endl;
    for(int i=0; i<res.path.size();i++)
    {
        cout<<res.path[i]<<" ";
    }
    cout<<endl;

    this->taskSetWidget.TaskPlanInfoShow(res);
}
void MainWindow::boxInfoWidget_openBox(std::vector<int> boxIndex)
{
    Json::Value root;
    Json::Value boxArry;
    Json::FastWriter fast;
    root["Name"]=("device_control");
    for(int i=0; i<20; i++)
    {
        if(std::find(boxIndex.begin(), boxIndex.end(), i) != boxIndex.end())
            boxArry.append("1");
        else
            boxArry.append("0");
    }

    root["Box_Info"]=boxArry;
//    string out = root.toStyledString();
//    cout<<out<<std::endl;
    std::string str=fast.write(root) ;
    this->myRobot->tcpIpSever.sendMessage(str);
}

//mainwidow上的左上和右上显示框内容更新
void MainWindow::showVehicleInfo()
{
    ui->textBrowser_vehicle->setTextColor(TEXT_COLOR);
    QString text;
    text.append("车辆编号 : ");
    text.append( QString::number(this->myRobot->carInfo.num) );
    text.append("\n");
    text.append("车辆位置 : ");
    text.append("\n");
    text.append("车辆速度 : ");
    text.append("\n");
    text.append("行驶里程 : ");
    text.append("\n");
    text.append("剩余里程 : ");
    text.append("\n");
    text.append("电量显示 : ");
    text.append("\n");
    text.append("车辆状态 : ");
    ui->textBrowser_vehicle->setText(text);
}
void MainWindow::showRoadInfo()
{
    ui->textBrowser_road->setTextColor(TEXT_COLOR);
    QString text;
    text.append("道路通行状态 : ");
    text.append(QString::number(this->myRobot->roadInfo.passable));
    text.append("\n");

    text.append("超声波_1 : ");
    text.append("\n");
    text.append("超声波_2 : ");
    text.append("\n");
    text.append("超声波_3 : ");
    text.append("\n");
    text.append("超声波_4 : ");
    text.append("\n");
    text.append("超声波_5 : ");
    text.append("\n");
    text.append("超声波_6 : ");
    text.append("\n");
    text.append("超声波_7 : ");
    text.append("\n");
    text.append("超声波_8 : ");

    ui->textBrowser_road->setText(text);
}
void MainWindow::showSysInfo()
{
    ui->textBrowser_system->setTextColor(TEXT_COLOR);
    QString text;
    text.append("通信状态 : ");
    text.append(QString::number(this->myRobot->sysInfo.communicationState));

    ui->textBrowser_system->setText(text);
}
void MainWindow::showTaskInfo()
{
    ui->textBrowser_task->setTextColor(TEXT_COLOR);
    QString text;

    ui->textBrowser_task->setText( QString ("task info"));
}
void MainWindow::showParcelInfo()
{
    ui->textBrowser_parcel->setTextColor(TEXT_COLOR);
    QString text;

    ui->textBrowser_parcel->setText( QString ("parcel info"));
}
