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
    Ui::BoxInfoWidget *ui;
};

#endif // BOXINFOWIDGET_H
