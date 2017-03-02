#include "camerasetwidget.h"
#include "ui_camerasetwidget.h"

CameraSetWidget::CameraSetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraSetWidget)
{
    ui->setupUi(this);
}

CameraSetWidget::~CameraSetWidget()
{
    delete ui;
}
