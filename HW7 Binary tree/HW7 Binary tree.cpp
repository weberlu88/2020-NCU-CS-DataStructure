// HW7 Binary tree.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

const string EMPTY_TREE("Tree is empty");
const string INVALID_TREE("Invalid tree");

class node {
public:
    int val;
    struct node* left;
    struct node* right;
    // Construtor: New node creation
    node(int _v) : val(_v), left(nullptr), right(nullptr) {};

    // Create leftchild and rightchild for the target node
    void createLeaf(int left, int right);

    // Find and return the target node, if not existed return NULL
    node* search(int value);
};

// Traverse Preorder (left > mid > right)
void traversePreOrder(node* temp);

// Traverse Inorder
void traverseInOrder(node* temp);

// Traverse Postorder
void traversePostOrder(node* temp);

int main()
{
    struct node* root = new node(1);
    root->left = new node(2);
    root->right = new node(3);
    root->left->left = new node(4);
}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
