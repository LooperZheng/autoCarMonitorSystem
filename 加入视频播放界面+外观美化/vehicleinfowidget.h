#ifndef VEHICLEINFOWIDGET_H
#define VEHICLEINFOWIDGET_H

#include <QWidget>

namespace Ui {
class VehicleInfoWidget;
}

class VehicleInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VehicleInfoWidget(QWidget *parent = 0);
    ~VehicleInfoWidget();
private:
    void initUi();//初始化界面参数
    void initConnect();//初始化信号和槽连接
private:
    Ui::VehicleInfoWidget *ui;
};

#endif // VEHICLEINFOWIDGET_H
