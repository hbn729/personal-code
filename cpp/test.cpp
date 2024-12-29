#include <iostream>
#include <climits>
#include <string>
#include <cstdlib>
#include <algorithm>

#define max_vexs 7      // 顶点的最大个数
#define max_number 9999 // 代表无穷大

using namespace std;

const int vexsnumber = 7;
const int arcsnumber = 10;
const int vexs[max_vexs] = {1, 2, 3, 4, 5, 6, 7};
const string city[max_vexs] = {"北京", "西安", "郑州", "徐州", "成都", "广州", "上海"}; // 顶点的信息
const double arcs[max_vexs][max_vexs] = {
    {0, 2553, 695, 704, max_number, max_number, max_number},
    {2553, 0, 511, max_number, 812, max_number, max_number},
    {695, 511, 0, 349, max_number, 1579, 651},
    {704, max_number, 349, 0, max_number, max_number, 651},
    {max_number, 812, max_number, max_number, 0, 2368, max_number},
    {max_number, max_number, 1579, max_number, 2368, 0, 1385},
    {max_number, max_number, 651, 349, max_number, 1385, 0}};
const double Time[max_vexs][max_vexs] = {
    {0, 8, 2.3, 2.5, max_number, max_number, max_number},
    {8, 0, 1.5, max_number, 3, max_number, max_number},
    {2.3, 1.5, 0, 1.2, max_number, 5, 2},
    {2.5, max_number, 1.2, 0, max_number, max_number, 2},
    {max_number, 3, max_number, max_number, 0, 7, max_number},
    {max_number, max_number, 5, max_number, 7, 0, 4},
    {max_number, max_number, 2, 1.2, max_number, 4, 0}};
const double cost[max_vexs][max_vexs] = {
    {0, 885, 202, 225, max_number, max_number, max_number},
    {885, 0, 148, max_number, 283, max_number, max_number},
    {202, 148, 0, 112, max_number, 495, 162},
    {225, max_number, 112, 0, max_number, max_number, 112},
    {max_number, 283, max_number, max_number, 0, 684, max_number},
    {max_number, max_number, 495, max_number, 684, 0, 386},
    {max_number, max_number, 162, 112, max_number, 386, 0}};

struct position
{
    int x, y;
};
struct node
{
    position data;
    struct node *next;
};
class queue
{ // 队列
private:
    node *root;

public:
    queue()
    {
        root = new node;
        root->next = NULL;
    }
    void push(position data)
    {
        node *node1 = root;
        while (node1->next)
        {
            node1 = node1->next;
        }
        node *node2 = new node;
        node2->data = data;
        node2->next = nullptr;
        node1->next = node2;
    }
    position front()
    {
        if (root->next == NULL)
        {
            return {-1, -1};
        }
        else
        {
            position number = root->next->data;
            return number;
        }
    };
    bool empty()
    {
        return root->next == NULL;
    }
    void pop()
    {
        if (root->next == NULL)
            return;
        node *node1 = root->next;
        root->next = node1->next;
        delete node1;
    }
    ~queue()
    {
        while (root)
        {
            node *temp = root;
            root = root->next;
            delete temp;
        }
    }
};

typedef struct Graph
{
    char vexs[max_vexs];             // 顶点的信息
    double arcs[max_vexs][max_vexs]; // 代表这个图的边的信息
    double time[max_vexs][max_vexs]; // 代表这个图的边的时间
    double cost[max_vexs][max_vexs]; // 代表这个图的边的费用
    int vexsnumber;                  // 顶点的个数
    int arcsnumber;                  // 边的个数
} Graph;

Graph *InitGraph(int vexs, int arcs)
{ // 初始化一个图
    Graph *G = new Graph;
    G->vexsnumber = vexs;
    G->arcsnumber = arcs;
    for (int i = 0; i < vexs; i++)
    {
        for (int j = 0; j < vexs; j++)
        {
            G->arcs[i][j] = max_number;
            G->time[i][j] = max_number;
            G->cost[i][j] = max_number;
        }
    }
    return G;
}

Graph *CreateGraph()
{                                                 // 传入一些数据,创建一个图
    Graph *G = InitGraph(vexsnumber, arcsnumber); // 初始化这个图
    for (int i = 0; i < G->vexsnumber; i++)
    { // 初始化这个图的顶点
        G->vexs[i] = vexs[i];
    }
    for (int i = 0; i < G->vexsnumber; i++)
    { // 初始化这个图的边
        for (int j = 0; j < G->vexsnumber; j++)
        {
            G->arcs[i][j] = arcs[i][j];
        }
    }
    for (int i = 0; i < G->vexsnumber; i++)
    { // 初始化这个图的时间
        for (int j = 0; j < G->vexsnumber; j++)
        {
            G->time[i][j] = Time[i][j];
        }
    }
    for (int i = 0; i < G->vexsnumber; i++)
    { // 初始化这个图的费用
        for (int j = 0; j < G->vexsnumber; j++)
        {
            G->cost[i][j] = cost[i][j];
        }
    }
    return G;
}

void Floyd(Graph *G, double dist[max_vexs][max_vexs], int path[max_vexs][max_vexs], double weight[max_vexs][max_vexs])
{
    for (int i = 0; i < G->vexsnumber; i++)
    {
        for (int j = 0; j < G->vexsnumber; j++)
        {
            dist[i][j] = weight[i][j];
            if (weight[i][j] < max_number)
            {
                path[i][j] = i;
            }
            else
            {
                path[i][j] = -1;
            }
        }
    }
    for (int k = 0; k < G->vexsnumber; k++)
    {
        for (int i = 0; i < G->vexsnumber; i++)
        {
            for (int j = 0; j < G->vexsnumber; j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }
}

void printPath(int path[max_vexs][max_vexs], int start, int end)
{
    if (path[start][end] == -1)
    {
        cout << "没有路径" << endl;
        return;
    }
    int route[max_vexs];
    int count = 0;
    for (int v = end; v != start; v = path[start][v])
    {
        route[count++] = v;
    }
    route[count++] = start;
    for (int i = count - 1; i >= 0; i--)
    {
        cout << city[route[i]] << (i == 0 ? "" : " -> ");
    }
    cout << endl;
}

void BFS(Graph *G, int start, int end)
{ // 传入一个图,一个起点,一个终点
    queue q;
    int dist[max_vexs]; // 代表从起点到这个顶点的中转次数
    int prev[max_vexs]; // 代表这个顶点的前一个顶点
    for (int i = 0; i < G->vexsnumber; i++)
    { // 初始化
        dist[i] = max_number;
        prev[i] = -1;
    }
    q.push({start, 0});
    dist[start] = 0; // 起点的中转次数为0
    while (!q.empty())
    { // 广度优先搜索
        position u = q.front();
        q.pop();
        for (int v = 0; v < G->vexsnumber; v++)
        { // 遍历这个顶点的所有邻接顶点
            if (G->arcs[u.x][v] != max_number && dist[v] == max_number)
            { // 如果这个顶点没有被访问过
                dist[v] = dist[u.x] + 1;
                prev[v] = u.x;
                q.push({v, dist[v]});
            }
        }
    } // 打印从start到end的路径和中转次数
    if (dist[end] == max_number)
    { // 如果终点的中转次数为无穷大
        cout << "从" << start + 1 << "到" << end + 1 << "没有路径" << endl;
    }
    else
    {
        cout << "从 " << city[start] << " 到 " << city[end] << " 的最少中转次数路径为：";
        int route[max_vexs];
        int count = 0;
        for (int v = end; v != start; v = prev[v])
        { // 从终点开始，一直到起点
            route[count++] = v;
        }
        route[count++] = start;
        for (int i = count - 1; i >= 0; i--)
        {
            cout << city[route[i]] << (i == 0 ? "" : " -> ");
        }
        cout << endl;
        cout << "总中转次数为：" << dist[end] - 1 << " 次" << endl;
    }
}

void menu()
{ // 菜单
    cout << "-------------------------------------------------" << endl;
    cout << "        请选择查询方式:\n";
    cout << "        1. 输入起点与终点进行查询\n";
    cout << "        2. 清空查询记录\n";
    cout << "        0. 退出交通查询系统\n";
    cout << "-------------------------------------------------" << endl;
    Graph *APP = CreateGraph();
    double dist_length[max_vexs][max_vexs];
    double dist_time[max_vexs][max_vexs];
    double dist_cost[max_vexs][max_vexs];
    int path_length[max_vexs][max_vexs];
    int path_time[max_vexs][max_vexs];
    int path_cost[max_vexs][max_vexs];
    Floyd(APP, dist_length, path_length, APP->arcs);
    Floyd(APP, dist_time, path_time, APP->time);
    Floyd(APP, dist_cost, path_cost, APP->cost);
    int query_type;
    cout << "---------------------------------------" << endl;
    cout << "     请输入起点与终点进行查询:\n";
    cin >> query_type;
    while (query_type)
    {
        if (query_type == 2)
        {
            system("cls"); // 清屏
            menu();
            return;
        }
        if (query_type < 0 || query_type > 4)
        {
            cout << "输入错误!!!" << endl;
            cout << endl;
            cout << "------------------------------" << endl;
            cout << "     请选择查询方式:\n";
            cin >> query_type;
            continue;
        }
        int start, end;
        cout << "----------------------------------------------------" << endl;
        cout << "(1)北京(2)西安(3)郑州(4)徐州(5)成都(6)广州(7)上海" << endl;
        cout << "----------------------------------------------------" << endl;
        cout << "请选择上面的城市序号:" << endl;
        cout << "起点城市:";
        cin >> start;
        cout << "终点城市:";
        cin >> end;
        if (start < 1 || start > vexsnumber || end < 1 || end > vexsnumber)
        {
            cout << "输入错误!!!" << endl;
            cout << endl;
            cout << "---------------------------" << endl;
            cout << "     请选择查询方式:\n";
            cin >> query_type;
            continue;
        }
        start--; // 转换为0-based索引
        end--;   // 转换为0-based索引
        switch (query_type)
        {
        case 1:
            cout << "--------------------------------------------------------------" << endl;
            cout << "最短距离为:" << endl;
            printPath(path_length, start, end);
            cout << "总距离为：" << dist_length[start][end] << " 公里" << endl;
            cout << "最短时间为:" << endl;
            printPath(path_time, start, end);
            cout << "总时间为：" << dist_time[start][end] << " 小时" << endl;
            cout << "最低费用为:" << endl;
            printPath(path_cost, start, end);
            cout << "总费用为：" << dist_cost[start][end] << " 元" << endl;
            cout << "最少中转次数查询:" << endl;
            BFS(APP, start, end);
            cout << "--------------------------------------------------------------" << endl;
            break;
        case 0:
            delete APP;
            return;
        }
        cout << endl;
        cout << "------------------------------" << endl;
        cout << "     请选择查询方式:\n";
        cin >> query_type;
    }
    delete APP;
}
int main()
{
    menu(); // 菜单
    return 0;
}
