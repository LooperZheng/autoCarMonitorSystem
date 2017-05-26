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
    la = 31.025816;
    lo =121.439659;
    iii=1;

    tcpIpClient.tcpClientInit();
}

Robot::~Robot()
{

}
void Robot::initConnect()
{

}
void Robot::getVehicelCoor()
{

//    iii = iii%planRes.path.size();
//    int pathID = planRes.path[iii];
//    cout<<pathID<<endl;
//    lo = pathPointID2Coordinate[pathID].first;
//    la = pathPointID2Coordinate[pathID].second;
//    if(find(taskSeq.begin(), taskSeq.end(), pathID) != taskSeq.end())
//    {
//        currentTaskID = pathID;
//        emit signal_getCurrentTaskID();
//        cout<<currentTaskID<<endl;
//        completedTaskSeq.insert(currentTaskID);
//        cout<<"completedTaskSeq size "<<completedTaskSeq.size()<<endl;
//    }
//    if (pathID == 0 && completedTaskSeq.size() == taskSeq.size())
//    {
//        completedTaskSeq.clear();
//        iii = 1;
//        emit signal_completeAllTask();
//    }
//    vehicleCoor.ID =0;
//    vehicleCoor.vehicle_x = lo;
//    vehicleCoor.vehicle_y = la;
//    vehicleCoor.vehicle_info = QString("vehivle");
//    iii++;

    int pathID = tcpIpClient.currentTaskID;
    cout<<pathID<<endl;
    lo = tcpIpClient.longitude;
    la = tcpIpClient.latitude;
    if(find(taskSeq.begin(), taskSeq.end(), pathID) != taskSeq.end())
    {
        currentTaskID = pathID;
        emit signal_getCurrentTaskID();
        cout<<currentTaskID<<endl;
        completedTaskSeq.insert(currentTaskID);
        cout<<"completedTaskSeq size "<<completedTaskSeq.size()<<endl;
    }
    if (pathID == 0 && completedTaskSeq.size() == taskSeq.size())
    {
        completedTaskSeq.clear();
        emit signal_completeAllTask();
    }
    vehicleCoor.ID =0;
    vehicleCoor.vehicle_x = lo;
    vehicleCoor.vehicle_y = la;
    vehicleCoor.vehicle_info = QString("vehivle");

}
//从数据库获取任务序列
void Robot::getTaskSeqFromLogisticDB()
{
    //模拟读取数据库信息
    char *taskSeqTmp[MAX_EDGE_NUM];
    int lineNum = read_file(taskSeqTmp, MAX_EDGE_NUM, "/home/zlp/qt_test/test1/topoMap/taskSeq.txt");
    if (lineNum == 0)
    {
        printf("Please input valid task file.\n");
    }

    std::stringstream str;
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

        //task Info
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
//获取拓扑地图
void Robot::getPathMapFromTopoMap()
{
    char *pathSeqTmp[MAX_LINE_LEN];
    int lineNum = read_file(pathSeqTmp, MAX_EDGE_NUM, "/home/zlp/qt_test/test1/topoMap/topoMap.txt");
    if (lineNum == 0)
    {
        printf("Please input valid task file.\n");
    }

    std::stringstream str;
    str<<pathSeqTmp[0];
    str>>nodeNum;
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
//路径点ID和对应经纬度的映射
void Robot::getPathPointFromTopoMap()
{
    char *pathPointTmp[MAX_LINE_LEN];
    int lineNum = read_file(pathPointTmp, MAX_EDGE_NUM, "/home/zlp/qt_test/test1/topoMap/pathPoint.txt");
    if (lineNum == 0)
    {
        printf("Please input valid task file.\n");
    }

    std::stringstream str;
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
//执行任务规划
result Robot::executeTaskPlan()
{
    planner.init(nodeNum, taskSeq);
    //debug
//    cout<<nodeNum<<endl;
//    for (int i =0; i<taskSeq.size();i++)
//        cout<<taskSeq[i]<<" ";
//    cout<<endl;

    for (int i= 0; i<pathMap.size(); i++)
    {
        planner.addedge(pathMap[i].from, pathMap[i].to, pathMap[i].dis);
        //debug
        //cout<<pathMap[i].from<<" "<<pathMap[i].to<<" "<<pathMap[i].dis<<endl;
    }
    //planRes = planner.traverlsalSolution();
    planRes = planner.heuristicSolution();
    taskSeq.assign(planRes.taskSeq.begin(), planRes.taskSeq.end());
    //debug
    for(int i=0;i<taskSeq.size();i++)
        cout<<taskSeq[i]<<" ";
    cout<<endl;
    return planRes;
}
void Robot::sendMessageToVehicle()
{
    vector<int> pathTemp = planRes.path;
    for(int i=0;i<pathTemp.size();i++)
        cout<<pathTemp[i]<<" ";
    cout<<endl;

    int index;
    QString dataTmp;
    QString data;
    QChar charTmp = '0';
    for(int i=0;i<pathTemp.size();i++)
    {
        index = pathTemp[i];
        dataTmp = QString::number(index);
        if (dataTmp.size() ==1)
        {
            dataTmp.insert(0,charTmp);
            dataTmp.insert(0,charTmp);
        }
        if(dataTmp.size()==2)
        {
            dataTmp.insert(0,charTmp);
        }
        //qDebug()<<dataTmp;
        data.append(dataTmp);
    }
    tcpIpClient.sendMessage(data);
}
