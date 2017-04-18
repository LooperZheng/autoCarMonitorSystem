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
#include "taskplan.h"

using namespace std;

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

    std::vector<int> taskSeq;
    std::vector<int> pathSeq;

    std::vector<Path> pathMap;
    std::vector<taskPoint> taskPointCluster;
    std::map<int, std::pair<double,double> > pathPointID2Coordinate;
    vehicleCoordinate vehicleCoor;

public slots:
     //local
     void getPathMapFromTopoMap();
     void getPathPointFromTopoMap();
     // DataBase from logistic
     void getTaskSeqFromLogisticDB();
     // data from vehicle
     void getVehicelCoor();
     //JS调用Robot对象的函数，访问对象数据 ,供javascript调用的槽
     int returnTaskNum() {return taskPointCluster.size();}
     double returnTaskPointLongitude(int num) {return taskPointCluster[num].longitude;}
     double returnTaskPointLatitude(int num) {return taskPointCluster[num].latitude;}
     QString returnTaskInfo(int num) {return taskPointCluster[num].taskInfo;}

     int returnPathPointNum(){return pathSeq.size();}
     double returnPathPointLongitude(int num) {return pathPointID2Coordinate[pathSeq[num]].first;}
     double returnPathPointLatitude(int num) {return pathPointID2Coordinate[pathSeq[num]].second;}

     //test for map
     int returnAllPathPointNum(){return pathMap.size();}
     double returnAllPathPointLongitudeFrom(int num) {return pathPointID2Coordinate[pathMap[num].from].first;}
     double returnAllPathPointLatitudeFrom(int num) {return pathPointID2Coordinate[pathMap[num].from].second;}
     double returnAllPathPointLongitudeEnd(int num) {return pathPointID2Coordinate[pathMap[num].to].first;}
     double returnAllPathPointLatitudeEnd(int num) {return pathPointID2Coordinate[pathMap[num].to].second;}

     double returnVehicle_x() {return vehicleCoor.vehicle_x;}
     double returnVehicle_y() {return vehicleCoor.vehicle_y;}
     QString returnVehicle_info() {return vehicleCoor.vehicle_info;}


private:
    TaskPlan paln;

};
#endif // ROBOT_H
