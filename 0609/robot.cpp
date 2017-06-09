#include <iostream>
#include <stdio.h>
#include "robot.h"
#include <string>
#include "io.h"
#include <json/json.h>
#include <json/value.h>
#include <json/writer.h>

#define MAX_LINE_LEN 100000
using namespace std;

Robot::Robot(QObject *parent):
    QObject(parent)
{
    la = 31.025816;
    lo =121.439659;
    iii=1;

    carInfo.num =001;
    carInfo.longitude = 121.437495362381 ;
    carInfo.latitude = 31.0275804094341;

    roadInfo.passable = 1;
    sysInfo.communicationState = 2;

    qDebug("start to tcp sever init");
    tcpIpSever.tcpSeverInit();
    tcpIpSever.tcpListening();


    initConnect();
}

Robot::~Robot()
{

}
void Robot::initConnect()
{
    //不同类对象之间通信
    connect( &(this->tcpIpSever), SIGNAL(signal_acceptMsgFromClient()), this,SLOT (slot_acceptMsgFromClient()));
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

//    int pathID = tcpIpClient.currentTaskID;
//    cout<<pathID<<endl;
//    lo = tcpIpClient.longitude;
//    la = tcpIpClient.latitude;
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
//        emit signal_completeAllTask();
//    }
    vehicleCoor.ID =carInfo.num;
    vehicleCoor.vehicle_x = carInfo.longitude;
    vehicleCoor.vehicle_y = carInfo.latitude;
    vehicleCoor.vehicle_info = QString("vehivle 001");

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
    for (int i= 0; i<lineNum; i++)
    {
        int taskID;
        str<<taskSeqTmp[i];
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
    //释放内存
    release_buff(taskSeqTmp, lineNum);

}
//获取拓扑地图
void Robot::getPathMapFromTopoMap()
{
    char *pathSeqTmp[MAX_LINE_LEN];
    int lineNum = read_file(pathSeqTmp, MAX_EDGE_NUM, "/home/zlp/qt_test/test1/topoMap/topoMap.txt");
    //int lineNum = read_file(pathSeqTmp, MAX_EDGE_NUM, "/home/zlp/qt_test/test1/topoMap/test1.txt");
    if (lineNum == 0)
    {
        printf("Please input valid task file.\n");
    }

    std::stringstream str;
    for (int i= 0; i<lineNum; i++)
    {
        int from, to;
        double dis;
        Path path;
        str<<pathSeqTmp[i];
        str>>from>>to>>dis;
        path.from = from;
        path.to = to;
        path.dis = dis;
        this->pathMap.push_back(path);
        //cout<<from<<" "<<to<<" "<<dis<<endl;
    }
    //释放内存
    release_buff(pathSeqTmp, lineNum);
}
//路径点ID和对应经纬度的映射
void Robot::getPathPointFromTopoMap()
{
    char *pathPointTmp[MAX_LINE_LEN];
    int lineNum = read_file(pathPointTmp, MAX_EDGE_NUM, "/home/zlp/qt_test/test1/topoMap/pathPoint.txt");
    //int lineNum = read_file(pathPointTmp, MAX_EDGE_NUM, "/home/zlp/qt_test/test1/topoMap/test.txt");
    if (lineNum == 0)
    {
        printf("Please input valid task file.\n");
    }

    std::stringstream str;
    //路径点的数量（包含配送站 0）
    str<<pathPointTmp[0];
    str>>nodeNum;
    for (int i= 0; i<lineNum-1; i++)
    {
        int ID;
        double longitude, latitude;
        bool isTaskPoint;
        str<<pathPointTmp[i+1];
        str>>ID>>longitude>>latitude>>isTaskPoint;
        std::pair<double, double> coordinate(longitude, latitude);
        pathPointID2Coordinate[ID] = coordinate;
        pathPointID2IsTaskPoint[ID] = isTaskPoint;
        //printf("%lf %lf\n", longitude, latitude);
        //cout<<ID<<" "<<longitude<<" "<<latitude<<" "<<isTaskPoint<<endl;
    }
    //释放内存
    release_buff(pathPointTmp, lineNum);
}
//存放所有路径点，包含曲线
void Robot::getPathPointAllFromTopoMap()
{
    char *pathPointTmp[MAX_LINE_LEN];
    int lineNum = read_file(pathPointTmp, MAX_EDGE_NUM, "/home/zlp/qt_test/test1/topoMap/pathPointAll.txt");
    if (lineNum == 0)
    {
        printf("Please input valid task file.\n");
    }

    std::stringstream str;
    //路径点的数量（包含配送站 0）
    str<<pathPointTmp[0];
    str>>nodeNum;
    for (int i= 0; i<lineNum-1; i++)
    {
        int ID;
        double longitude, latitude;
        bool isTaskPoint;
        str<<pathPointTmp[i+1];
        str>>ID>>longitude>>latitude>>isTaskPoint;
        std::pair<double, double> coordinate(longitude, latitude);
        pathPointID2CoordinateAll[ID] = coordinate;
        //printf("%lf %lf\n", longitude, latitude);
        //cout<<ID<<" "<<longitude<<" "<<latitude<<" "<<isTaskPoint<<endl;
    }
    //释放内存
    release_buff(pathPointTmp, lineNum);
}
//执行任务规划
result Robot::executeTaskPlan()
{
    planner.init(nodeNum, taskSeq);

    //构建图的顶点和边（graph）
    for (int i= 0; i<pathMap.size(); i++)
    {
        planner.addedge(pathMap[i].from, pathMap[i].to, pathMap[i].dis);
        //debug
        //cout<<pathMap[i].from<<" "<<pathMap[i].to<<" "<<pathMap[i].dis<<endl;
    }
    //开始规划
    //planRes = planner.traverlsalSolution();
    planRes = planner.heuristicSolution();

    //绘制曲线完整路径
    pathAll.clear();
    for (int i=0;i<planRes.path.size()-1;i++)
    {
        pathAll.push_back(planRes.path[i]);
        if(planRes.path[i] == 1 && planRes.path[i+1] == 0)
        {
            pathAll.push_back(7);
            pathAll.push_back(8);
            pathAll.push_back(9);
            pathAll.push_back(10);
        }
        if(planRes.path[i] == 0 && planRes.path[i+1] == 1)
        {
            pathAll.push_back(10);
            pathAll.push_back(9);
            pathAll.push_back(8);
            pathAll.push_back(7);
        }
        if(planRes.path[i] == 0 && planRes.path[i+1] == 4)
        {
            pathAll.push_back(11);
            pathAll.push_back(12);
            pathAll.push_back(13);
            pathAll.push_back(14);
            pathAll.push_back(15);
            pathAll.push_back(16);
        }
        if(planRes.path[i] == 4 && planRes.path[i+1] == 0)
        {
            pathAll.push_back(16);
            pathAll.push_back(15);
            pathAll.push_back(14);
            pathAll.push_back(13);
            pathAll.push_back(12);
            pathAll.push_back(11);
        }
        if(planRes.path[i] == 2 && planRes.path[i+1] == 3)
        {
            pathAll.push_back(17);
            pathAll.push_back(18);
            pathAll.push_back(19);
        }
        if(planRes.path[i] == 3 && planRes.path[i+1] == 2)
        {
            pathAll.push_back(19);
            pathAll.push_back(18);
            pathAll.push_back(17);
        }
    }
    pathAll.push_back(planRes.path[planRes.path.size()-1]);

    //show
    cout<<"pathAll show"<<endl;
    for(int i=0; i<pathAll.size();i++)
        cout<<pathAll[i];
    cout<<endl;

    //规划后的任务序列顺序
    taskSeq = planRes.taskSeq;
    return planRes;
}
//发送任务规划后的任务序列和路径序列
void Robot::sendMessageToVehicle()
{
    vector<int> pathTemp = planRes.path;
    vector<int> taskTemp = planRes.taskSeq;
    //debug
    qDebug()<<"**send path seq and task seq to vehicle";
    for(int i=0;i<pathTemp.size();i++)
        cout<<pathTemp[i]<<" ";
    cout<<endl;
    for(int i=0;i<taskTemp.size();i++)
        cout<<taskTemp[i]<<" ";
    cout<<endl;

    Json::Value pathSeqJson;
    Json::Value taskSeqJson;
    Json::Value root;
    Json::FastWriter fast;
    //构建json数组
    for(int i=0; i<pathTemp.size();i++)
    {
        pathSeqJson.append(pathTemp[i]);
    }
    for(int i=0; i<taskTemp.size();i++)
    {
        taskSeqJson.append(taskTemp[i]);
    }

    root["Name"]="planRes";
    root["pathSeq"]=pathSeqJson;
    root["taskSeq"]=taskSeqJson;
    string out = root.toStyledString();
    cout<<out<<std::endl;

    std::string str=fast.write(root) ;
    tcpIpSever.sendMessage(str);
}
//从客户端接收到信息的槽函数
void Robot::slot_acceptMsgFromClient()
{
    //qDebug("slot_acceptMsgFromClient()");
    std::string msg;
    msg = tcpIpSever.readMessageFromTcpClient();

    Json::Reader read;
    Json::Value root;
    if(read.parse(msg.c_str(), root))
    {
        std::string name = root["Name"].asString();
        qDebug()<<QString::fromStdString(name);
        if(name == "car_Info")
        {
            qDebug()<<carInfo.num;
            carInfo.num = root["num"].asInt();
            carInfo.longitude = root["lon"].asDouble();
            carInfo.latitude = root["lat"].asDouble();
            carInfo.vel = root["vel"].asDouble();
            carInfo.miles = root["miles"].asDouble();
            carInfo.miles_left  = root["miles_left"].asDouble();
            carInfo.battery = root["battery"].asInt();
            carInfo.state = root["state"].asBool();
        }
        else if(name == "road_Info")
        {
            roadInfo.passable = root["passable"].asBool();

            //??? vector
        }
        else if(name == "sys_Info")
        {
            sysInfo.communicationState = root["comm_state"].asInt();
        }
    }
}
