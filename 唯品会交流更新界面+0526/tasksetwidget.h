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
    void on_pushButton_addTask_clicked();
    void on_pushButton_deleTask_clicked();
    void on_pushButton_startPlan_clicked();
    void on_pushButton_changeSchedule_clicked();
    void on_pushButton_changeDistributionTime_clicked();
    void on_pushButton_changeDistributionWays_clicked();
    void on_pushButton_changeDistributionDestination_clicked();
    void on_pushButton_parcelQuery_clicked();

    void addTaskCombox_clicked(const QString &);
    void deleTaskCombox_clicked(const QString &);
    void changeDistributionSchedule_clicked(const QString &);
    void changeDistributionTime_clicked(const QString &);
    void changeDistributionWays_clicked(const QString &);
    void changeDistributionDestination_clicked(const QString &);

private:
    Ui::TaskSetWidget *ui;
};

#endif // TASKSETWIDGET_H
