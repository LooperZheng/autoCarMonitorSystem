#include "scannerwidget.h"
#include "ui_scannerwidget.h"
#include <QDesktopWidget>
ScannerWidget::ScannerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScannerWidget)
{
    ui->setupUi(this);
    audioPlayer = new QMediaPlayer;
    initUi();//初始化界面参数
    initConnect();//初始化信号和槽连接
    i=0;
}

ScannerWidget::~ScannerWidget()
{
    delete ui;
}
void ScannerWidget::initUi()
{
    // 固定窗口的大小
    this->setFixedSize(this->width(), this->height());

    this->setWindowTitle("扫描装车");
    this->setWindowOpacity(0.95);

    //设置弹出窗口的位置（在屏幕中央）
    QDesktopWidget *deskdop=QApplication::desktop();
    this->move((deskdop->width()-this->width())/2,(deskdop->height()-this->height())/2);

}
void ScannerWidget::initConnect()
{

}

void ScannerWidget::on_pushButton_start_clicked()
{
    ui->textBrowser_state->setTextColor(QColor(165,73,43));
    ui->textBrowser_state->setText("扫描开始...");
    ui->textBrowser_state->setTextColor(QColor(0,0,0));
}
void ScannerWidget::on_pushButton_end_clicked()
{
    ui->textBrowser_state->setTextColor(QColor(165,73,43));
    ui->textBrowser_state->setText("扫描停止...");
    ui->textBrowser_state->setTextColor(QColor(0,0,0));
}
void ScannerWidget::on_pushButton_audio_clicked()
{
    ui->textBrowser_state->setTextColor(QColor(165,73,43));
    ui->textBrowser_state->setText("语音播放模式...");
    ui->textBrowser_state->setTextColor(QColor(0,0,0));
    i++;
    playAudio(i);
}
void ScannerWidget::on_pushButton_noAudio_clicked()
{
    ui->textBrowser_state->setTextColor(QColor(165,73,43));
    ui->textBrowser_state->setText("禁止语音播放...");
    ui->textBrowser_state->setTextColor(QColor(0,0,0));
}
void ScannerWidget::on_pushButton_parcelQuery_clicked()
{
    ui->textBrowser_state->setTextColor(QColor(165,73,43));
    ui->textBrowser_state->setText("运单查询...");
    ui->textBrowser_state->setTextColor(QColor(0,0,0));
}
void ScannerWidget::playAudio(int index)
{
    QUrl audioSelect;
    switch (index) {
    case 0:
        audioSelect = QUrl::fromLocalFile("/home/zlp/qt_test/test1/audio/hint.mp3");
        break;
    case 1:
        audioSelect = QUrl::fromLocalFile("/home/zlp/qt_test/test1/audio/xunlei.mp3");
        break;
    case 2:
        audioSelect = QUrl::fromLocalFile("/home/zlp/qt_test/test1/audio/7820.mp3");
        break;
    case 3:
        audioSelect = QUrl::fromLocalFile("/home/zlp/qt_test/test1/audio/8407.mp3");
        break;
    default:
        audioSelect = QUrl::fromLocalFile("/home/zlp/qt_test/test1/audio/error.mp3");
        break;
    }

    audioPlayer->setMedia(audioSelect);
    audioPlayer->setVolume(100);
    audioPlayer->play();
}
