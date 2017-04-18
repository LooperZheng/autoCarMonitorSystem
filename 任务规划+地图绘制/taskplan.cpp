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
#include<functional>
#include "taskplan.h"

using namespace std;
#define INF 100000000
#define N 10000
#define PATHMAX 50000

void TaskPlan::init(int nodeNum,  vector<int>const& taskCluster)//初始化
{

    this->path.resize(PATHMAX);
    this->nodeNum = nodeNum;
    this->stationID=0;
    disMin = INF;

    for(int i=0;i<nodeNum;i++)
        G[i].clear();
    edges.clear();

    memset(taskSeq,0,sizeof(taskSeq));
    memset(taskSeqLast,0,sizeof(taskSeqLast));
    memset(taskSeqNew,0,sizeof(taskSeqNew));

    for(int i=0; i<taskCluster.size();i++)
    {
        taskSeq[i] = taskCluster[i];
    }

    taskNum = taskCluster.size();

}

void TaskPlan::addedge(int from,int to,double dis)//加边
{
    edges.push_back(Edge(from,to,dis));
    //vector的size为每个点的出度，每个value为对应Edges存储边的下标
    int m=edges.size();
    G[from].push_back(m-1);
    //cout<<from<<" "<<to<<" "<<dis<<endl;
}

//寻找最短路径
bool TaskPlan::SPFA(int s,int t)
{
    pathTmp.clear();

    for(int i=0;i<nodeNum;i++)
        d[i]=INF;

    memset(inq,0,sizeof(inq));
    d[s]=0;inq[s]=1;p[s]=0;

    queue<int> Q;
    Q.push(s);
    while(!Q.empty())
    {
        int u=Q.front();
        Q.pop();
        inq[u]--;
        //广度优先 BFS
        for(int i=0;i<G[u].size();i++)
        {
            Edge& e=edges[G[u][i]];
            if(d[e.to]>d[u]+e.dis) //满足可变短
            {
                d[e.to]=d[u]+e.dis;
                p[e.to]=G[u][i];
                //是否在队列中
                if(!inq[e.to])
                {
                    inq[e.to]++;
                    Q.push(e.to);
                }
            }
        }
    }

    if(d[t]==INF)
        return false;//汇点不可达则退出
    //保存本次路径
    int u=t;
    pathTmp.push_back(u);
    disTmp =0;
    //cout<<"u "<<u<<" s "<<s<<endl;
    while(u!=s)
    {
        disTmp += edges[p[u]].dis;
        u=edges[p[u]].from;
        pathTmp.push_back(u);
    }

    reverse(pathTmp.begin(), pathTmp.end());
    //debug
//    cout<<disTmp<<endl;
//    for (int i=0;i<pathTmp.size();i++)
//        cout<<pathTmp[i]<<" ";
//    cout<<endl;

    return true;
}

result TaskPlan::traverlsalSolution()
{
    //初始化随机数种子
    srand((unsigned)time(NULL));

    disMin = INF;
    result res;
    res.isValid =true;
    int cnt =0;
    while (cnt < 5)
    {

        dis = 0;
        path.clear();

        if (SPFA(stationID, taskSeq[0]))
        {
            dis += disTmp;
            pathTmp.pop_back();
            path.insert(path.end(), pathTmp.begin(), pathTmp.end());
        }
        else
        {
            res.isValid = false;
            return res;
        }

        for (int i=0; i<taskNum-1;i++)
        {
            int s = taskSeq[i];
            int t = taskSeq[i+1];
            if (SPFA(s, t))
            {
                dis += disTmp;
                pathTmp.pop_back();
                path.insert(path.end(), pathTmp.begin(), pathTmp.end());
            }
            else
            {
                res.isValid = false;
                return res;
            }
        }

        if (SPFA( taskSeq[taskNum-1], stationID))
        {
            dis += disTmp;
            path.insert(path.end(), pathTmp.begin(), pathTmp.end());
        }
        else
        {
            res.isValid = false;
            return res;
        }

        //cout<<"dis = "<<dis<<endl;
        dis<disMin ? res.dis=dis : res.dis=res.dis;
        dis<disMin ? res.path=path : res.path=res.path;
        dis<disMin ? disMin=dis : disMin=disMin;
        //Exchange two pos
        int pos1 = randomi(0, taskNum-1);
        int pos2 = randomi(0, taskNum-1);

        int temp = taskSeq[pos1];
        taskSeq[pos1] = taskSeq[pos2];
        taskSeq[pos2] = temp;

        cnt ++;
    }

    return res;
}
//求随机数
int  TaskPlan::randomi(int a, int b)
{
    int c=rand()%(b-a+1)+a;
    return c;
}

double TaskPlan::randomf(double a, double b)
{
    double c = (double)(rand()%((int)b-(int)a)) + a + (double)(rand()/(RAND_MAX + 1.0));
    return c;
}

bool TaskPlan::accept(double deta,float T)
{
    if (deta<0)
    {
        //cout<<"---Find a better valid answer---"<<endl;
        return 1;
    }
    else if (((deta>0) && (exp(-deta/T)>randomf(0,1))))
    {
        double aa =exp(-deta/T);
        //cout<<"deta= "<<deta<<" "<<"T= "<<T<<" "<<"(exp(-deta/T) = "<<aa<<endl;
        //cout<<"****accept a not better ans****"<<endl;
        return 1;
    }
    return 0;
}

void TaskPlan::initAns()
{
    for (int i= 0; i<taskNum; i++)
    {
        taskSeqNew[i] = taskSeq[i];
    }
}

void TaskPlan::calcNewAns()
{
    //Exchange two pos
    int pos1 = randomi(0, taskNum-1);
    int pos2 = randomi(0, taskNum-1);

    memcpy(taskSeqNew, taskSeq, sizeof(taskSeq));
    int temp = taskSeqNew[pos1];
    taskSeqNew[pos1] = taskSeqNew[pos2];
    taskSeqNew[pos2] = temp;
}

result TaskPlan::heuristicSolution ()
{
    //初始化随机数种子
    srand((unsigned)time(NULL));

    //模拟退火
    float T = 100;
    float T_time = 0.001;
    int L =20;

    disMin = INF;
    double disLast = INF;
    result res;
    res.isValid = true;
    initAns();

    while (T>T_time)
    {
        for(int i=0; i<L;i++)
        {
            dis = 0;
            path.clear();

            if (SPFA(stationID, taskSeq[0]))
            {
                dis += disTmp;
                pathTmp.pop_back();
                path.insert(path.end(), pathTmp.begin(), pathTmp.end());
            }
            else
            {
                res.isValid = false;
                return res;
            }

            for (int i=0; i<taskNum-1;i++)
            {
                int s = taskSeqNew[i];
                int t = taskSeqNew[i+1];
                if (SPFA(s, t))
                {
                    dis += disTmp;
                    pathTmp.pop_back();
                    path.insert(path.end(), pathTmp.begin(), pathTmp.end());
                }
                else
                {
                    res.isValid = false;
                    return res;
                }
            }

            if (SPFA(taskSeq[taskNum-1], stationID))
            {
                dis += disTmp;
                path.insert(path.end(), pathTmp.begin(), pathTmp.end());
            }
            else
            {
                res.isValid = false;
                return res;
            }

            dis<disMin? res.dis=dis: res.dis=res.dis;
            dis<disMin? res.path=path: res.path=res.path;
            dis<disMin? disMin=dis: disMin=disMin;

            double deta = dis - disLast;
            if (accept(deta, T))
            {
                memcpy(taskSeq, taskSeqNew, sizeof(taskSeqNew));
                disLast = dis;
            }

            //产生新解
            calcNewAns();
        }

        T = 0.98*T;
    }
    return res;
}
