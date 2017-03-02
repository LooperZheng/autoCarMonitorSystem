#ifndef SUB_WINDPW3_H
#define SUB_WINDPW3_H

#include <QWidget>

namespace Ui {
class Sub_windpw3;
}

class Sub_windpw3 : public QWidget
{
    Q_OBJECT

public:
    explicit Sub_windpw3(QWidget *parent = 0);
    ~Sub_windpw3();
private slots:
     void on_pushButton_clicked();
private:
    Ui::Sub_windpw3 *ui;
};

#endif // SUB_WINDPW3_H
