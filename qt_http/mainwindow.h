#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtNetwork>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void sendRequest(const QString& strUrl);//根据url发起http请求

signals:
    void signal_requestFinished(bool bSuccess,const QString& strResult); //http请求结束

public slots:
    void replyFinished(); //http请求结束
    void requestTimeout();  //请求超时
    void on_pushButton_clicked();
    void requestFinished(bool bSuccess, const QString &strResult);

private:
    Ui::MainWindow *ui;

    QNetworkAccessManager* m_pNetworkManager;//网络管理类
    QNetworkReply* m_pNetworkReply; //封装请求返回信息
    QTimer* m_pTimer; //请求超时计时器
    QString m_strUrl; //记录当前请求的url
};

#endif // MAINWINDOW_H
