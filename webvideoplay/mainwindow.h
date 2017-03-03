#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextEdit>
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
    void on_pushButton_play_clicked();
    void on_pushButton_replay_clicked();
    void on_pushButton_select_clicked();
private:
     QString htmlUrl;
     QString mimeReturn(const QFile& file);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
