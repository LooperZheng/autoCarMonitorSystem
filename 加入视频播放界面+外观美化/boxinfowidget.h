#ifndef BOXINFOWIDGET_H
#define BOXINFOWIDGET_H

#include <QWidget>

namespace Ui {
class BoxInfoWidget;
}

class BoxInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BoxInfoWidget(QWidget *parent = 0);
    ~BoxInfoWidget();
private:
    void initUi();//初始化界面参数
    void initConnect();//初始化信号和槽连接

private:
    Ui::BoxInfoWidget *ui;
};

#endif // BOXINFOWIDGET_H
