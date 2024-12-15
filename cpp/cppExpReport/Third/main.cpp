#include <iostream>
#define Maxint 32767
#define MVnum 100
#include<vector>
using namespace std;

struct Graph
{
    int vexs[MVnum];//节点值
    int arcs[MVnum][MVnum];//权值
    int vexnum, arcnum;//节点数量和边的数量
} AMGraph;

struct GraphNode{
    int adjvex;//所指顶点的值
    GraphNode *nexttrac;//指向下一条边的指针
    int info;//边的信息，这个实验是权值
};

struct G{
    int numvex;
    vector<GraphNode*> GraphNodelist;
};

void CreateUDG(G&G){
    
}
void CreateUDN(Graph &G)
{
    cin >> G.vexnum >> G.arcnum;
    for (int i = 0; i < G.vexnum; i++) // 节点的值
    {
        cin >> G.vexs[i];
    }

    for (int k = 0; k < G.arcnum; k++) // 权值的初始化
    {
        int v1, v2, w = 0;
        cin >> v1 >> v2 >> w;
        G.arcs[v1][v2] = w;
        G.arcs[v2][v1] = w;
    }
}

void prtUDG(Graph &G)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        cout << "    "<<i + 1 << "    ";
    }
    cout << endl;
    for (int i = 0; i < G.vexnum; i++)
    {
        cout << i + 1;
        for (int j = 0; j < G.vexnum; j++)
        {
            cout <<"   "<< G.arcs[i][j] << "    ";
        }
        cout << endl;
    }
}
int main()
{
    Graph G;
    CreateUDG(G);
    prtUDG(G);
}