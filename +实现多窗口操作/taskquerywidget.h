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
    Ui::TaskQueryWidget *ui;
};

#endif // TASKQUERYWIDGET_H
