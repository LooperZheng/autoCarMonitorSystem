#include <iostream>
#include <stdio.h>
#include "robot.h"
#include <string>
#include "io.h"
#define MAX_LINE_LEN 100000
using namespace std;

Robot::Robot(QObject *parent):
    QObject(parent)
{

}


Robot::~Robot()
{

}
void Robot::getVehicelCoor()
{
    vehicleCoor.ID =0;
    vehicleCoor.vehicle_x = 121.439659;
    vehicleCoor.vehicle_y = 31.025816;
    vehicleCoor.vehicle_info = QString("vehivle");
}
void Robot::getTaskSeqFromLogisticDB()
{
    //模拟读取数据库信息
    char *taskSeqTmp[MAX_EDGE_NUM];
    int lineNum = read_file(taskSeqTmp, MAX_EDGE_NUM, "/home/zlp/qt_test/test1/topoMap/taskSeq.txt");
    if (lineNum == 0)
    {
        printf("Please input valid task file.\n");
    }

    stringstream str;
    str<<taskSeqTmp[0];
    int num;
    str>>num;
    for (int i= 0; i<lineNum-1; i++)
    {
        int taskID;
        str<<taskSeqTmp[i+1];
        str>>taskID;
        //cout<<taskID<<endl;
        this->taskSeq.push_back(taskID);

        //
        QString taskInfo;
        taskInfo = "task " + QString::number(taskID);
        taskPoint taskPointTmp;
        taskPointTmp.ID = taskID;
        taskPointTmp.longitude = pathPointID2Coordinate[taskID].first;
        taskPointTmp.latitude = pathPointID2Coordinate[taskID].second;
        taskPointTmp.taskInfo = taskInfo;
        taskPointCluster.push_back(taskPointTmp);

    }

    release_buff(taskSeqTmp, lineNum);

}
void Robot::getPathMapFromTopoMap()
{
    char *pathSeqTmp[MAX_LINE_LEN];
    int lineNum = read_file(pathSeqTmp, MAX_EDGE_NUM, "/home/zlp/qt_test/test1/topoMap/topoMap.txt");
    if (lineNum == 0)
    {
        printf("Please input valid task file.\n");
    }

    stringstream str;
    str<<pathSeqTmp[0];
    int num;
    str>>num;
    for (int i= 0; i<lineNum-1; i++)
    {
        int from, to;
        double dis;
        Path path;
        str<<pathSeqTmp[i+1];
        str>>from>>to>>dis;
        path.from = from;
        path.to = to;
        path.dis = dis;
        this->pathMap.push_back(path);
        //cout<<from<<" "<<to<<" "<<dis<<endl;
    }
    release_buff(pathSeqTmp, lineNum);
}

void Robot::getPathPointFromTopoMap()
{
    char *pathPointTmp[MAX_LINE_LEN];
    int lineNum = read_file(pathPointTmp, MAX_EDGE_NUM, "/home/zlp/qt_test/test1/topoMap/pathPoint.txt");
    if (lineNum == 0)
    {
        printf("Please input valid task file.\n");
    }

    stringstream str;
    str<<pathPointTmp[0];
    int num;
    str>>num;
    for (int i= 0; i<lineNum-1; i++)
    {
        int ID;
        double longitude, latitude;
        bool isTaskPoint;
        str<<pathPointTmp[i+1];
        str>>ID>>longitude>>latitude>>isTaskPoint;
        std::pair<double, double> coordinate(longitude, latitude);
        pathPointID2Coordinate[ID] = coordinate;
        //printf("%lf %lf\n", longitude, latitude);
        //cout<<ID<<" "<<longitude<<" "<<latitude<<" "<<isTaskPoint<<endl;
    }
    release_buff(pathPointTmp, lineNum);
}
