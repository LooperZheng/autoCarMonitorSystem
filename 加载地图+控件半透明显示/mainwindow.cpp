#include "mainwindow.h"
#include "ui_mainwindow.h"
#define TEXT_COLOR  QColor(100,200,220)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui=new Ui::MainWindow();
    myRobot=new Robot(this);

    initUi();//初始化界面参数
    initConnect();//初始化信号和槽连接
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initConnect()
{
     connect(ui->webView->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),this, SLOT(addJavaScriptObject()));//地图刷新调取
     //connect(ui->,SIGNAL(clicked()),this->myGrdStn,SLOT(setCruise()));//开始巡航
}

void MainWindow::initUi()
{
    ui->setupUi(this);

    //加载百度地图
    ui->webView->settings()->setAttribute(QWebSettings::JavascriptEnabled,true);//使能javascript
    ui->webView->settings()->setAttribute(QWebSettings::PluginsEnabled,true);
    addJavaScriptObject();
    ui->webView->setUrl(QUrl("file:///home/zlp/qt_test/test1/htmlapi/baiduapi.html"));
    ui->webView->show();
    //设置背景颜色
    this->setAutoFillBackground(true);//这个语句很重要，没有的话，子widget背景色修改不成功
    QPalette myPalette;
    myPalette.setBrush(backgroundRole(),QColor(10,20,35));
    this->setPalette(myPalette);
    //设置信息显示框的透明度，字体颜色
    ui->tabWidget->setStyleSheet("QTabWidget:pane {border-top:0px solid #e8f3f9;background:  transparent; }");
    ui->textBrowser_task->setStyleSheet("background-color:rgba(255,255,255,80)");
    ui->textBrowser_task->setTextColor(TEXT_COLOR);
    ui->textBrowser_task->setText( QString (""));
    ui->textBrowser_parcel->setStyleSheet("background-color:rgba(255,255,255,80)");
    ui->textBrowser_parcel->setTextColor(TEXT_COLOR);
    ui->textBrowser_parcel->setText( QString ("包裹信息"));

    ui->tabWidget_2->setStyleSheet("QTabWidget:pane {border-top:0px solid #e8f3f9;background:  transparent; }");
    ui->textBrowser_vehicle->setStyleSheet("background-color:rgba(255,255,255,80)");
    ui->textBrowser_vehicle->setTextColor(TEXT_COLOR);
    ui->textBrowser_vehicle->setText( QString("车辆信息"));
    ui->textBrowser_road->setStyleSheet("background-color:rgba(255,255,255,80)");
    ui->textBrowser_road->setTextColor(TEXT_COLOR);
    ui->textBrowser_road->setText(QString ("路况信息"));
    ui->textBrowser_system->setStyleSheet("background-color:rgba(255,255,255,80)");
    ui->textBrowser_system->setTextColor(TEXT_COLOR);
    ui->textBrowser_system->setText(QString ("系统信息"));
}
//JavaScript调用Qt对象
void MainWindow::addJavaScriptObject()
{
    //将本地的QObject对象暴露给webkit和JavaScript,javascript可以通过对象名***,访问***对象。
    this->ui->webView->page()->mainFrame()->addToJavaScriptWindowObject(QString("myRobot"),this);
}

