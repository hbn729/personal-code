#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

struct TreeNode
{
    char data;
    TreeNode *left;
    TreeNode *right;
    bool ltag;
    bool rtag;
    TreeNode(char c) : data(c), left(nullptr), right(nullptr) {}
};

struct xiansuoTreeNode
{
    char value;
    xiansuoTreeNode *left;
    xiansuoTreeNode *right;
    bool ltag;
    bool rtag;
    xiansuoTreeNode(char c) : value(c), left(nullptr), right(nullptr) {}
};


//将普通二叉树节点结构线索化
void createxiansuoTree(TreeNode *root, xiansuoTreeNode *root2)
{

    if (!root)
        return;
    root2->value = root->data;

    //递归创建左子树
    if (root->left)
    {
        xiansuoTreeNode *left2 = new xiansuoTreeNode(root->left->data);
        root2->left = left2;
    }

    //递归创建右子树
    if (root->right)
    {
        xiansuoTreeNode *right2 = new xiansuoTreeNode(root->right->data);
        root2->right = right2;
    }
    //递归调用左右子树
    createxiansuoTree(root->left, root2->left);
    createxiansuoTree(root->right, root2->right);
}

// 中序线索化二叉树
void inOrderThread(xiansuoTreeNode *node)
{
    static xiansuoTreeNode *prev2 = nullptr; // 上一个访问的节点，初始为nullptr 
    if (!node)
        return;
    // 中序递归遍历左子树
    inOrderThread(node->left);

    // 线索化当前节点的左子树  
    if (!node->left)
    {
        node->ltag = 1;     // 左子树为线索
        node->left = prev2; // 指向前驱
    }

// 线索化前驱节点的右子树
    if (prev2 && !prev2->right)
    {
        prev2->rtag = 1;     // 右子树为线索
        prev2->right = node; // 指向当前节点
    }

    prev2 = node; // 更新前驱
    // 遍历右子树
    inOrderThread(node->right);
}

void findPreNext(xiansuoTreeNode *node)
{
    if (node->ltag == 1)
    {
        cout << "前驱为：" << node->left << endl;
    }
    if (node->rtag == 1)
    {
        cout << "后继为：" << node->right << endl;
    }
    xiansuoTreeNode *p = node->left;
    xiansuoTreeNode *q = node->right;
    while (p->rtag == 0)
    { // 右子树存在，找右子树最左节点
        p = p->right;
    }
    while (q->ltag == 0)
    { // 左子树存在，找左子树最右节点
        q = q->left;
    }
    cout << "前驱为：" << p->value << endl;
    cout << "后继为：" << q->value << endl;
}

TreeNode *createTree(const string &str, int &index)
{ // 采用递归的方式进行前序创建
    if (index >= str.length() || str[index] == ')')
        return nullptr; // 左判断是否为字符串的结束位置，右判断上一个节点是否为叶子节点

    TreeNode *root = new TreeNode(str[index++]); // 创建值为当前位置的节点
    if (index < str.length() && str[index] == '(')
    {                                        // 如果下个字符是（ 代表当前节点有左子树
        index++;                             // 跳过 '('
        root->left = createTree(str, index); // 当前节点的左孩子
        if (index < str.length() && str[index] == ',')
            index++; // 如果是“ ，”代表有右子树，跳过 ','
        root->right = createTree(str, index);
        if (index < str.length() && str[index] == ')')
            index++; // 如果是）代表当前子树创建完毕，跳过 ')'
    }
    return root;
}

// 中序遍历 (递归)
void inOrderdigui(TreeNode *root)
{
    if (root)
    {
        inOrderdigui(root->left);
        cout << root->data << " ";
        inOrderdigui(root->right);
    }
}

// 中序遍历 (非递归)
// 采用栈来进行中序遍历，从根节点的左子树开始遍历，不断入栈左孩子的左孩子，每次弹出就是栈顶结点的左子树遍历完毕时，开始入栈它的右孩子的左子树直到节点为空。循环这个过程直到栈空。
void inOrderNodigui(TreeNode *root)
{
    stack<TreeNode *> s;
    TreeNode *current = root;
    while (current || !s.empty())
    { // 当前节点不为空（右子树的最后一个右孩子）或者栈不为空的判断条件
        while (current)
        {
            s.push(current);
            current = current->left;
        }
        current = s.top();
        s.pop();
        cout << current->data << " ";
        current = current->right;
    }
}

// 先序遍历 (递归)
void preOrderDigui(TreeNode *root)
{
    if (root)
    {
        cout << root->data << " ";
        preOrderDigui(root->left);
        preOrderDigui(root->right);
    }
}

// 先序遍历 (非递归)
void preOrderNoDigui(TreeNode *root)
{
    stack<TreeNode *> s;
    if (root)
        s.push(root);
    while (!s.empty())
    {
        TreeNode *node = s.top();
        s.pop();
        cout << node->data << " ";
        if (node->right)
            s.push(node->right);
        if (node->left)
            s.push(node->left);
    }
}

// 后序遍历 (递归)
void indextOrderDigui(TreeNode *root)
{
    if (root)
    {
        indextOrderDigui(root->left);
        indextOrderDigui(root->right);
        cout << root->data << " ";
    }
}

// 后序遍历 (非递归)
void indextOrderNoDigui(TreeNode *root)
{
    stack<TreeNode *> s1, s2;
    s1.push(root);
    while (!s1.empty())
    {
        TreeNode *node = s1.top();
        s1.pop();
        s2.push(node);
        if (node->left)
            s1.push(node->left);
        if (node->right)
            s1.push(node->right);
    }
    while (!s2.empty())
    {
        cout << s2.top()->data << " ";
        s2.pop();
    }
}

// 节点个数
int getNodeCount(TreeNode *root)
{
    if (!root)
        return 0;
    return 1 + getNodeCount(root->left) + getNodeCount(root->right);
}

// 叶子节点个数
int getLeafCount(TreeNode *root)
{
    if (!root)
        return 0;
    if (!root->left && !root->right)
        return 1;
    return getLeafCount(root->left) + getLeafCount(root->right);
}

// 树的高度
int getHeight(TreeNode *root)
{
    if (!root)
        return 0;
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    return 1 + max(leftHeight, rightHeight);
}

// 树的度
int getDegree(TreeNode *root)
{
    if (!root)
        return 0;
    int degree = 0;
    if (root->left)
        degree++;
    if (root->right)
        degree++;
    return max(degree, max(getDegree(root->left), getDegree(root->right)));
}

TreeNode *findNode(TreeNode *root, char datatmp)
{ // 查找值的节点
    if (!root)
        return nullptr;// 如果树为空，返回nullptr 
    if (root->data == datatmp)
        return root;// 如果当前节点就是目标节点，返回当前节点
    TreeNode *leftResult = findNode(root->left, datatmp);
    if (leftResult)
        return leftResult;// 如果左子树找到，返回  
    return findNode(root->right, datatmp);
}

void leftAndRight(TreeNode *root, char datatmp)
{ // 输出节点左孩子和右孩子的值
    TreeNode *p = findNode(root, datatmp);
    if (p)
    {
        if (p->left)
        {
            cout << p->left->data << " ";
        }
        else
        {
            cout << "空";
        }
        if (p->right)
        {
            cout << p->right->data << endl;
        }
        else
        {
            cout << "空" << endl;
        }
    }
    else
    {
        cout << "not found" << endl;
    }
}

int main()
{
    string str = "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))";
    int index = 0;
    TreeNode *root = createTree(str, index);

    cout << "中序遍历 (递归): ";
    inOrderdigui(root);
    cout << endl;

    cout << "中序遍历 (非递归): ";
    inOrderNodigui(root);
    cout << endl;

    cout << "先序遍历 (递归): ";
    preOrderDigui(root);
    cout << endl;

    cout << "先序遍历 (非递归): ";
    preOrderNoDigui(root);
    cout << endl;

    cout << "后序遍历 (递归): ";
    indextOrderDigui(root);
    cout << endl;

    cout << "后序遍历 (非递归): ";
    indextOrderNoDigui(root);
    cout << endl;
    cout << "根节点的左孩子和右孩子：" << endl;
    leftAndRight(root, 'H');
    cout << "节点个数: " << getNodeCount(root) << endl;
    cout << "叶子节点个数: " << getLeafCount(root) << endl;
    cout << "树的高度: " << getHeight(root) << endl;
    cout << "树的度: " << getDegree(root) << endl;

    xiansuoTreeNode *root2 = new xiansuoTreeNode('0');
    createxiansuoTree(root, root2);

    inOrderThread(root2);
    findPreNext(root2);
    return 0;
}