#ifndef REFUSEDIALOG_H
#define REFUSEDIALOG_H
#include <QButtonGroup>
#include <QDialog>

namespace Ui {
class RefuseDialog;
}

class RefuseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RefuseDialog(QWidget *parent = 0);
    ~RefuseDialog();
private:
    void initUi();//初始化界面参数
    void initConnect();//初始化信号和槽连接
private slots:
    void on_pushButton_yes_clicked();
    void on_pushButton_cancell_clicked();
    void refuseButtonGroup_clicked(QAbstractButton *button);
private:
    Ui::RefuseDialog *ui;
    QButtonGroup *m_pButtonGroup;
};

#endif // REFUSEDIALOG_H
