#include<iostream>
#define element int
using namespace std;

struct treeNode{
    treeNode *left;
    treeNode *right;
    element data;
};
class binarytree{
    private:
    treeNode *root;
    public:
    binarytree(){
        root->data = 0;
        root->left == nullptr;
        root->right == nullptr;
    }
    ~binarytree(){

    }
    bool bitreeisEmpty(){
        if(root->left&&root->right){
            return true;
        }
        else
            return false;
    }
};
int main(){
    return 0;
}
