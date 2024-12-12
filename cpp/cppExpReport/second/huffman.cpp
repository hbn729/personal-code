#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <map>
#include <vector>
using namespace std;

// 定义哈夫曼树结构体
struct HuffmanNode
{
    char character;                                                                          // 字符
    int freq;                                                                                // 出现的频率
    HuffmanNode *leftChild;                                                                  // 左子节点
    HuffmanNode *rightChild;                                                                 // 右子节点
    HuffmanNode(char d, int f) : character(d), freq(f), leftChild(NULL), rightChild(NULL) {} // 初始化
};

// 统计出现的频率
map<char, int> countCharFreq(string &text)
{
    map<char, int> freqMap; // 用于存储字符及频率的容器
    for (char character : text)
    {                         // 遍历字符串
        freqMap[character]++; // 如果字符在map中，对应的频率加1；
    }
    return freqMap; // 返回映射
}

// 确定优先队列中元素的比较规则
struct CompareNode
{
    bool operator()(const HuffmanNode *a, const HuffmanNode *b)
    {                             // 比较规则
        return a->freq > b->freq; // 比较两个节点的频率，返回大的频率
    }
};

// 构建哈夫曼树
HuffmanNode *buildHuffmanTree(const map<char, int> &freqMap)
{
    priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareNode> priorityQueue; // 创建一个优先队列
    for (auto &it : freqMap)
    {                                                             // 遍历频率映射，为每个字符及其频率创建HuffmanNode
        priorityQueue.push(new HuffmanNode(it.first, it.second)); // 将每个字符节点插入到优先队列中
    }

    while (priorityQueue.size() > 1)
    {                                                  // 当优先队列中还有多个节点时
        HuffmanNode *leftChild = priorityQueue.top();  // 取出频率最小的节点作为左子节点
        priorityQueue.pop();                           // 从优先队列中移除该节点
        HuffmanNode *rightChild = priorityQueue.top(); // 取出下一个频率最小的节点作为右子节点
        priorityQueue.pop();                           // 从优先队列中移除该节点
                                                       // 创建一个新的父节点，其字符数据暂时设为'\0'，频率为左右子节点频率之和
        HuffmanNode *parentNode = new HuffmanNode('\0', leftChild->freq + rightChild->freq);
        parentNode->leftChild = leftChild;   // 将左子节点连接到新父节点
        parentNode->rightChild = rightChild; // 将右子节点连接到新父节点
        priorityQueue.push(parentNode);      // 将新父节点插入到优先队列中
    }
    return priorityQueue.top(); // 返回构建好的哈夫曼树的根节点指针
}

// 生成哈夫曼编码
void generateHuffmanCodes(HuffmanNode *rootNode, string code, map<char, string> &codes)
{
    if (rootNode->character != '\0')
    {                                      // 如果当前节点是叶子节点（即character不为'\0'）
        codes[rootNode->character] = code; // 将该字符及其编码存入codes映射map中
        return;                            // 找到叶子节点后返回
    }
    generateHuffmanCodes(rootNode->leftChild, code + "0", codes);  // 编码添加 '0'，递归左子树中字符
    generateHuffmanCodes(rootNode->rightChild, code + "1", codes); // 编码添加 '1'，递归右子树中字符
}

// 对输入的文本进行哈夫曼编码，返回编码后的字符串
string huffmanEncode(const string &text, const map<char, string> &codes)
{
    string encodedText = ""; // 初始化编码后的字符串
    for (char character : text)
    {                                       // 遍历文本中的每个字符
        encodedText += codes.at(character); // 根据字符获取哈夫曼编码，并添加到编码后的字符串中
    }
    return encodedText; // 返回整体编码后的字符串
}

// 对文本进行解码
string huffmanDecode(HuffmanNode *rootNode, const string &encodedText)
{
    string decodedText = "";             // 初始化解码后的字符串
    HuffmanNode *currentNode = rootNode; // 当前节点指向树的根节点

    for (char bit : encodedText)
    { // 遍历编码后的文本中的每一位
        if (bit == '0')
        {                                         // 如果当前位是 '0'
            currentNode = currentNode->leftChild; // 在哈夫曼树中移动到当前节点的左子节点
        }
        else
        {                                          // 如果当前位是 '1'
            currentNode = currentNode->rightChild; // 在哈夫曼树中移动到当前节点的右子节点
        }

        if (currentNode->character != '\0')
        {                                          // 检查当前节点是否为叶子节点
            decodedText += currentNode->character; // 如果是叶子节点，将该节点对应的字符添加到解码后的文本中
            currentNode = rootNode;                // 重置当前节点为根节点，准备解码下一个字符
        }
    }

    return decodedText; // 返回解码后的字符串
}

int main()
{
    string inputText = "The Chinese official said he viewed the Trump Presidency not as an "
                       "aberration but as the product of a failing political system. "
                       "This jibes with other accounts. The Chinese leadership believes that "
                       "the United States, and Western democracies in general, haven’t risen "
                       "to the challenge of a globalized economy, which necessitates big changes "
                       "in production patterns, as well as major upgrades in education and public "
                       "infrastructure. In Trump and Trumpism, the Chinese see an inevitable "
                       "backlash to this failure."; // 输入文本示例

    map<char, int> freqMap = countCharFreq(inputText);           // 统计频率
    HuffmanNode *rootNode = buildHuffmanTree(freqMap);           // 构建
    map<char, string> huffmanCodes;                              // 存储编码
    generateHuffmanCodes(rootNode, "", huffmanCodes);            // 生成编码
    string encodedText = huffmanEncode(inputText, huffmanCodes); // 编码
    cout << "原始文本: " << inputText << endl;                   // 输出原始文本
    cout << "编码后的文本: " << encodedText << endl;             // 输出编码后的文本
    string decodedText = huffmanDecode(rootNode, encodedText);   // 解码
    cout << "解码后的文本: " << decodedText << endl;             // 输出解码后的文本

    return 0; // 结束程序
}