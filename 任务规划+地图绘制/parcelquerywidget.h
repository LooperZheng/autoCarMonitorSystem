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
    void initUi();//初始化界面参数
    void initConnect();//初始化信号和槽连接
    bool checkParcelNum(QString);
    bool isParcelExist(QString);
private slots:
    void on_pushButton_parcelQuery_clicked();

private:
    Ui::ParcelQueryWidget *ui;
};

#endif // PARCELQUERYWIDGET_H
