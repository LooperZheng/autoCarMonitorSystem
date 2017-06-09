#ifndef CAMERASETWIDGET_H
#define CAMERASETWIDGET_H

#include <QWidget>
#include <QString>
#include <QFile>
namespace Ui {
class CameraSetWidget;
}

class CameraSetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CameraSetWidget(QWidget *parent = 0);
    ~CameraSetWidget();
private:
    void initUi();
     void initConnect();//初始化信号和槽连接
    // QString mimeReturn(const QFile& file);
private slots:
     void stop_display();
     void on_pushButton_play_clicked();
     void on_pushButton_select_clicked();
    // void addJavaScriptObject();
private:
    Ui::CameraSetWidget *ui;
    bool * pauseVedio;
    QString vedioHtmlUrl;

};

#endif // CAMERASETWIDGET_H
