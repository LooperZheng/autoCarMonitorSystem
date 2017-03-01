#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QStackedWidget>
#include <QListWidget>
#include <QtWebKitWidgets/QWebView>
#include <QtWebKitWidgets/QWebFrame>
#include <QHBoxLayout>
#include "robot.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //普通构造函数能够被隐式调用,explicit构造函数只能被显式调用。
    explicit MainWindow(QWidget *parent = 0);
    void initConnect();
    void initUi();
    ~MainWindow();
public slots:
    void addJavaScriptObject();
private:
    Ui::MainWindow *ui;
    Robot *myRobot;
};

#endif // MAINWINDOW_H
