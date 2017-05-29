#ifndef TASKSET_H
#define TASKSET_H

#include <QWidget>

namespace Ui {
class taskset;
}

class taskset : public QWidget
{
    Q_OBJECT

public:
    explicit taskset(QWidget *parent = 0);
    ~taskset();

private:
    Ui::taskset *ui;
};

#endif // TASKSET_H
