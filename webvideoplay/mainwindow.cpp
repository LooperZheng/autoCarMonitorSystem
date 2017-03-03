#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>
#include <QProcess>
#include <QScrollBar>
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>
#include <QWebView>
#include <QTextStream>
#include <QMimeDatabase>
#include <QMimeType>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
 void MainWindow::on_pushButton_play_clicked()
 {
     QString videoFilePath = ui->playerEdit->text();
     QString htmlFilePath = "/home/zlp/qt_test/webvideoplay/t.html";

     QFile file(htmlFilePath);
     if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
         return;
     }

     QString mimetype = mimeReturn(videoFilePath);
     QTextStream stream(&file);

     stream << "<html>"<< "\n";
     stream << "<video width=\"480\" height=\"270\" controls autoplay>"<< "\n";
     stream << "<source src="
            << "\"" << videoFilePath << "\" " << "type=\""
            << mimetype << "\"> \n";
     stream << "</video>"<< "\n";
     stream << "</html>"<< "\n";

     htmlUrl = "file:///" + htmlFilePath;

     ui->webView->load(htmlUrl);
 }

QString MainWindow::mimeReturn(const QFile& file)
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
 void MainWindow::on_pushButton_replay_clicked()
 {
         ui->webView->load(htmlUrl);
 }
void MainWindow::on_pushButton_select_clicked()
{
    QString fileName =
        QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "/home/zlp/qt_test/ffmpeg",
                tr("videoss (*.mp4 *.mov *.avi *webm *.mkv *.flv)"));
    if (!fileName.isEmpty()) {
        ui->playerEdit->setText(fileName);
    }
}
