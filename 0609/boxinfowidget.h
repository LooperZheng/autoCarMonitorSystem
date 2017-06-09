#ifndef BOXINFOWIDGET_H
#define BOXINFOWIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QGraphicsItem>
#include <QGraphicsScene>
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
    void updateBox();
    void getCombineBox(const std::vector<int>[], std::vector<int>&,std::vector<int>&,std::vector<int>&);
private slots:
    void on_pushButton_openBox_clicked();
    void boxButtonGroup_clicked(QAbstractButton *button);
signals:
    void signal_openBox(std::vector<int>);
private:
    Ui::BoxInfoWidget *ui;
    QButtonGroup *m_pButtonGroup;
    QGraphicsScene *scene;
    std::vector<QGraphicsRectItem*> itemClister;

    QRect rec_2v;
    QRect rec_2h;
    QRect rec_4;
    QRect rec_2v_s;
    QRect rec_2h_s;
    QRect rec_4_s;

    int test;
};

#endif // BOXINFOWIDGET_H
