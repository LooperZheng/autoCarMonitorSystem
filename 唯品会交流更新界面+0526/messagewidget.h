#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>
#include "neworderinfowidget.h"
namespace Ui {
class MessageWidget;
}

class MessageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MessageWidget(QWidget *parent = 0);
    ~MessageWidget();
    void initUi();//初始化界面参数
    void initConnect();//初始化信号和槽连接
public slots:
    void on_pushButton_msg_clicked();
    void on_pushButton_close_clicked();
private:
    Ui::MessageWidget *ui;
    NewOrderInfoWidget newOrderInfoWidget;
};

#endif // MESSAGEWIDGET_H
