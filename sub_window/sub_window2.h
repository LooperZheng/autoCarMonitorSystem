#ifndef SUB_WINDOW2_H
#define SUB_WINDOW2_H

#include <QWidget>

namespace Ui {
class Sub_window2;
}

class Sub_window2 : public QWidget
{
    Q_OBJECT

public:
    explicit Sub_window2(QWidget *parent = 0);
    ~Sub_window2();
private slots:
     void on_pushButton_clicked();
private:
    Ui::Sub_window2 *ui;
};

#endif // SUB_WINDOW2_H
