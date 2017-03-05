#ifndef CAMERASETWIDGET_H
#define CAMERASETWIDGET_H

#include <QWidget>

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
private slots:
     void stop_display();
    // void addJavaScriptObject();
private:
    Ui::CameraSetWidget *ui;
    bool * pauseVedio;
};

#endif // CAMERASETWIDGET_H
