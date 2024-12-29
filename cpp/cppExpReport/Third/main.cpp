#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
#include <queue>
#include <algorithm>
#define MAXN 100
#define INF 0x3F3F3F3F
using namespace std;

struct Edge
{
    int adjvex; // 下标
    int weight; // 权重
    Edge *next; // 指向下一条边的指针
};

// 顶点
struct Vertex
{
    int data;    // 顶点
    Edge *first; // 指向第一条边的指针
};

class AdjListGraph
{
private:
    vector<Vertex> vertices; // 顶点数组
    int VexNum, arcnum;      // 顶点数量和边的数量

public:
    // 创建邻接表表示的图
    void CreateGraph()
    {
        cout << "输入节点数量和边的数量" << endl;
        cin >> VexNum >> arcnum;

        // 初始化顶点数组
        vertices.resize(VexNum);
        cout << "依次输入节点的值" << endl;
        for (int i = 0; i < VexNum; i++)
        {
            cin >> vertices[i].data;
            vertices[i].first = nullptr;
        }
        cout << "依次输入边的端点和权值" << endl;
        for (int k = 0; k < arcnum; k++)
        {
            int v1, v2, w;
            cin >> v1 >> v2 >> w;

            // 插入边v1 -> v2
            Edge *newEdge = new Edge;
            newEdge->adjvex = v2;
            newEdge->weight = w;
            newEdge->next = vertices[v1].first;
            vertices[v1].first = newEdge;

            // 无向图需要对称插入边v2 -> v1
            newEdge = new Edge;
            newEdge->adjvex = v1;
            newEdge->weight = w;
            newEdge->next = vertices[v2].first;
            vertices[v2].first = newEdge;
        }
    }

    // 打印邻接表
    void display()
    {
        for (int i = 0; i < VexNum; i++)
        {
            cout << vertices[i].data << " : ";
            Edge *p = vertices[i].first;
            while (p)
            {
                cout << "(" << p->adjvex << ", " << p->weight << ") ";
                p = p->next;
            }
            cout << endl;
        }
    }
};

struct Graph
{
    int vexs[MAXN];       // 节点值
    int arcs[MAXN][MAXN]; // 权值
    int VexNum, arcnum;   // 节点数量和边的数量
};

class AdjGraph
{
private:
    Graph *G;

public:
    AdjGraph() : G(nullptr) {}

    ~AdjGraph()
    {
        destroyGraph();
    }

    // 创建邻接矩阵表示的图
    void CreateGraph()
    {
        G = new Graph;
        cout << "输入节点的数量和边的数量" << endl;
        cin >> G->VexNum >> G->arcnum;
        cout << "依次输入节点的值" << endl;
        for (int i = 0; i < G->VexNum; i++)
        {
            cin >> G->vexs[i];
            // 初始化值为INF
            for (int j = 0; j < G->VexNum; j++)
            {
                G->arcs[i][j] = INF;
            }
        }
        cout << "依次输入边的端点和权值" << endl;
        for (int k = 0; k < G->arcnum; k++)
        {
            int v1, v2, w;
            cin >> v1 >> v2 >> w;
            G->arcs[v1][v2] = w;
            G->arcs[v2][v1] = w; // 对称赋值
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

    // 打印图
    void display()
    {
        for (int i = 0; i < G->VexNum; i++)
        {
            for (int j = 0; j < G->VexNum; j++)
            {
                if (G->arcs[i][j] == INF)
                {
                    cout << "INF ";
                }
                else
                {
                    cout << G->arcs[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

    // 求顶点的度
    int Degree1(int v)
    {
        int d = 0;
        for (int i = 0; i < G->VexNum; i++)
        {
            if (G->arcs[v][i] != INF && G->arcs[v][i] != 0)
            {
                d++;
            }
        }
        return d;
    }

    // 深度优先遍历
    void DFS(int v)
    {
        vector<bool> visited(G->VexNum, false);
        DFS1(v, visited);
        cout << endl;
    }

    void DFS1(int v, vector<bool> &visited)
    {
        visited[v] = true;
        cout << v << " ";

        for (int i = 0; i < G->VexNum; i++)
        {
            if (G->arcs[v][i] != INF && !visited[i])
            {
                DFS1(i, visited);
            }
        }
    }

    // 广度优先遍历
    void BFS(int v)
    {
        vector<bool> visited(G->VexNum, false);
        queue<int> q;

        visited[v] = true;
        q.push(v);
        cout << v << " ";

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int i = 0; i < G->VexNum; i++)
            {
                if (G->arcs[u][i] != INF && !visited[i])
                {
                    visited[i] = true;
                    q.push(i);
                    cout << i << " ";
                }
            }
        }
        cout << endl;
    }

    int GetVexNum()
    {
        if (G)
        {
            return G->VexNum;
        }
        return 0;
    }

    // Prim
    void Prim(int startNode)
    {
        // 存节点到最小生成树的最小边权值
        vector<int> lowcost(G->VexNum, INF);
        // 存节点在最小生成树中的父节点
        vector<int> parent(G->VexNum, -1);
        // 标记节点是否在树中
        vector<bool> inMST(G->VexNum, false);

        // 初始化
        lowcost[startNode] = 0;

        // 循环直到所有节点都在最小生成树中
        for (int count = 0; count < G->VexNum; ++count)
        {
            // 找不在MST中且有最小lowcost的节点
            int u = -1;
            for (int v = 0; v < G->VexNum; ++v)
            {
                if (!inMST[v] && (u == -1 || lowcost[v] < lowcost[u]))
                {
                    u = v;
                }
            }

            if (u == -1)
                break;

            // 将u标记为在树中
            inMST[u] = true;

            // 如果u有父节点，输出边
            if (parent[u] != -1)
            {
                cout << parent[u] << " - " << u << " : " << lowcost[u] << endl;
            }

            // 更新u的临界节点的lowcost和parent
            for (int v = 0; v < G->VexNum; ++v)
            {
                if (!inMST[v] && G->arcs[u][v] < lowcost[v])
                {
                    lowcost[v] = G->arcs[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    // Kruskal
    void Kruskal()
    {
        // 存边的结构体
        struct Edge
        {
            int u, v, weight;
        };

        // 存所有边
        vector<Edge> edges;
        for (int u = 0; u < G->VexNum; ++u)
        {
            for (int v = u + 1; v < G->VexNum; ++v)
            {
                if (G->arcs[u][v] != INF)
                {
                    edges.push_back({u, v, G->arcs[u][v]});
                }
            }
        }

        // 按照权对边进行排序
        sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
             { return a.weight < b.weight; });

        // 初始化每个节点的父节点为自身
        vector<int> parent(G->VexNum);
        for (int i = 0; i < G->VexNum; ++i)
        {
            parent[i] = i;
        }

        // 主逻辑
        for (const Edge &edge : edges)
        {
            // 找边的两个点所在集合的根节点
            int rootU = findSet(parent, edge.u);
            int rootV = findSet(parent, edge.v);

            // 如果两个节点不同，则边不会形成环，加入树
            if (rootU != rootV)
            {
                cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
                parent[rootU] = rootV;
            }
        }
    }

    // 查找函数
    int findSet(vector<int> &parent, int i)
    {
        return (parent[i] == i) ? i : (parent[i] = findSet(parent, parent[i]));
    }

    // Dijkstra算法求单源最短路径
    void Dijkstra(int startNode)
    {
        // 存源点到各节点的最短距离，初始化为INF
        vector<int> D(G->VexNum, INF);
        // 节点是否找到最短路径，初始化为false
        vector<bool> S(G->VexNum, false);
        // 存每个节点的前驱节点，初始化为-1
        vector<int> Path(G->VexNum, -1);

        // 源点到自身的距离为0
        D[startNode] = 0;
        // 记源点已找到最短路径
        S[startNode] = true;

        // 初始化
        for (int v = 0; v < G->VexNum; v++)
        {
            if (G->arcs[startNode][v] != INF)
            {
                D[v] = G->arcs[startNode][v];
                Path[v] = startNode;
            }
        }

        // 主循环
        for (int count = 0; count < G->VexNum - 1; count++)
        {
            // 选择下一顶点v
            int v = -1;
            int minDist = INF;
            for (int w = 0; w < G->VexNum; w++)
            {
                if (!S[w] && D[w] < minDist)
                {
                    v = w;
                    minDist = D[w];
                }
            }

            // 节点v已找到
            S[v] = true;

            // 更新与v相邻的顶点的距离
            for (int w = 0; w < G->VexNum; w++)
            {
                if (!S[w] && G->arcs[v][w] != INF && D[v] + G->arcs[v][w] < D[w])
                {
                    D[w] = D[v] + G->arcs[v][w];
                    Path[w] = v;
                }
            }
        }

        // 输出
        cout << "从节点 " << startNode << " 出发的最短路径长度:" << endl;
        for (int i = 0; i < G->VexNum; ++i)
        {
            cout << "到节点 " << i << ": " << (D[i] == INF ? "INF" : to_string(D[i])) << endl;
        }
    }

    // Floyd算法求多源最短路径
    void Floyd()
    {
        // 初始化，存各节点间的最短距离，初始化为INF
        vector<vector<int>> D(G->VexNum, vector<int>(G->VexNum, INF));
        // 存节点的前驱节点，初始化为-1
        vector<vector<int>> Path(G->VexNum, vector<int>(G->VexNum, -1));

        // 初始化
        for (int i = 0; i < G->VexNum; ++i)
        {
            D[i][i] = 0;
            for (int j = 0; j < G->VexNum; ++j)
            {
                if (G->arcs[i][j] != INF)
                {
                    D[i][j] = G->arcs[i][j];
                    Path[i][j] = i;
                }
            }
        }

        for (int k = 0; k < G->VexNum; ++k)
        {
            for (int i = 0; i < G->VexNum; ++i)
            {
                for (int j = 0; j < G->VexNum; ++j)
                {
                    if (D[i][k] != INF && D[k][j] != INF && D[i][k] + D[k][j] < D[i][j])
                    {
                        D[i][j] = D[i][k] + D[k][j];
                        Path[i][j] = Path[k][j];
                    }
                }
            }
        }

        // 输出结果
        cout << "多源最短路径矩阵:" << endl;
        for (int i = 0; i < G->VexNum; ++i)
        {
            for (int j = 0; j < G->VexNum; ++j)
            {
                cout << setw(4) << (D[i][j] == INF ? "INF" : to_string(D[i][j])) << " ";
            }
            cout << endl;
        }
    }

    // 针对无权图的单源最短路径（这里简单使用类似BFS的思路实现）
    void migong(int startNode)
    {
        vector<int> dist(G->VexNum, -1);
        queue<int> q;

        dist[startNode] = 0;
        q.push(startNode);

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int v = 0; v < G->VexNum; v++)
            {
                if (G->arcs[u][v] != INF && dist[v] == -1)
                {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }

        cout << "从节点 " << startNode << " 出发的最短路径长度:" << endl;
        for (int i = 0; i < G->VexNum; ++i)
        {
            cout << "到节点 " << i << ": " << (dist[i] == -1 ? "INF" : to_string(dist[i])) << endl;
        }
    }
};

int main()
{

    AdjListGraph graph;
    graph.CreateGraph();
    graph.display();

    AdjGraph adjGraph;
    adjGraph.CreateGraph();

    cout << "邻接矩阵:" << endl;
    adjGraph.display();

    int startNode;
    cout << "请输入起始节点 (0-" << adjGraph.GetVexNum() - 1 << "): ";
    cin >> startNode;

    cout << "深度优先遍历 (DFS): " << endl;
    adjGraph.DFS(startNode);

    cout << "广度优先遍历 (BFS): ";
    adjGraph.BFS(startNode);

    cout << "Prim 算法 (起始节点 0):" << endl;
    adjGraph.Prim(0);

    cout << "Kruskal 算法:" << endl;
    adjGraph.Kruskal();

    cout << "Dijkstra 算法 (起始节点 0):" << endl;
    adjGraph.Dijkstra(0);

    cout << "Floyd 算法:" << endl;
    adjGraph.Floyd();

    cout << "无权图单源最短路径 (起始节点 0):" << endl;
    adjGraph.migong(0);

    return 0;
}