#ifndef PARCELQUERYWIDGET_H
#define PARCELQUERYWIDGET_H

#include <QWidget>

namespace Ui {
class ParcelQueryWidget;
}

class ParcelQueryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ParcelQueryWidget(QWidget *parent = 0);
    ~ParcelQueryWidget();

private:
    Ui::ParcelQueryWidget *ui;
};

#endif // PARCELQUERYWIDGET_H
