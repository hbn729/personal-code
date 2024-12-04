#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#define endl "\n"

using namespace std;

// 结点的结构体
template <typename T>
struct ListNode
{
    T data;
    ListNode<T> *next;
};

// 链表
template <typename T>
class Linklist
{
private:
    ListNode<T> *head;

public:
    // 构造函数
    Linklist()
    {
        head = new ListNode<T>();
        head->data = 0;
        head->next = nullptr;
    }

    // 析构函数
    ~Linklist()
    {
        ListNode<T> *p = head->next;
        while (p)
        {
            ListNode<T> *r = p->next;
            delete p;
            p = r;
        }
        delete head;
    }

    // 将L2合并进L1
    void merge(Linklist<T> *L2)
    {
        ListNode<T> *p = head;
        ListNode<T> *r = p->next;
        ListNode<T> *c = L2->head->next;

        while (r != nullptr && L2->head->next != nullptr)
        {
            if (c->data >= r->data)
            {
                p = r;
                r = r->next;
            }
            else
            {
                L2->head->next = L2->head->next->next;
                c->next = r;
                p->next = c;
                p = p->next;
                c = L2->head->next;
            }
        }

        if (L2->head->next != nullptr)
        {
            p->next = c;
            L2->head->next = nullptr;
        }
        delete r;
        L2->head->data = 0;
    }

    void fanzhuan()
    {
        ListNode<T> *p = head->next->next;
        ListNode<T> *r = p->next;
        head->next->next = nullptr;

        while (p != nullptr)
        {
            p->next = head->next;
            head->next = p;
            p = r;
            if (r != nullptr)
                r = r->next;
        }
    }

    void fenge(T datatmp)
    {
        ListNode<T> *current = head->next->next;
        ListNode<T> *next = current->next;
        ListNode<T> *prev = head->next;
        while (current)
        {
            if (current->data < datatmp)
            {
                prev->next = current->next;
                current->next = head->next;
                head->next = current;
                current = next;
                if (next == nullptr)
                    next = nullptr;
                else
                    next = next->next;
            }
            else
            {
                prev = current;
                current = next;
                if (next == nullptr)
                    next = nullptr;
                else
                    next = next->next;
            }
        }
    }

    void random(int cnt)
    {
        srand(time(0));
        for (int i = 0; i < cnt; i++)
        {
            int num = rand() % 899 + 100;
            tianjiaNode(num);
        }
    }

    // 遍历
    void print()
    {
        ListNode<T> *p = head;
        if (p->data == 0)
            cout << "error,list is empty" << endl;
        else
        {
            while (p->next)
            {
                cout << p->next->data << " ";
                p = p->next;
            }
            cout << endl;
        }
    }

    // 查找
    void searchData(T datatmp)
    {
        ListNode<T> *p = head;
        int cnt = 1;

        if (p->data == 0)
            cout << "error,Linklist is empty" << endl;
        else
        {
            while (p->next)
            {
                if (p->next->data == datatmp)
                {
                    cout << "下标：" << cnt << endl;
                    return;
                }
                else
                {
                    cnt++;
                    p = p->next;
                }
            }
            cout << "cant find this data" << endl;
        }
    }

    // 尾插法添加数据为datatmp的节点到链表中
    void tianjiaNode(T datatmp)
    {
        ListNode<T> *h = head;
        ListNode<T> *p = new ListNode<T>();
        p->data = datatmp;
        p->next = nullptr;
        while (h->next)
        {
            h = h->next;
        }
        h->next = p;
        head->data += 1;
    }

    // 指定位置插入
    void insertData(T datatmp, int index)
    {
        ListNode<T> *p = head;
        ListNode<T> *pre = nullptr;

        if (((index < 1) || (head->data < index)))
        {
            cout << "error, index error" << endl;
            return;
        }
        else
        {
            while (index--)
            {
                pre = p;
                p = p->next;
            }

            ListNode<T> *tmp = new ListNode<T>();
            tmp->data = datatmp;
            tmp->next = p;
            pre->next = tmp;
            head->data += 1;
        }
    }

    // 删除
    void deleteData(T datatmp)
    {
        int flag = 1; // 是否成功删除，1：否  0：是
        ListNode<T> *p = head;
        ListNode<T> *pre = p;
        if (p->data == 0)
            cout << "error,list is empty" << endl;
        else
        {
            while (p->next)
            {
                if (p->next->data == datatmp)
                {
                    pre = p;
                    p = p->next;
                    pre->next = p->next;
                    delete p;
                    cout << "data was deleted" << endl;
                    flag = 0;
                    break;
                }
                else
                {
                    pre = p;
                    p = p->next;
                }
            }
            if (flag)
                cout << "data was not found" << endl;
        }
    }
};

// 栈
template <typename T>
class Stack
{
private:
    ListNode<T> *top;

public:
    Stack()
    {
        top = new ListNode<T>();
        top->data = 0;
        top->next = nullptr;
    }

    ~Stack()
    {
        while (top->next)
        {
            ListNode<T> *p = top->next;
            top->next = top->next->next;
            delete p;
        }
        delete top;
    }
    // 生成count个随机数添加到zhan
    void random(int cnt)
    {
        srand(time(0));
        for (int i = 0; i < cnt; i++)
        {
            int num = rand() % 899 + 100;
            push(num);
            GetTop();
        }
    }

    T GetTop()
    {
        if (top->data == 0)
        {
            return -1;
        }
        return top->next->data;
    }

    void push(T datatmp)
    {
        // 头插法
        ListNode<T> *p = top;
        ListNode<T> *tmp = new ListNode<T>();
        tmp->data = datatmp;
        tmp->next = p->next;
        p->next = tmp;
        top->data += 1;
    }

    T pop()
    {
        if (top->data == 0)
        {
            return -1; // 返回默认值
        }
        ListNode<T> *p = top->next;
        top->next = top->next->next;
        T t = p->data;
        delete p;
        top->data -= 1;
        return t;
    }

    bool isEmpty()
    {
        if (top->data == 0)
            return 1;
        else
            return 0;
    }
};

// 队列
template <typename T>
class Queue
{
private:
    ListNode<T> *rear;
    ListNode<T> *front;

public:
    Queue()
    {
        rear = new ListNode<T>();
        front = new ListNode<T>();
        front->data = 0;
        rear->data = 0;
        rear->next = nullptr;
        front = rear;
    }

    ~Queue()
    {
        while (!isEmpty())
        {
            ListNode<T> *p = front->next;
            front->next = front->next->next;
            delete p;
        }
        delete front;
    }

    void EnQueue(T datatmp)
    {
        ListNode<T> *tmp = new ListNode<T>();
        tmp->data = datatmp;
        tmp->next = nullptr;
        rear->next = tmp;
        rear = tmp;
    }

    T DeQueue()
    {
        if (isEmpty())
        {
            cout << "error, no element" << endl;
            return -1; // 返回默认值
        }
        else
        {
            T tmp = front->next->data;
            ListNode<T> *p = front->next;
            front->next = front->next->next;
            if (front->next == nullptr)
                rear = front;
            delete p;
            return tmp;
        }
    }

    void QueueTraverse()
    {
        if (!isEmpty())
        {
            for (ListNode<T> *p = front->next; p != nullptr; p = p->next)
            {
                cout << p->data << " ";
            }
            cout << endl;
        }
        else
            cout << "queue is empty" << endl;
    }

    void random(int cnt)
    {
        srand(time(0));
        for (int i = 0; i < cnt; i++)
        {
            int num = rand() % 899 + 100;
            EnQueue(num);
        }
    }

    bool isEmpty()
    {
        return front->next == nullptr;
    }
};

int main()
{
    // 链表的实现测试
    cout << "链表的实现测试:" << endl;
    Linklist<int> L1;
    L1.random(10);
    L1.print();
    cout << "请输入要搜索的数" << endl;
    int read = 0;
    cin >> read;
    L1.searchData(read);
    cout << "请输入数据和要插入的位置" << endl;
    int index = 0;
    cin >> read >> index;
    L1.insertData(read, index);
    L1.print();
    cout << "请输入要删除的数据" << endl;
    cin >> read;
    L1.deleteData(read);
    L1.print();

    // 反转链表 :用双指针，初始化current指向首元结点的下个节点，r节点指向current的下一个节点，将首元节点的next指向nullptr，用头插法插入current节点后，再将current=r，r=r->next;，更新两个节点，while循环停止条件就是current指向nullptr的时候
    cout << "反转链表" << endl;
    Linklist<int> L2;
    L2.random(10);
    L2.print();
    L2.fanzhuan();
    L2.print();

    // 栈的实现测试
    cout << "栈的实现测试" << endl;
    Stack<int> T3;
    T3.random(10);
    cout << endl;
    while (!T3.isEmpty())
    {
        cout << T3.GetTop() << endl;
        T3.pop();
    }

    // 应用：

    // 翻转队列：将队列队头出对后入栈即可，等到队空再出栈然后入队到栈空
    cout << "翻转队列" << endl;
    Queue<int> q4;
    q4.random(10);
    q4.QueueTraverse();
    Stack<int> T5;
    while (!q4.isEmpty())
    {
        T5.push(q4.DeQueue());
    }
    while (!T5.isEmpty())
    {
        q4.EnQueue(T5.pop());
    }
    q4.QueueTraverse();

    // 合并链表：以第一个链表为合并后的链表的基础链表，用三个指针，基础链表用两个，被合并链表用一个指针从前往后扫，比较被合并链表的指针所指，如果大于基础链表，则基础链表的两个指针后移一位，如果大于，则插入那个数前面，被合并链表的指针继续更新，到最后delete一下被合并链表的表头即可。再反转一下就行了。
    cout << "合并链表" << endl;
    Linklist<int> L6;
    Linklist<int> L7;
    for (int i = 0; i < 5; i++)
    {
        L6.tianjiaNode(i);
    }
    cout << "链表1：" << endl;
    L6.print();
    for (int i = 1; i < 6; i++)
    {
        L7.tianjiaNode(i);
    }
    cout << "链表2:" << endl;
    L7.print();

    L6.merge(&L7);
    L6.fanzhuan();
    cout << "合并和翻转后：" << endl;
    L6.print();

    // 分割链表,从首元结点的下一个节点开始往后扫比较大小，如果小于基准数就用三个指针进行头插法移位，否则进行下一个更新，分别是prev指针，current指针，next指针。
    cout << "分割链表:" << endl;
    Linklist<int> L8;
    L8.random(10);
    L8.print();
    int in;
    cout << "输入基准数" << endl;
    cin >> in;
    L8.fenge(in);
    L8.print();

    // 括号匹配，一个栈存左括号，每扫到一个右括号就和栈顶进行比较，不匹配直接return错误，匹配直接出栈进行下一个字符的比较。最后判断一下栈是否为空再报错，防止遗漏情况
    cout << "括号匹配" << endl;
    Stack<char> T9;
    string target;
    cin >> target;
    for (int i = 0; i < target.size(); i++)
    {
        if (target[i] == '(' || target[i] == '[' || target[i] == '{')
        {
            T9.push(target[i]);
        }

        else if (target[i] == ')')
        {
            if (T9.GetTop() == '(')
                T9.pop();
            else
            {
                cout << "error" << endl;
                T9.pop();
                break;
            }
        }
        else if (target[i] == ']')
        {
            if (T9.GetTop() == '[')
                T9.pop();
            else
            {
                cout << "error" << endl;
                T9.pop();
                break;
            }
        }
        else if (target[i] == '}')
        {
            if (T9.GetTop() == '{')
                T9.pop();
            else
            {
                cout << "error" << endl;
                T9.pop();
                break;
            }
        }
    }
    if (!T9.isEmpty())
        cout << "error";
}