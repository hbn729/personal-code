#include <iostream>  
#include <cstdlib>  
#include <ctime>  
#include <stdexcept>  

using namespace std;  

// 链表节点  
struct Node {  
    int data;  
    Node* next;  
    Node(int val) : data(val), next(nullptr) {}  
};  

// 链表类  
class LinkedList {  
private:  
    Node* head;  

public:  
    LinkedList() : head(nullptr) {}  

    // 生成随机数并插入链表  
    void generateRandomNumbers(int count) {  
        srand(time(0));  
        for (int i = 0; i < count; i++) {  
            int num = rand() % 100;  // 生成0到99之间的随机数  
            insertAtEnd(num);  
        }  
    }  

    // 尾部插入  
    void insertAtEnd(int val) {  
        Node* newNode = new Node(val);  
        if (!head) {  
            head = newNode;  
        } else {  
            Node* temp = head;  
            while (temp->next) {  
                temp = temp->next;  
            }  
            temp->next = newNode;  
        }  
    }  

    // 指定位置插入  
    void insertAtPosition(int value, int position) {  
        if (position < 0) return; // 无效位置  
        Node* newNode = new Node(value);  
        if (position == 0) {  
            newNode->next = head;  
            head = newNode;  
        } else {  
            Node* temp = head;  
            for (int i = 0; i < position - 1 && temp; i++) {  
                temp = temp->next;  
            }  
            if (temp) {  
                newNode->next = temp->next;  
                temp->next = newNode;  
            }  
        }  
    }  

    // 查找值  
    int find(int value) {  
        Node* temp = head;  
        int position = 0;  
        while (temp) {  
            if (temp->data == value) {  
                return position;  
            }  
            temp = temp->next;  
            position++;  
        }  
        return -1; // 未找到  
    }  

    // 删除值  
    void deleteValue(int value) {  
        if (!head) return; // 链表为空  
        if (head->data == value) {  
            Node* temp = head;  
            head = head->next;  
            delete temp;  
            return;  
        }  
        Node* current = head;  
        while (current->next) {  
            if (current->next->data == value) {  
                Node* temp = current->next;  
                current->next = current->next->next;  
                delete temp;  
                return;  
            }  
            current = current->next;  
        }  
    }  

    // 翻转链表  
    void reverse() {  
        Node* prev = nullptr;  
        Node* current = head;  
        while (current) {  
            Node* next = current->next; // 反转指针  
            current->next = prev;  
            prev = current;  
            current = next;  
        }  
        head = prev; // 更新头指针  
    }  

    // 合并两个有序链表  
    static LinkedList merge(LinkedList& list1, LinkedList& list2) {  
        LinkedList mergedList;  
        Node* p1 = list1.head;  
        Node* p2 = list2.head;  

        while (p1 || p2) {  
            if (p1 && (!p2 || p1->data <= p2->data)) {  
                mergedList.insertAtEnd(p1->data);  
                p1 = p1->next;  
            } else {  
                mergedList.insertAtEnd(p2->data);  
                p2 = p2->next;  
            }  
        }  
        return mergedList;  
    }  

    // 输出链表内容  
    void display() {  
        Node* temp = head;  
        while (temp) {  
            cout << temp->data << " ";  
            temp = temp->next;  
        }  
        cout << endl;  
    }  

    // 析构函数，释放链表内存  
    ~LinkedList() {  
        while (head) {  
            Node* temp = head;  
            head = head->next;  
            delete temp;  
        }  
    }  
};  

// 栈节点  
struct StackNode {  
    int data;  
    StackNode* next;  
    StackNode(int val) : data(val), next(nullptr) {}  
};  

// 栈类  
class Stack {  
private:  
    StackNode* top;  

public:  
    Stack() : top(nullptr) {}  

    // 入栈操作  
    void push(int value) {  
        StackNode* newNode = new StackNode(value);  
        newNode->next = top;  
        top = newNode;  
    }  

    // 出栈操作  
    int pop() {  
        if (!top) {  
            throw runtime_error("栈为空");  
        }  
        int value = top->data;  
        StackNode* temp = top;  
        top = top->next;  
        delete temp;  
        return value;  
    }  

    // 获取栈顶元素  
    int peek() {  
        if (!top) {  
            throw runtime_error("栈为空");  
        }  
        return top->data;  
    }  

    // 检查栈是否为空  
    bool isEmpty() {  
        return top == nullptr;  
    }  

    // 输出栈内容  
    void display() {  
        StackNode* temp = top;  
        while (temp) {  
            cout << temp->data << " ";  
            temp = temp->next;  
        }  
        cout << endl;  
    }  

    // 析构函数，释放栈内存  
    ~Stack() {  
        while (top) {  
            StackNode* temp = top;  
            top = top->next;  
            delete temp;  
        }  
    }  
};  

int main() {  
    // 测试链表  
    LinkedList list;  
    list.generateRandomNumbers(10);  
    
    cout << "生成的链表内容: ";  
    list.display();  

    int searchValue;  
    cout << "请输入要查找的整数: ";  
    cin >> searchValue;  
    int position = list.find(searchValue);  
    if (position != -1) {  
        cout << searchValue << " 在链表中的位置: " << position << endl;  
    } else {  
        cout << searchValue << " 不在链表中." << endl;  
    }  

    int insertValue, insertPosition;  
    cout << "请输入要插入的整数和位置: ";  
    cin >> insertValue >> insertPosition;  
    list.insertAtPosition(insertValue, insertPosition);  
    cout << "插入后的链表内容: ";  
    list.display();  

    int deleteValue;  
    cout << "请输入要删除的整数: ";  
    cin >> deleteValue;  
    list.deleteValue(deleteValue);  
    cout << "删除后的链表内容: ";  
    list.display();  

    list.reverse();  
    cout << "翻转后的链表内容: ";  
    list.display();  

    // 合并两个有序链表示例  
    LinkedList list1, list2;  
    list1.generateRandomNumbers(5);  
    list2.generateRandomNumbers(5);  
    cout << "链表1内容: ";  
    list1.display();  
    cout << "链表2内容: ";  
    list2.display();  
    
    LinkedList mergedList = LinkedList::merge(list1, list2);  
    cout << "合并后的链表内容: ";  
    mergedList.display();  

    // 测试栈  
    Stack stack;  
    cout << "入栈的随机数: ";  
    for (int i = 0; i < 10; i++) {  
        int num = rand() % 100; // 生成0到99之间的随机数  
        stack.push(num);  
        cout << num << " ";  
    }  
    cout << endl;  

    cout << "当前栈内容: ";  
    stack.display();  

    cout << "出栈: " << stack.pop() << endl;  
    cout << "当前栈内容: ";  
    stack.display();  

    cout << "栈顶元素: " << stack.peek() << endl;  

    return 0;  
}