#ifndef NEWORDERINFOWIDGET_H
#define NEWORDERINFOWIDGET_H

#include <QWidget>

namespace Ui {
class NewOrderInfoWidget;
}

class NewOrderInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NewOrderInfoWidget(QWidget *parent = 0);
    ~NewOrderInfoWidget();
    void initUi();//初始化界面参数
    void initConnect();//初始化信号和槽连接
private:
    Ui::NewOrderInfoWidget *ui;
};

#endif // NEWORDERINFOWIDGET_H
