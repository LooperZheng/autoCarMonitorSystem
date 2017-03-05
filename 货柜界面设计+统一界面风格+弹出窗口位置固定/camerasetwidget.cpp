#include "camerasetwidget.h"
#include "ui_camerasetwidget.h"
#include <QDesktopWidget>
CameraSetWidget::CameraSetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraSetWidget)
{
    ui->setupUi(this);
    initUi();//初始化界面参数
    initConnect();//初始化信号和槽连接
}

CameraSetWidget::~CameraSetWidget()
{
    delete ui;
}
void CameraSetWidget::initConnect()
{
    connect(ui->pushButton,SIGNAL(clicked()), this,SLOT(stop_display()));
}
void CameraSetWidget::stop_display()
{
    this->close();
}
void CameraSetWidget::initUi()
{
    this->setWindowTitle("相机监控界面");
    //设置弹出窗口的位置（在屏幕中央）
    QDesktopWidget *deskdop=QApplication::desktop();
    this->move((deskdop->width()-this->width())/2,      (deskdop->height()-this->height())/2);
    //设置背景颜色和按钮风格
    this->setAutoFillBackground(true);//这个语句很重要，没有的话，子widget背景色修改不成功
    QPalette myPalette;
    myPalette.setBrush(backgroundRole(),QColor(10,20,35));
    this->setPalette(myPalette);
    QString button_style="QPushButton{background-color:rgb(20,20,20); color: rgb(230,230,255);   border-radius: 2px;  border: 1px solid rgb(183 , 183 , 183);}"
                                         "QPushButton:hover{background-color:rgb(40,40,40); color: rgb(230,230,255);  border: 1px solid rgb(15 , 150 , 255);}"
                                        "QPushButton:pressed{background-color:rgb(30, 30, 30);    border: 1px solid rgb(15 , 150 , 255); padding-left:1px;  padding-top:1px;}";
    ui->pushButton->setStyleSheet(button_style);
    ui->pushButton->setFocusPolicy(Qt::NoFocus);
    //设置每个webview的背景颜色
    ui->webView_backCamera->setStyleSheet("background-color:rgb(40,40,40); padding: 7px ; color:rgb(255,255,255)");
    ui->webView_frontCamera->setStyleSheet("background-color:rgb(40,40,40); padding: 7px ; color:rgb(255,255,255)");
    ui->webView_leftCamera->setStyleSheet("background-color:rgb(40,40,40); padding: 7px ; color:rgb(255,255,255)");
    ui->webView_rightCamera->setStyleSheet("background-color:rgb(40,40,40); padding: 7px ; color:rgb(255,255,255)");
    ui->webView_leftMoniCamera->setStyleSheet("background-color:rgb(40,40,40); padding: 7px ; color:rgb(255,255,255)");
    ui->webView_rightMoniCamera->setStyleSheet("background-color:rgb(40,40,40); padding: 7px ; color:rgb(255,255,255)");
    ui->webView_map ->setStyleSheet("background-color:rgb(40,40,40); padding: 7px ; color:rgb(255,255,255)");
    ui->webView_vedioPlay ->setStyleSheet("background-color:rgb(40,40,40); padding: 7px ; color:rgb(255,255,255)");

    //加载视频
    QString leftCameraHtmlUrl = "file:///home/zlp/qt_test/test1/vediohtml/leftcamera.html";
    ui->webView_leftCamera->load(leftCameraHtmlUrl);

    QString frontCameraHtmlUrl = "file:///home/zlp/qt_test/test1/vediohtml/frontcamera.html";
    ui->webView_frontCamera->load(frontCameraHtmlUrl);

    QString rightCmeraHtmlUrl = "file:///home/zlp/qt_test/test1/vediohtml/rightcamera.html";
    ui->webView_rightCamera->load(rightCmeraHtmlUrl);

    QString backCameraHtmlUrl = "file:///home/zlp/qt_test/test1/vediohtml/backcamera.html";
    ui->webView_backCamera->load(backCameraHtmlUrl);

    QString leftMoniCameraHtmlUrl = "file:///home/zlp/qt_test/test1/vediohtml/leftmonicamera.html";
    ui->webView_leftMoniCamera->load(leftMoniCameraHtmlUrl);

    QString rightMoniCameraHtmlUrl = "file:///home/zlp/qt_test/test1/vediohtml/rightmonicamera.html";
    ui->webView_rightMoniCamera->load(rightMoniCameraHtmlUrl);


}
