#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sub_window2.h"
#include "sub_windpw3.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_pushButton_clicked();
    void on_ww_clicked();
    private:
    Ui::MainWindow *ui;
    Sub_window2 window2;
    Sub_windpw3 window3;
};

#endif // MAINWINDOW_H
