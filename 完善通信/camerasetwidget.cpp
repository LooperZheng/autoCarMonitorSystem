#include "camerasetwidget.h"
#include "ui_camerasetwidget.h"
#include <QDesktopWidget>
#include <QFileDialog>
#include <QTextStream>
#include <QMimeDatabase>
#include <QMimeType>
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
    //ui->webView_frontCamera->setDisabled(true);
}
void CameraSetWidget::initUi()
{
    // 固定窗口的大小
    this->setFixedSize(this->width(), this->height());

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
    QString button_style_gridlaout="QPushButton{height: 28px; width:90px; background-color:rgb(20,20,20); color: rgb(230,230,255);   border-radius: 2px;  border: 1px solid rgb(183 , 183 , 183);}"
                                         "QPushButton:hover{background-color:rgb(40,40,40); color: rgb(230,230,255);  border: 1px solid rgb(15 , 150 , 255);}"
                                        "QPushButton:pressed{background-color:rgb(30, 30, 30);    border: 1px solid rgb(15 , 150 , 255); padding-left:1px;  padding-top:1px;}";
       ui->pushButton_play->setStyleSheet(button_style_gridlaout);
    ui->pushButton_play->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_select->setStyleSheet(button_style_gridlaout);
    ui->pushButton_select->setFocusPolicy(Qt::NoFocus);
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

    QString mapHtmlUrl = "file:///home/zlp/qt_test/test1/htmlapi/baiduapi.html";
    ui->webView_map->load(mapHtmlUrl);

}

void CameraSetWidget::on_pushButton_play_clicked()
{
    QString videoFilePath = vedioHtmlUrl;
    QString htmlFilePath = "/home/zlp/qt_test/test1/playvedio.html";

    QFile file(htmlFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QString mimetype = mimeReturn(videoFilePath);
    QTextStream stream(&file);

    stream << "<html>"<< "\n";
    stream << "<video width=\"275\" height=\"205\" controls autoplay>"<< "\n";
    stream << "<source src="
           << "\"" << videoFilePath << "\" " << "type=\""
           << mimetype << "\"> \n";
    stream << "</video>"<< "\n";
    stream << "</html>"<< "\n";

    vedioHtmlUrl = "file:///" + htmlFilePath;

    ui->webView_vedioPlay->load(vedioHtmlUrl);
}

QString CameraSetWidget::mimeReturn(const QFile& file)
{
   QMimeDatabase mimeDatabase;
   QMimeType mimeType;

   mimeType = mimeDatabase.mimeTypeForFile(QFileInfo(file));

   // mp4 mpg4
   if(mimeType.inherits("video/mp4"))
       return "video/mp4";

   // mpeg mpg mpe
   else if(mimeType.inherits("video/mpeg"))
       return "video/mpeg";

   // ogv
   else if(mimeType.inherits("video/ogg"))
       return "video/ogg";

   // qt, mov
   else if(mimeType.inherits("video/quicktime"))
       return "video/quicktime";

   // avi
   else if(mimeType.inherits("video/x-msvideo"))
       return "video/x-msvideo";

   // flv
   else if (mimeType.inherits("video/x-flv"))
       return "video/x-flv";

   // webm
   else if (mimeType.inherits("video/webm"))
       return "video/webm";

   // text
   else if (mimeType.inherits("text/plain"))
       return "text";

   else
       return "";
}

void CameraSetWidget::on_pushButton_select_clicked()
{
   QString fileName =
       QFileDialog::getOpenFileName(
               this,
               tr("Open File"),
               "/home/zlp/qt_test/test1/videos",
               tr("videoss (*.mp4 *.mov *.avi *webm *.mkv *.flv)"));
   if (!fileName.isEmpty()) {
       vedioHtmlUrl = fileName;
   }
}

