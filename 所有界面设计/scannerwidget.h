#ifndef SCANNERWIDGET_H
#define SCANNERWIDGET_H

#include <QWidget>
#include <QtMultimedia>

namespace Ui {
class ScannerWidget;
}

class ScannerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScannerWidget(QWidget *parent = 0);
    ~ScannerWidget();
private:
    void initUi();//初始化界面参数
    void initConnect();//初始化信号和槽连接

public slots:
    void on_pushButton_start_clicked();
    void on_pushButton_end_clicked();
    void on_pushButton_audio_clicked();
    void on_pushButton_noAudio_clicked();

    void playAudio(int index);
private:
    Ui::ScannerWidget *ui;
    QMediaPlayer* audioPlayer;
    int i;
};

#endif // SCANNERWIDGET_H
