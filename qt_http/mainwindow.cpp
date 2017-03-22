#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include "QDebug"
#include <QTextCodec>

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QTimer>
#include <QSslConfiguration>
#include <QString>
#include <QByteArray>

const int nHTTP_TIME = 10000; //10秒

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pNetworkManager = new QNetworkAccessManager(this);
    m_pNetworkReply = NULL;
    m_pTimer = new QTimer;
    connect(m_pTimer,SIGNAL(timeout()),this,SLOT(requestTimeout()));//超时信号
}

MainWindow::~MainWindow()
{
    m_pNetworkReply->deleteLater();
    this->deleteLater(); //释放内存
    delete ui;
}

void MainWindow::sendRequest(const QString &strUrl)
{
    m_strUrl = strUrl;
    QNetworkRequest netRequest;
    netRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    netRequest.setUrl(QUrl(strUrl)); //地址信息
    if(strUrl.toLower().startsWith("https"))//https请求，需ssl支持
    {
        QSslConfiguration sslConfig;
        sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
        sslConfig.setProtocol(QSsl::TlsV1_1);
        netRequest.setSslConfiguration(sslConfig);
    }
    m_pNetworkReply = m_pNetworkManager->get(netRequest); //发起get请求
    connect(m_pNetworkReply,SIGNAL(finished()),this,SLOT(replyFinished())); //请求完成信号
    m_pTimer->start(nHTTP_TIME);
}

//请求结束
void MainWindow::replyFinished()
{
    m_pTimer->stop();//关闭定时器
    QByteArray resultContent = m_pNetworkReply->readAll();
    QTextCodec* pCodec = QTextCodec::codecForName("UTF-8");
    QString strResult = pCodec->toUnicode(resultContent);
    int nHttpCode = m_pNetworkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();//http返回码
    if(nHttpCode == 200)//成功
    {
        emit signal_requestFinished(true,strResult);//请求成功
    }
    else
    {
        emit signal_requestFinished(false,strResult);//请求失败
    }
}
void MainWindow::requestTimeout()
{
    emit signal_requestFinished(false,"timeout");//请求失败
}
void MainWindow::on_pushButton_clicked()
{
    QString strUrl = ui->lineEdit->text().trimmed();
    connect(this,SIGNAL(signal_requestFinished(bool,const QString&)), //http请求结束信号
            this,SLOT(requestFinished(bool,const QString&)));
    sendRequest(strUrl);
}
void MainWindow::requestFinished(bool bSuccess, const QString &strResult)
{
    if(bSuccess)
    {
        ui->textBrowser->setPlainText((strResult)); //纯文本显示
    }
    else
    {
        ui->textBrowser->setPlainText(tr("请求失败！"));
    }

}
