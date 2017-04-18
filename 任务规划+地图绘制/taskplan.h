#ifndef __TASKPLAN_H__
#define __TASKPLAN_H__
#include <stdio.h>
#include<iostream>
#include<algorithm>
#include<string>
#include <sstream>
#include<vector>
#include<map>
#include<queue>
#include<deque>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<functional>

using namespace std;
#define INF 100000000
#define N 10000
#define PATHMAX 50000

struct result
{
  double dis;
  vector<int> path;
  bool isValid;
};

struct Edge
{
    int from,to;
    double dis;
    Edge(int u, int v, double dist){from=u; to=v; dis=dist;}
};

struct TaskPlan
{
    vector<int> path;
    vector<int> pathTmp;
    int stationID;
    int nodeNum;

    double dis;
    double disTmp;
    double disMin;
    int m,s,t;
    vector<Edge> edges;
    vector<int> G[N]; //网络,临接表.存放vector的数组
    int inq[N];//是否在队列中
    double d[N];//距离
    int p[N];//上一条弧

    void init(int nodeNum, vector<int>const& taskCluster);//初始化
    void addedge(int from,int to,double dis);//加边
    bool SPFA(int s,int t);//寻找最短路径
    result heuristicSolution();
    result traverlsalSolution();
    result greedySolution();

    int taskNum;
    int taskSeq[50];
    int taskSeqNew[50];
    int taskSeqLast[50];

    int randomi(int a, int b);
    double randomf(double a, double b);
    bool accept(double deta, float T); //判断是否接受新解
    void initAns();
    void calcNewAns();
};
#endif
