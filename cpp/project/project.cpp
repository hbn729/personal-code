#include <iostream>
#include <queue>
#include <climits>
#include <string>
#include <cstdlib>
#include <stack>
#include <algorithm>

#define MAXN 7
#define MAXAN 10
#define INF 99999
using namespace std;

// 数据预处理

// 顶点数据
const vector<int> vexs = {1, 2, 3, 4, 5, 6, 7};

// 城市名字
const vector<string> data_city = {"北京", "西安", "郑州", "徐州", "成都", "广州", "上海"};

// 图
const vector<vector<double>> data_Distance = {
    {0, 2553, 695, 704, INF, INF, INF},
    {2553, 0, 511, INF, 812, INF, INF},
    {695, 511, 0, 349, INF, 1579, INF},
    {704, INF, 349, 0, INF, INF, 651},
    {INF, 812, INF, INF, 0, 2368, INF},
    {INF, INF, 1579, INF, 2368, 0, 1385},
    {INF, INF, INF, 651, INF, 1385, 0}};
const vector<vector<double>> data_Time = {
    {0, 8, 2.3, 2.5, INF, INF, INF},
    {8, 0, 1.5, INF, 3, INF, INF},
    {2.3, 1.5, 0, 1.2, INF, 5, INF},
    {2.5, INF, 1.2, 0, INF, INF, 2},
    {INF, 3, INF, INF, 0, 7, INF},
    {INF, INF, 5, INF, 7, 0, 4},
    {INF, INF, INF, 2, INF, 4, 0}};
const vector<vector<double>> data_Cost = {
    {0, 885, 202, 225, INF, INF, INF},
    {885, 0, 148, INF, 283, INF, INF},
    {202, 148, 0, 112, INF, 495, INF},
    {225, INF, 112, 0, INF, INF, 162},
    {INF, 283, INF, INF, 0, 684, INF},
    {INF, INF, 495, INF, 684, 0, 386},
    {INF, INF, INF, 162, INF, 386, 0}};

// 图
struct Graph
{
    vector<int> vexs;                // 城市序号
    vector<string> cityname;         // 城市名字
    vector<vector<double>> time;     // 时间权值
    vector<vector<double>> cost;     // 花费权值
    vector<vector<double>> distance; // 路程权值
    int Vexnum, Arcnum;              // 定点数量，边的数量
};

// 类
class AdjGraph
{
private:
    Graph *G;

public:
    AdjGraph() : G(nullptr)
    {
    }

    ~AdjGraph()
    {
        destroyGraph();
    }

    // 初始化图的数据
    void CreateGraph()
    {
        G = new Graph;
        G->Vexnum = MAXN;
        G->Arcnum = MAXAN;

        G->vexs = vexs;
        G->cityname = data_city;

        G->time.resize(7, vector<double>(7, INF));
        G->distance.resize(7, vector<double>(7, INF));
        G->cost.resize(7, vector<double>(7, INF));

        for (int i = 0; i < 7; ++i)
        {
            for (int j = 0; j < 7; ++j)
            {
                G->time[i][j] = data_Time[i][j];
                G->distance[i][j] = data_Distance[i][j];
                G->cost[i][j] = data_Cost[i][j];
            }
        }
    }

    // 销毁
    void destroyGraph()
    {
        if (G)
        {
            delete G;
            G = nullptr;
        }
    }

    void printlujing(int start, int end, const vector<int> &path)
    {
        cout << " 路径为：";
        stack<int> route;
        for (int v = end; v != -1 && v != start; v = path[v])
        {
            route.push(v);
        }
        if (!route.empty())
            route.push(start); // 只有当存在路径时才添加起点

        double timeSum = 0, costSum = 0, distanceSum = 0;
        bool isFirst = true;
        int prevNode = -1;
        while (!route.empty())
        {
            int currentNode = route.top();
            if (!isFirst)
            {
                // 计算其他两种权重的和
                if (prevNode != -1)
                {
                    timeSum += G->time[prevNode][currentNode];
                    costSum += G->cost[prevNode][currentNode];
                    distanceSum += G->distance[prevNode][currentNode];
                }
            }
            if (!isFirst)
                cout << " -> ";
            cout << data_city[currentNode];
            isFirst = false;
            prevNode = currentNode;
            route.pop();
        }
        cout << endl;

        cout << timeSum << "h, 成本 " << costSum << "元, 距离 " << distanceSum << "km" << endl;
    }

    void Dijkstra(int start, int end, int chance)
    {
        // 初始化
        vector<double> D(G->Vexnum, INF);
        vector<bool> visited(G->Vexnum, false);
        vector<int> path(G->Vexnum, -1);

        D[start] = 0;

        // 主循环v
        for (int vex = 0; vex < G->Vexnum; vex++)
        {
            int v = -1;
            double minDist = INF;
            for (int j = 0; j < G->Vexnum; j++)
            {
                if (!visited[j] && D[j] < minDist)
                {
                    v = j;
                    minDist = D[j];
                }
            }
            if (v == -1)
                break;
            visited[v] = true;
            // cout << "选择顶点：" << v << " 当前最短距离：" << minDist << endl;
            // 根据chance选择权重矩阵
            vector<vector<double>> Weight;
            switch (chance)
            {
            case 1:
                Weight.resize(7, vector<double>(7, INF));
                for (int i = 0; i < 7; ++i)
                {
                    for (int j = 0; j < 7; ++j)
                    {
                        Weight[i][j] = data_Distance[i][j];
                    }
                }
                break;
            case 2:
                Weight.resize(7, vector<double>(7, INF));
                for (int i = 0; i < 7; ++i)
                {
                    for (int j = 0; j < 7; ++j)
                    {
                        Weight[i][j] = data_Time[i][j];
                    }
                }
                break;
            case 3:
                Weight.resize(7, vector<double>(7, INF));
                for (int i = 0; i < 7; ++i)
                {
                    for (int j = 0; j < 7; ++j)
                    {
                        Weight[i][j] = data_Cost[i][j];
                    }
                }
                break;
            default:
                return;
            }

            for (int w = 0; w < G->Vexnum; w++)
            {
                if (!visited[w] && Weight[v][w] != INF)
                {
                    double newDist = D[v] + Weight[v][w];
                    if (newDist < D[w])
                    {
                        D[w] = newDist;
                        path[w] = v;
                    }
                }
            }
        }

        if (D[end] == INF)
        {
            cout << "从" << G->cityname[start] << "到" << G->cityname[end] << "没有路径";
        }
        else
        {
            cout << "从 " << G->cityname[start] << " 到 " << G->cityname[end];
            if (chance == 1)
            {
                cout << " 的最短距离为：" << D[end] << "km";
            }
            else if (chance == 2)
            {
                cout << " 的最短时间为：" << D[end] << "h";
            }
            else if (chance == 3)
            {
                cout << " 的最低花费为：" << D[end] << "元";
            }
        }
        printlujing(start, end, path);
    }

    // 最少中转次数
    void BFS(int start, int end)
    {
        vector<int> dist(MAXN, -1);
        queue<int> q;
        vector<int> prev(MAXN, -1); // 记录前驱节点

        dist[start] = 0;
        q.push(start);

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int v = 0; v < G->Vexnum; v++)
            {
                if ((G->distance[u][v] != INF) || (G->time[u][v] != INF) || (G->cost[u][v] != INF))
                {
                    if (dist[v] == -1)
                    {
                        dist[v] = dist[u] + 1;
                        prev[v] = u; // 记录v的前驱节点为u
                        q.push(v);
                    }
                }
            }
        }
        if (dist[end] == -1)
        {
            cout << "从" << G->cityname[start] << "到" << G->cityname[end] << "没有路径" << endl;
        }
        else
        {
            cout << "从" << G->cityname[start] << "到" << G->cityname[end] << "的最少中转次数为" << dist[end] - 1 << "次 路径为：";
            printlujing(start, end, prev);
        }
    }
};
void display()
{
    cout << "*******************************" << endl;
    cout << "*  1. 输入起点与终点进行查询  *\n";
    cout << "*  0. 退出                    *\n";
    cout << "*******************************" << endl;
    cout << "您的选择：" << endl;
}

void menu()
{
    display();
    AdjGraph sys;
    sys.CreateGraph();
    int chance;
    while (true)
    {
        cout << "请输入你的选择: ";
        cin >> chance;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "输入错误！请输入一个整数。" << endl;
            continue;
        }

        if (chance != 0 && chance != 1)
        {
            cout << "！！！输入错误！！！" << endl;
            continue;
        }

        int start, end;
        cout << "********************************************" << endl;
        cout << "(0)北京(1)西安(2)郑州(3)徐州(4)成都(5)广州(6)上海" << endl;
        cout << "********************************************" << endl;
        cout << "起点城市:";
        while (true)
        {
            cin >> start;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1024, '\n');
                cout << "输入错误！请输入一个整数。" << endl;
                continue;
            }
            if (start < 0 || start > 6)
            {
                cout << "！！！输入错误！！！请输入1到7之间的整数。" << endl;
                continue;
            }
            break;
        }

        cout << "终点城市:";
        while (true)
        {
            cin >> end;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1024, '\n');
                cout << "输入错误！请输入一个整数。" << endl;
                continue;
            }
            if (end < 0 || end > 6)
            {
                cout << "！！！输入错误！！！请输入0到6之间的整数。" << endl;
                continue;
            }
            if (start == end)
            {
                cout << "重复输入，请重新输入终点城市" << endl;
                continue;
            }
            break;
        }

        switch (chance)
        {
        case 1:
            cout << "**************************************" << endl;
            sys.Dijkstra(start, end, 1);
            sys.Dijkstra(start, end, 2);
            sys.Dijkstra(start, end, 3);
            sys.BFS(start, end);
            break;
        case 0:
            return;
        }
        display();
    }
}

int main()
{
    menu();
    return 0;
}