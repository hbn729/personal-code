#include <iostream>
#include <cstdlib>
#include <ctime>
#include <list>

using namespace std;

// 交换
template <typename T>
void Swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

// 直接插入排序
template <typename T>
pair<int, int> insert(T arr[], int n)
{
    pair<int, int> p1(0, 0); // first是比较，second是移动,后面的排序算法都如此
    for (int i = 1; i < n; ++i)
    {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            p1.first++;
            arr[j + 1] = arr[j];
            p1.second++;
            j--;
        }
        arr[j + 1] = key;
        p1.second++;
    }
    return p1;
}

// 折半插入排序
template <typename T>
pair<int, int> binaryInsert(T arr[], int n)
{
    pair<int, int> p1(0, 0);
    for (int i = 1; i < n; ++i)
    {
        T key = arr[i];
        int left = 0, right = i - 1;
        while (left <= right)
        {
            p1.first++;
            int mid = (left + right) / 2;
            if (arr[mid] > key)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        for (int j = i - 1; j >= left; --j)
        {
            arr[j + 1] = arr[j];
            p1.second++;
        }
        arr[left] = key;
        p1.second++;
    }
    return p1;
}

// 希尔排序
template <typename T>
pair<int, int> shell(T arr[], int n)
{
    pair<int, int> p1(0, 0);
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; ++i)
        {
            T key = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > key)
            {
                p1.first++;
                arr[j] = arr[j - gap];
                p1.second++;
                j -= gap;
            }
            arr[j] = key;
            p1.second++;
        }
    }
    return p1;
}

// 冒泡排序
template <typename T>
pair<int, int> bubble(T arr[], int n)
{
    pair<int, int> p1(0, 0);
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            p1.first++;
            if (arr[j] > arr[j + 1])
            {
                Swap(arr[j], arr[j + 1]);
                p1.second++;
            }
        }
    }
    return p1;
}

// 快速排序的划分操作
template <typename T>
int partition(T arr[], int low, int high, int &compare, int &move)
{
    T pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j)
    {
        compare++;
        if (arr[j] <= pivot)
        {
            i++;
            Swap(arr[i], arr[j]);
            move++;
        }
    }
    Swap(arr[i + 1], arr[high]);
    move++;
    return i + 1;
}

// 快速排序
template <typename T>
pair<int, int> quick(T arr[], int low, int high)
{
    int compare = 0;
    int move = 0;
    if (low < high)
    {
        int pi = partition(arr, low, high, compare, move);
        pair<int, int> p1 = quick(arr, low, pi - 1);
        pair<int, int> p2 = quick(arr, pi + 1, high);
        compare += p1.first + p2.first;
        move += p1.second + p2.second;
    };
    return make_pair(compare, move);
}

// 选择排序
template <typename T>
pair<int, int> selection(T arr[], int n)
{
    pair<int, int> p1(0, 0);
    for (int i = 0; i < n - 1; ++i)
    {
        int min_index = i;
        for (int j = i + 1; j < n; ++j)
        {
            p1.first++;
            if (arr[j] < arr[min_index])
            {
                min_index = j;
            }
        }
        if (min_index != i)
        {
            Swap(arr[i], arr[min_index]);
            p1.second++;
        }
    }
    return p1;
}

// 堆排序
template <typename T>
void heapify(T arr[], int n, int i, int &compare, int &move)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest])
    {
        compare++;
        largest = l;
    }
    if (r < n && arr[r] > arr[largest])
    {
        compare++;
        largest = r;
    }
    if (largest != i)
    {
        Swap(arr[i], arr[largest]);
        move++;
        heapify(arr, n, largest);
    }
}

template <typename T>
pair<int, int> heap(T arr[], int n)
{
    int compare = 0;
    int move = 0;
    for (int i = n / 2 - 1; i >= 0; --i)
    {
        heapify(arr, n, i, compare, move);
    };
    for (int i = n - 1; i > 0; --i)
    {
        Swap(arr[0], arr[i]);
        move++;
        heapify(arr, i, 0, compare, move);
    };
    return make_pair(compare, move);
}

// 归并排序，合并
template <typename T>
void merge(T arr[], int l, int m, int r, int &compare, int &move)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    T *L = new T[n1];
    T *R = new T[n2];
    for (int i = 0; i < n1; ++i)
    {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; ++j)
    {
        R[j] = arr[m + 1 + j];
    }
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        compare++;
        if (L[i] <= R[j])
        {
            arr[k] = L[i];

            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        move++;
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        move++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        move++;
        k++;
    }
    delete[] L;
    delete[] R;
}

// 归并
template <typename T>
pair<int, int> mergeSort(T arr[], int l, int r)
{
    int move = 0;
    int compare = 0;
    if (l < r)
    {

        int m = l + (r - l) / 2;
        pair<int, int> p1 = mergeSort(arr, l, m);
        pair<int, int> p2 = mergeSort(arr, m + 1, r);
        compare += p1.first + p2.first;
        move += p1.second + p2.second;
        merge(arr, l, m, r, compare, move);
    }
    return make_pair(compare, move);
}

// 基数排序
template <typename T>
pair<int, int> radix(T arr[], int n)
{
    int max_num = arr[0];
    pair<int, int> p1(0, 0);
    for (int i = 1; i < n; ++i)
    {
        if (arr[i] > max_num)
        {
            max_num = arr[i];
        }
    }
    for (int exp = 1; max_num / exp > 0; exp *= 10)
    {
        T *output = new T[n];
        int count[10] = {0};

        for (int i = 0; i < n; ++i)
        {
            int digit = (arr[i] / exp) % 10;
            count[digit]++;
            p1.first++;
        }

        for (int i = 1; i < 10; ++i)
        {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; --i)
        {
            int digit = (arr[i] / exp) % 10;
            output[count[digit] - 1] = arr[i];
            p1.second++;
            count[digit]--;
        }

        for (int i = 0; i < n; ++i)
        {
            arr[i] = output[i];
            p1.second++;
        }
        delete[] output;
    }
    return p1;
}

// 顺序查找（链表）
void sqSearchList(list<char> &lst, char target, bool &found, int &position)
{
    int pos = 0;
    for (char c : lst)
    {
        if (c == target)
        {
            found = true;
            position = pos;
            return;
        }
        pos++;
    }
    found = false;
    position = -1;
}
// 顺序查找（数组，哨兵）
void sqSearchArray(char arr[], int n, char target, bool &found, int &position)
{
    arr[n] = target; // 设置哨兵
    int i = 0;
    while (arr[i] != target)
    {
        i++;
    }
    if (i < n)
    {
        found = true;
        position = i;
    }
    else
    {
        found = false;
        position = -1;
    }
}

// 折半查找（使用数组实现，查找前元素先排序）
void binarySearch(char arr[], int n, char target, bool &found, int &position)
{
    int left = 0, right = n - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (arr[mid] == target)
        {
            found = true;
            position = mid;
            return;
        }
        else if (arr[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    found = false;
    position = -1;
}

// 二叉查找树节点结构体
struct TreeNode
{
    char val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(char x) : val(x), left(NULL), right(NULL) {}
};

// 插入节点到二叉查找树
TreeNode *insert(TreeNode *root, char val)
{
    if (root == NULL)
    {
        return new TreeNode(val);
    }
    if (val < root->val)
    {
        root->left = insert(root->left, val);
    }
    else
    {
        root->right = insert(root->right, val);
    }
    return root;
}

// 先序遍历二叉查找树
void pre(TreeNode *root)
{
    if (root != NULL)
    {
        cout << root->val << " ";
        pre(root->left);
        pre(root->right);
    }
}

// 中序遍历二叉查找树
void inorder(TreeNode *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        inorder(root->right);
        cout << root->val << " ";
    }
}

// 在二叉查找树中查找节点并返回比较次数
bool search(TreeNode *root, char target, int &compare)
{
    TreeNode *cur = root;
    while (cur != NULL)
    {
        compare++;
        if (cur->val == target)
        {
            return true;
        }
        else if (cur->val > target)
        {
            cur = cur->left;
        }
        else
        {
            cur = cur->right;
        }
    }
    return false;
}

// 删除二叉查找树中的节点（简单实现，未考虑复杂情况）
TreeNode *deleteNode(TreeNode *root, char target)
{
    if (root == NULL)
    {
        return root;
    }
    if (target < root->val)
    {
        root->left = deleteNode(root->left, target);
    }
    else if (target > root->val)
    {
        root->right = deleteNode(root->right, target);
    }
    else
    {
        if (root->left == NULL)
        {
            TreeNode *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            TreeNode *temp = root->left;
            delete root;
            return temp;
        }
        TreeNode *temp = root->right;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        root->val = temp->val;
        root->right = deleteNode(root->right, temp->val);
    }
    return root;
}

// 哈希查找（使用除留余数法、开放地址法中的线性探测法）
const int Size = 100;
class Hash
{
public:
    int table[Size];
    bool isEmpty[Size];
    Hash()
    {
        for (int i = 0; i < Size; ++i)
        {
            isEmpty[i] = true;
        }
    }
    int hashFunc(int key)
    {
        return key % Size;
    }
    pair<bool, int> hashSearch(int key)
    {
        int compare = 0;
        int index = hashFunc(key);
        int start_index = index;
        while (!isEmpty[index])
        {
            compare++;
            if (table[index] == key)
            {
                return make_pair(true, compare);
            }
            index = (index + 1) % Size;
            if (index == start_index)
            {
                break;
            }
        }
        return make_pair(false, compare);
    }
    void insert(int key)
    {
        int index = hashFunc(key);
        int start_index = index;
        while (!isEmpty[index])
        {
            index = (index + 1) % Size;
            if (index == start_index)
            {
                cout << "Hash table is full!" << endl;
                return;
            }
        }
        table[index] = key;
        isEmpty[index] = false;
    }
};

int main()
{

    srand(time(nullptr));
    int arr[16];
    for (int i = 0; i < 16; i++)
    {
        arr[i] = rand() % 90 + 10;
    }

    cout << "原数组: ";
    for (int num : arr)
    {
        cout << num << " ";
    }
    cout << endl;

    // 冒泡
    // pair<int, int> p = bubble(arr, 16);

    // 折半插入
    // pair<int, int> p = binaryInsert(arr, 16);

    // 直接插入
    // pair<int, int> p = insert(arr, 16);

    // 希尔
    // pair<int, int> p = shell(arr, 16);

    // 选排
    // pair<int, int> p = selection(arr, 16);

    // 快排
    //  pair<int, int> p = quick(arr, 16);

    // 归并
    pair<int, int> p = mergeSort(arr, 0, 15);

    //   基数
    //   pair<int, int> p = radix(arr, 16);

    cout << "比较次数：" << p.first << "移动次数：" << p.second << endl;
    cout << "排序结果: ";
    for (int i = 0; i < 16; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    list<char> charList;
    char used[26] = {0};
    srand(time(nullptr));

    for (int i = 0; i < 16; ++i)
    {
        char c;
        do
        {
            c = 'a' + rand() % 26;
        } while (used[c - 'a']);
        used[c - 'a'] = 1;
        charList.push_back(c);
    }

    cout << "链表中的字符: ";
    for (char c : charList)
    {
        cout << c << " ";
    }

    cout << endl;
    char target;
    cout << "请输入要查找的字符: ";
    cin >> target;
    bool wasfound;
    int index;
    sqSearchList(charList, target, wasfound, index);
    if (wasfound)
    {
        cout << "在链表中找到字符 " << target << "，位置是 " << index << endl;
    }
    else
    {
        cout << "在链表中未找到字符 " << target << endl;
    }

    // 使用数组实现，并设置哨兵机制
    char charArray[17];
    int Index = 0;
    for (int i = 0; i < 16; ++i)
    {
        do
        {
            char c = 'a' + rand() % 26;
            bool isChongfu = false;
            for (int j = 0; j < index; ++j)
            {
                if (charArray[j] == c)
                {
                    isChongfu = true;
                    break;
                }
            }
            if (!isChongfu)
            {
                charArray[index++] = c;
            }
        } while (index < 16);
    }

    cout << "数组中的字符: ";

    for (int i = 0; i < 16; ++i)
    {
        cout << charArray[i] << " ";
    }

    cout << endl;
    cout << "请输入要查找的字符: ";
    cin >> target;

    bool foundArray;
    int positionArray;

    sqSearchArray(charArray, 16, target, foundArray, positionArray);
    if (foundArray)
    {
        cout << "在数组中找到字符 " << target << "，位置是 " << positionArray << endl;
    }
    else
    {
        cout << "在数组中未找到字符 " << target << endl;
    }

    //  折半查找
    char sortArray[16];
    for (int i = 0; i < 16; ++i)
    {
        sortArray[i] = charArray[i];
    }
    bubble(sortArray, 16);

    cout << "排序后的数组: ";
    for (int i = 0; i < 16; ++i)
    {
        cout << sortArray[i] << " ";
    }

    cout << endl;
    cout << "请输入要查找的字符: ";
    cin >> target;
    bool foundBinary;
    int positionBinary;

    binarySearch(sortArray, 16, target, foundBinary, positionBinary);
    if (foundBinary)
    {
        cout << "折半查找找到字符 " << target << "，位置是 " << positionBinary << endl;
    }
    else
    {
        cout << "折半查找未找到字符 " << target << endl;
    }

    //  二叉查找树
    TreeNode *root = nullptr;
    cout << "请依次输入10个字母: ";
    for (int i = 0; i < 10; ++i)
    {
        char input;
        cin >> input;
        root = insert(root, input);
    }

    cout << "先序遍历二叉查找树: ";
    pre(root);
    cout << endl;
    cout << "中序遍历二叉查找树: ";
    inorder(root);
    cout << endl;
    cout << "请输入要查找的字母: ";
    cin >> target;
    int compare = 0;
    if (search(root, target, compare))
    {
        cout << "找到字符 " << target << " 比较次数: " << compare << endl;
    }
    else
    {
        cout << "未找到字符 " << target << " 比较次数: " << compare << endl;
    }

    cout << "请输入要删除的字母: ";
    cin >> target;
    root = deleteNode(root, target);
    cout << "删除后先序遍历二叉查找树: ";
    pre(root);
    cout << endl;

    // 哈希查找
    Hash hashTable;
    srand(time(nullptr));
    for (int i = 0; i < 16; ++i)
    {
        int num = rand() % 90 + 10;
        hashTable.insert(num);
    }
    cout << "请输入要查找的数字: ";
    int targetNum;
    cin >> targetNum;
    pair<bool, int> result = hashTable.hashSearch(targetNum);
    if (result.first)
    {
        cout << "haxi找到数字 " << targetNum << " 比较次数: " << result.second << endl;
    }
    else
    {
        cout << "haxi未找到数字 " << targetNum << " 比较次数: " << result.second << endl;
    }

    return 0;
}
