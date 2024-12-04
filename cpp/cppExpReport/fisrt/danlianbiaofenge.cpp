#include <iostream>  
#include <cstdlib>  
#include <ctime>  
using namespace std;  

// 链表节点  
struct ListNode {  
    int data;  
    ListNode* next;  
    ListNode(int val) : data(val), next(nullptr) {}  
};  

// 链表类  
class LinkedList {  
private:  
    ListNode* head;  

public:  
    LinkedList() : head(nullptr) {}  

    // 生成随机数并插入链表  
    void generateRandomNumbers(int count) {  
        for (int i = 0; i < count; i++) {  
            int num = rand() % 900 + 100; // 生成100到999之间的随机数  
            insertAtEnd(num);  
        }  
    }  

    // 在链表末尾插入节点  
    void insertAtEnd(int value) {  
        ListNode* newNode = new ListNode(value);  
        if (!head) {  
            head = newNode;  
        } else {  
            ListNode* temp = head;  
            while (temp->next) {  
                temp = temp->next;  
            }  
            temp->next = newNode;  
        }  
    }  

    // 输出链表内容  
    void display() {  
        ListNode* temp = head;  
        while (temp) {  
            cout << temp->data << " ";  
            temp = temp->next;  
        }  
        cout << endl;  
    }  

    // 按基准值分割链表  
    void partition(int pivot) {  
        ListNode* lessHead = nullptr;  
        ListNode* lessTail = nullptr;  
        ListNode* greaterHead = nullptr;  
        ListNode* greaterTail = nullptr;  

        ListNode* current = head;  
        while (current) {  
            if (current->data < pivot) {  
                if (!lessHead) {  
                    lessHead = lessTail = current;  
                } else {  
                    lessTail->next = current;  
                    lessTail = lessTail->next;  
                }  
            } else {  
                if (!greaterHead) {  
                    greaterHead = greaterTail = current;  
                } else {  
                    greaterTail->next = current;  
                    greaterTail = greaterTail->next;  
                }  
            }  
            current = current->next;  
        }  

        if (lessTail) {  
            lessTail->next = greaterHead; // 连接两个部分  
            head = lessHead; // 更新头指针  
        } else {  
            head = greaterHead; // 如果没有小于基准的部分  
        }  

        if (greaterTail) {  
            greaterTail->next = nullptr; // 结束链表  
        }  
    }  

    // 析构函数，释放链表内存  
    ~LinkedList() {  
        while (head) {  
            ListNode* temp = head;  
            head = head->next;  
            delete temp;  
        }  
    }  
};  

int main() {  
    srand(static_cast<unsigned int>(time(0))); // 设置随机种子  

    // 生成随机数并存入单链表  
    LinkedList list;  
    list.generateRandomNumbers(10);  
    cout << "生成的链表内容: ";  
    list.display();  

    int pivot;  
    cout << "请输入基准值: ";  
    cin >> pivot;  
    list.partition(pivot);  
    cout << "分割后的链表内容: ";  
    list.display();  

    return 0;  
}