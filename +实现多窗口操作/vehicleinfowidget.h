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
    Ui::VehicleInfoWidget *ui;
};

#endif // VEHICLEINFOWIDGET_H
