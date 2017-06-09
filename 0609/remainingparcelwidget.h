#ifndef REMAININGPARCELWIDGET_H
#define REMAININGPARCELWIDGET_H

#include <QWidget>

namespace Ui {
class RemainingParcelWidget;
}

class RemainingParcelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RemainingParcelWidget(QWidget *parent = 0);
    ~RemainingParcelWidget();
private:
    void initUi();//初始化界面参数
    void initConnect();//初始化信号和槽连接
private slots:
    void on_pushButton_openAllDoor_clicked();
    void on_pushButton_updateParcelState_clicked();
private:
    Ui::RemainingParcelWidget *ui;
};

#endif // REMAININGPARCELWIDGET_H
