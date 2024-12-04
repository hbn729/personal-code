#include <iostream>  
#include <cstdlib>  
#include <ctime>  
using namespace std;  

// 队列节点  
struct QueueNode {  
    int data;  
    QueueNode* next;  
    QueueNode(int val) : data(val), next(nullptr) {}  
};  

// 队列类  
class Queue {  
private:  
    QueueNode* front;  
    QueueNode* rear;  

public:  
    Queue() : front(nullptr), rear(nullptr) {}  

    // 入队操作  
    void enqueue(int value) {  
        QueueNode* newNode = new QueueNode(value);  
        if (rear) {  
            rear->next = newNode;  
        } else {  
            front = newNode; // 如果队列为空  
        }  
        rear = newNode;  
    }  

    // 出队操作  
    int dequeue() {  
        if (!front) {  
            throw runtime_error("队列为空");  
        }  
        int value = front->data;  
        QueueNode* temp = front;  
        front = front->next;  
        if (!front) {  
            rear = nullptr; // 如果队列为空，更新 rear  
        }  
        delete temp;  
        return value;  
    }  

    // 输出队列内容  
    void display() {  
        QueueNode* temp = front;  
        while (temp) {  
            cout << temp->data << " ";  
            temp = temp->next;  
        }  
        cout << endl;  
    }  

    // 翻转队列  
    void reverse() {  
        QueueNode* prev = nullptr;  
        QueueNode* current = front;  
        rear = front; // 更新 rear 为原来的 front  
        while (current) {  
            QueueNode* next = current->next; // 保存下一个节点  
            current->next = prev; // 反转指针  
            prev = current; // 移动 prev  
            current = next; // 移动 current  
        }  
        front = prev; // 更新 front 为新的头  
    }  

    // 析构函数，释放队列内存  
    ~Queue() {  
        while (front) {  
            QueueNode* temp = front;  
            front = front->next;  
            delete temp;  
        }  
    }  
};  

int main() {  
    srand(static_cast<unsigned int>(time(0))); // 设置随机种子  

    // 1. 生成随机数并入队  
    Queue queue;  
    cout << "生成的随机数: ";  
    for (int i = 0; i < 10; i++) {  
        int num = rand() % 900 + 100; // 生成100到999之间的随机数  
        queue.enqueue(num);  
        cout << num << " ";  
    }  
    cout << endl;  

    // 2. 遍历输出队列内容  
    cout << "队列内容: ";  
    queue.display();  

    // 3. 翻转队列并输出  
    queue.reverse();  
    cout << "翻转后的队列内容: ";  
    queue.display();  

    return 0;  
}