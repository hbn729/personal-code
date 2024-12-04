#include <iostream>
#include <string>
#define element int
#include <cstdlib>
#include <ctime>
#define endl "\n"
using namespace std;

// 结点的结构体
struct ListNode
{
    element data;
    ListNode *next;
};

// 链表
class Linklist
{
private:
    ListNode *head;

public:
    // 构造函数
    Linklist()
    {
        head = new ListNode();
        head->data = 0;
        head->next = nullptr;
    }
    // 析构函数
    ~Linklist()
    {
        ListNode *p = head->next;
        while (p)
        {
            ListNode *r = p->next;
            delete p;
            p = r;
        }
        delete head;
    }

    // 将L2合并进L1
    void merge(Linklist *L2)
    {
        ListNode *p = head;
        ListNode *r = p->next;
        ListNode *c = L2->head->next;
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
        ListNode *p = head->next->next;
        ListNode *r = p->next;
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

    void test(element datatmp)
    {
        ListNode *current = head->next->next;
        ListNode *next = current->next;
        ListNode *prev = head->next;
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

        ListNode *p = head;
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
    void searchData(element datatmp)
    {

        ListNode *p = head;
        int cnt = 1;

        if (p->data == 0)
            cout << "error,Linklist is empty" << endl;
        else
        {
            while (p->next)
            {
                if (p->next->data == datatmp)
                {
                    cout << cnt << endl;
                    break;
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
    void tianjiaNode(element datatmp)
    {
        ListNode *h = head;
        ListNode *p = new ListNode();
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
    void insertData(element datatmp, int index)
    {

        ListNode *p = head;
        ListNode *pre = nullptr;

        if (((index < 1) && (head->data < index)))
        {
            cout << "error,List is empty or index error" << endl;
        }
        else
        {
            while (index--)
            {
                pre = p;
                p = p->next;
            }
            ListNode *tmp = new ListNode;
            tmp->data = datatmp;
            tmp->next = p;
            pre->next = tmp;
            head->data += 1;
        }
    }

    // 删除
    void deleteData(element datatmp)
    {

        int flag = 1; // 是否成功删除，1：否  0：是
        ListNode *p = head;
        ListNode *pre = p;

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
                cout << "data was not find" << endl;
        }
    }
};

// 栈
class stack
{
private:
    ListNode *top;

public:
    stack()
    {
        top = new ListNode();
        top->data = 0;
        top->next = nullptr;
    }

    ~stack()
    {
        while (top->next)
        {
            ListNode *p = top->next;
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

    // 获取栈顶元素
    element GetTop()
    {
        ListNode *p = top->next;
        if (top->data == 0)
        {
            cout << "stack is empty" << endl;
            return -1;
        }
        else
            return p->data;
    }

    // 入栈
    void push(element datatmp)
    {
        // 头插法
        ListNode *p = top;
        ListNode *tmp = new ListNode();
        tmp->data = datatmp;
        tmp->next = p->next;
        p->next = tmp;
        top->data += 1;
    }

    // 出栈
    element pop()
    {
        ListNode *p = top->next;
        top->next = top->next->next;
        element t = p->data;
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
class queue
{
private:
    ListNode *rear;
    ListNode *front;

public:
    queue()
    {
        rear = new ListNode();
        front = new ListNode();
        front->data = 0;
        rear->data = 0;
        rear->next = nullptr;
        front = rear;
    }
    ~queue()
    {
        while (!isEmpty())
        {
            ListNode *p = front->next;
            front->next = front->next->next;
        }
    }

    void EnQueue(element datatmp)
    {
        ListNode *tmp = new ListNode();
        tmp->data = datatmp;
        tmp->next = nullptr;
        rear->next = tmp;
        rear = tmp;
    }

    element DeQueue()
    {
        if (isEmpty())
        {
            cout << "error,no element" << endl;
            return -1;
        }
        else
        {
            element tmp = front->next->data;
            ListNode *p = front->next;
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
            for (ListNode *p = front->next; p != nullptr; p = p->next)
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
    // //链表的实现
    // Linklist L;
    // L.random(10);
    // L.print();
    //     int read = 0;
    //     cin >> read;
    //     L.searchData(read);
    //     int index = 0;
    //     cin >> read >> index;
    //     L.insertData(read, index);
    //     L.print();
    //     cin >> read;
    //     L.deleteData(read);
    //     L.print();

    // 反转链表
    // L.fanzhuan();
    // L.print();
    // // 栈的实现
    // stack T;
    // T.random(10);
    // cout << endl;
    // while (!T.isEmpty())
    // {
    //     T.GetTop();
    //     T.pop();
    // }

    // //翻转队列
    //     queue q;
    //     q.random(10);
    //     q.QueueTraverse();
    //     stack T;
    //     while (!1)
    //     {
    //         cout << 1;
    //     }
    //     while (!q.isEmpty())
    //     {
    //         T.push(q.DeQueue());
    //     }
    //     while (!T.isEmpty())
    //     {
    //         q.EnQueue(T.pop());
    //     }
    //     q.QueueTraverse();

    // //合并链表
    // Linklist L1;
    // Linklist L2;
    // for (int i = 0; i < 5; i++)
    // {
    //     L1.tianjiaNode(i);
    //     L1.tianjiaNode(i);
    // }
    // L1.print();
    // for (int i = 1; i < 6; i++)
    // {
    //     L2.tianjiaNode(i);
    //     L2.tianjiaNode(i);
    // }
    // L2.print();

    // // 合并
    // L1.merge(&L2);
    // L1.fanzhuan();
    // L1.print();

    //fenge
        Linklist L;
        L.random(10);
        L.print();
        element in;
        cin >> in;
        L.test(in);
        L.print();

    // // kuohaopipei
    // stack T;
    // string target;
    // cin >> target;
    // for (int i = 0; i < target.size(); i++)
    // {
    //     if (target[i] == '(' || target[i] == '[' || target[i] == '{')
    //     {
    //         T.push(target[i]);
    //     }

    //     else if (target[i] == ')')
    //     {
    //         if (T.GetTop() == '(')
    //             T.pop();
    //         else
    //         {
    //             cout << "error" << endl;
    //             break;
    //         }
    //     }
    //     else if (target[i] == ']')
    //     {
    //         if (T.GetTop() == '[')
    //             T.pop();
    //         else
    //         {
    //             cout << "error" << endl;
    //             break;
    //         }
    //     }
    //     else if (target[i] == '}')
    //     {
    //         if (T.GetTop() == '{')
    //             T.pop();
    //         else
    //         {
    //             cout << "error" << endl;
    //             break;
    //         }
    //     }
    // }
    // if (!T.isEmpty())
    //     cout << "error" << endl;
    // else
    //     cout << "good" << endl;
}