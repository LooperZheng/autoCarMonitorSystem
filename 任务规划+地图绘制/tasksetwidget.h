#ifndef TASKSETWIDGET_H
#define TASKSETWIDGET_H

#include <QWidget>

namespace Ui {
class TaskSetWidget;
}

class TaskSetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TaskSetWidget(QWidget *parent = 0);
    ~TaskSetWidget();
private:
    void initUi();//初始化界面参数
    void initConnect();//初始化信号和槽连接
private slots:
    void addTaskCombox_clicked(const QString &);
    void deleTaskCombox_clicked(const QString &);
    void on_pushButton_addTask_clicked();
    void on_pushButton_deleTask_clicked();
    void on_pushButton_startPlan_clicked();

private:
    Ui::TaskSetWidget *ui;
};

#endif // TASKSETWIDGET_H
