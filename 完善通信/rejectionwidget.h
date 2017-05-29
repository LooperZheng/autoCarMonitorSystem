#ifndef REJECTIONWIDGET_H
#define REJECTIONWIDGET_H

#include <QWidget>
#include "refusedialog.h"
namespace Ui {
class RejectionWidget;
}

class RejectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RejectionWidget(QWidget *parent = 0);
    ~RejectionWidget();
private:
    void initUi();//初始化界面参数
    void initConnect();//初始化信号和槽连接
private slots:
    void on_pushButton_agree_clicked();
    void on_pushButton_disagree_clicked();
private:
    Ui::RejectionWidget *ui;
    RefuseDialog refuseDialog;
};

#endif // REJECTIONWIDGET_H
