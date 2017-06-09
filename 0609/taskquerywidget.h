#ifndef TASKQUERYWIDGET_H
#define TASKQUERYWIDGET_H

#include <QWidget>

namespace Ui {
class TaskQueryWidget;
}

class TaskQueryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TaskQueryWidget(QWidget *parent = 0);
    ~TaskQueryWidget();
private:
    void initUi();//初始化界面参数
    void initConnect();//初始化信号和槽连接
private slots:
    void parcelSelectCombox_clicked(const QString &);
    void taskSelectCombox_clicked(const QString &);
    void scheduleCombox_clicked(const QString &);
    void rankWaysCombox_clicked(const QString &);
private:
    Ui::TaskQueryWidget *ui;
};

#endif // TASKQUERYWIDGET_H
