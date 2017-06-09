#include"camthread.h"
#include<QtGui>


Camthread::Camthread()
{
    cam     = NULL;
    timer   = new QTimer(this);
}

Camthread::~Camthread()
{
    timer->stop();         // 停止读取数据。
    cvReleaseCapture(&cam);//释放内存；
    cvReleaseVideoWriter(&writer);

}
void Camthread::startPlay(int camIndex)
{
    cam = cvCreateCameraCapture(camIndex);//打开摄像头，从摄像头中获取视频
    if(!cam)
    {
        QString err;
        err.append(QString::number(camIndex));
        emit sig_err(err);
        qDebug("Warning, Cameras are not found.");
    }
    else
    {
        qDebug("camera open success.");
        timer->start(100);              // 开始计时，超时则发出timeout()信号
        //start thread
        start();
    }
}
//线程启动后，执行该函数
void Camthread::run()
{
    // 时间到，读取当前摄像头信息
    double fps=30;
    frame = cvQueryFrame(cam);
    CvSize size=cvGetSize(frame);
    //保存视频函数 获取视频相关参数
    //writer=cvCreateVideoWriter("Video from CAMERA.avi",CV_FOURCC('X','V','I','D'),fps,size,1);

    connect(timer, SIGNAL(timeout()), this, SLOT(readFrame()));

}
//定时读取视频一帧数据
void Camthread::readFrame( )
{
    frame = cvQueryFrame(cam);// 从摄像头中抓取并返回每一帧
    QImage image = QImage((const uchar*)frame->imageData, frame->width, frame->height,QImage::Format_RGB888).rgbSwapped();

    //cvWriteFrame(writer,frame);
    //发射信号函数
    emit sig_GetOneFrame(image);

}
