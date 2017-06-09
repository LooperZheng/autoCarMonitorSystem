#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <vector>
#include <map>
#include <string>
#include "task_plan.h"
#include "client.h"
#include "sever.h"
using namespace std;

//上传车辆信息
struct CarInfo
{
    int num;
    double longitude;
    double latitude;
    double vel;
    double miles;
    double miles_left;
    int battery;
    bool state;
};
//上传路况信息
struct RoadInfo
{
    std::vector<int> ultrasonicID;
    std::vector<double> obstacleDistance;
    bool passable;
};
//上传系统信息
struct SysInfo
{
    std::vector<std::string> boxState;
    int communicationState;
};


struct taskPoint
{
    int ID;
    double longitude;
    double latitude;
    QString taskInfo;
};
struct Path
{
    int from;
    int to;
    double dis;
};

struct vehicleCoordinate
{
  int ID;
  double vehicle_x;
  double vehicle_y;
  QString vehicle_info;
};
class Robot: public QObject
{
     Q_OBJECT
public:
     explicit Robot(QObject *parent=0);
     ~Robot();
    void initConnect();
    std::vector<int> taskSeq;
    std::vector<int> pathSeq;
    std::set<int> completedTaskSeq;
    std::vector<Path> pathMap;
    std::vector<taskPoint> taskPointCluster;
    std::map<int, std::pair<double,double> > pathPointID2Coordinate;
    std::map<int, bool>  pathPointID2IsTaskPoint;
    vehicleCoordinate vehicleCoor;
    int currentTaskID;
    int nodeNum;
    result planRes;
    //存放所有路径点，包含曲线
    std::vector<int> pathAll;
    std::map<int, std::pair<double,double> > pathPointID2CoordinateAll;

    //上传信息
    CarInfo carInfo;
    RoadInfo roadInfo;
    SysInfo sysInfo;
    //test
    double lo;
    double la;
    int iii;
public slots:
     //local
     void getPathMapFromTopoMap();
     void getPathPointFromTopoMap();
     void getPathPointAllFromTopoMap();
     // DataBase from logistic
     void getTaskSeqFromLogisticDB();
     // data from vehicle
     void getVehicelCoor();


     //JS调用Robot对象的函数，访问对象数据 ,供javascript调用的槽
     int returnTaskNum() {return taskPointCluster.size();}
     double returnTaskPointLongitude(int num) {return taskPointCluster[num].longitude;}
     double returnTaskPointLatitude(int num) {return taskPointCluster[num].latitude;}
     QString returnTaskInfo(int num) {return taskPointCluster[num].taskInfo;}
     int returnTaskID(int num) {return taskPointCluster[num].ID;}

     int returnPathPointNum(){return pathSeq.size();}
     double returnPathPointLongitude(int num) {return pathPointID2Coordinate[pathSeq[num]].first;}
     double returnPathPointLatitude(int num) {return pathPointID2Coordinate[pathSeq[num]].second;}

//     //test for map
//     int returnAllPathPointNum(){return pathMap.size();}
//     double returnAllPathPointLongitudeFrom(int num) {return pathPointID2Coordinate[pathMap[num].from].first;}
//     double returnAllPathPointLatitudeFrom(int num) {return pathPointID2Coordinate[pathMap[num].from].second;}
//     double returnAllPathPointLongitudeEnd(int num) {return pathPointID2Coordinate[pathMap[num].to].first;}
//     double returnAllPathPointLatitudeEnd(int num) {return pathPointID2Coordinate[pathMap[num].to].second;}

     //draw path (not test)
     int returnAllPathPointNum(){return pathAll.size()-1;}
     double returnAllPathPointLongitudeFrom(int num) {return pathPointID2CoordinateAll[pathAll[num]].first;}
     double returnAllPathPointLatitudeFrom(int num) {return pathPointID2CoordinateAll[pathAll[num]].second;}
     double returnAllPathPointLongitudeEnd(int num) {return pathPointID2CoordinateAll[pathAll[num+1]].first;}
     double returnAllPathPointLatitudeEnd(int num) {return pathPointID2CoordinateAll[pathAll[num+1]].second;}

     //vehicle
     double returnVehicle_x() {return vehicleCoor.vehicle_x;}
     double returnVehicle_y() {return vehicleCoor.vehicle_y;}
     QString returnVehicle_info() {return vehicleCoor.vehicle_info;}

     //current task
     int returnCurrentTaskID() {return currentTaskID;}

     //taskplan
     result executeTaskPlan();

     void slot_acceptMsgFromClient();
signals:
     void signal_getCurrentTaskID();
     void signal_completeAllTask();
private:
    TaskPlan planner;
public:
    Sever tcpIpSever;

public:
    void sendMessageToVehicle();

};
#endif // ROBOT_H
