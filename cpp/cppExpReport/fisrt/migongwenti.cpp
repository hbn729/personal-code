#include <iostream>  
#include <queue>  
#include <vector>  
using namespace std;  

const int N = 8; // 迷宫大小  
int maze[N][N] = {  
    {0, 1, 1, 1, 1, 1, 1, 1},  
    {0, 0, 0, 1, 0, 0, 0, 0},  
    {1, 1, 0, 1, 0, 1, 1, 1},  
    {1, 0, 0, 0, 0, 0, 1, 0},  
    {1, 1, 1, 1, 1, 0, 1, 0},  
    {1, 0, 0, 1, 0, 0, 0, 0},  
    {1, 1, 0, 1, 1, 1, 1, 1},  
    {1, 0, 0, 0, 0, 0, 0, 0}  
};  

struct Point {  
    int x, y; // 坐标  
    Point(int x, int y) : x(x), y(y) {}  
};  

// 输出迷宫  
void printMaze() {  
    for (int i = 0; i < N; i++) {  
        for (int j = 0; j < N; j++) {  
            cout << (maze[i][j] == 0 ? '.' : '#') << " ";  
        }  
        cout << endl;  
    }  
}  

// 检查坐标是否有效  
bool isValid(int x, int y, vector<vector<bool>>& visited) {  
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 0 && !visited[x][y]);  
}  

// BFS 寻找最短路径  
void findShortestPath() {  
    queue<Point> q;  
    vector<vector<bool>> visited(N, vector<bool>(N, false));  
    vector<vector<Point>> parent(N, vector<Point>(N, Point(-1, -1))); // 存储路径  

    q.push(Point(1, 1)); // 起点  
    visited[1][1] = true;  

    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // 右，下，左，上  

    while (!q.empty()) {  
        Point current = q.front();  
        q.pop();  

        // 到达出口  
        if (current.x == 7 && current.y == 7) {  
            cout << "找到最短路径: ";  
            Point p = current;  
            while (p.x != -1 && p.y != -1) {  
                cout << "(" << p.x + 1 << ", " << p.y + 1 << ") ";  
                p = parent[p.x][p.y];  
            }  
            cout << endl;  
            return;  
        }  

        for (auto& dir : directions) {  
            int newX = current.x + dir[0];  
            int newY = current.y + dir[1];  

            if (isValid(newX, newY, visited)) {  
                visited[newX][newY] = true;  
                q.push(Point(newX, newY));  
                parent[newX][newY] = current; // 记录路径  
            }  
        }  
    }  

    cout << "没有路径" << endl;  
}  

int main() {  
    cout << "迷宫布局:" << endl;  
    printMaze();  

    findShortestPath();
}