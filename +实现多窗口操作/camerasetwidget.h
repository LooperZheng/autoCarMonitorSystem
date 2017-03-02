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
    Ui::CameraSetWidget *ui;
};

#endif // CAMERASETWIDGET_H
