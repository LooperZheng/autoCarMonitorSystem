#include "mainwindow.h"
#include "ui_mainwindow.h"

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
}

//JavaScript调用Qt对象
void MainWindow::addJavaScriptObject()
{
    //将本地的QObject对象暴露给webkit和JavaScript,javascript可以通过对象名***,访问***对象。
    this->ui->webView->page()->mainFrame()->addToJavaScriptWindowObject(QString("myRobot"),this);
}

