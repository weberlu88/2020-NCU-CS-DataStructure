// HW7 Binary tree.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
// @Author: MIS Senior - Weber Lu

#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;

const string EMPTY_TREE("Tree is empty");
const string INVALID_TREE("Invalid tree");

class node {
public:
    int val;
    node* left;
    node* right;
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

// Recursive function to calculate height of given binary tree. Complexity : O(n)
int height(node* root);

// Calculate amounts of leaves. Complexity : O(n)
int leafCount(node* root);

int main()
{
    /* Test Code
    node* root = new node(1);
    root->left = new node(2);
    root->right = new node(3);
    root->left->left = new node(4); 
    node* find = root->search(2);
    if (find)
        cout << find->val;
    else
        cout << INVALID_TREE;
    int treeHeight = height(root);
    int leatCount = leafCount(root);
    cout << "treeHeight: " << treeHeight << ", leatCount: " << leatCount << endl;*/

    node* root = NULL; // root node of tree
    bool firstTime = true;

    // build the binary tree
    while (true) {

        // read the input command. eg. "0 1 2"
        string command;
        getline(cin, command);
        istringstream iss(command);
        vector<string> tokens {
            istream_iterator<string>{iss},
            istream_iterator<string>{}
        };

        // end of file
        if (tokens.size() == 0) 
            break;

        // target means which node to create sub-tree
        int target = stoi(tokens[0]), left = stoi(tokens[1]), right = stoi(tokens[2]);

        // adding childs, search for the target to create sub-tree, if not find throws error msg
        if (firstTime) {
            firstTime = false;
            root = new node(target);
            root->createLeaf(left, right);
        }
        else {
            node* find = root->search(target);
            if (find)
                find->createLeaf(left, right);
                // cout << find->val;
            else {
                cout << INVALID_TREE;
                return 0;
            }
        }
    } // end while

    // print the tree height and amount of leaves
    if (root == NULL)
        cout << EMPTY_TREE;
    else {
        int treeHeight = height(root);
        int leatCount = leafCount(root);
        // cout << "treeHeight: " << treeHeight << ", leatCount: " << leatCount << endl;
        cout << treeHeight << endl << leatCount << endl;
    }
}

int height(node* root) {
    // Base case: empty tree has height 0
    if (root == nullptr)
        return 0;

    // recur for left and right subtree and consider maximum depth
    return 1 + max(height(root->left), height(root->right));
}

int leafCount(node* root) {
    // Base case: if node is null, return 
    if (!root)
        return 0;

    // if node is leaf node, print its data     
    if (!root->left && !root->right)
        return 1;

    // Recursive  case: add leaf counts of left child and right child
    return leafCount(root->left) + leafCount(root->right);
}

void traversePreOrder(node* temp) {
    if (temp == NULL)
        return;

    /* first print data of node */
    cout << temp->val << " ";

    traversePreOrder(temp->left);
    traversePreOrder(temp->right);
}

void node::createLeaf(int left, int right) {
    if (left)
        this->left = new node(left);
    if (right)
        this->right = new node(right);
}

node* node::search(int value) {
    // Complexity : O(n). Need to traverse nearly whole tree, same as DFS, BFS
    // Base Cases: root is null or key is present at root (find the value!) (root means current node)
    if (this == NULL)
        return NULL;
    else if (this->val == value)
        return this;
    
    // Recursive Cases: if find in subtree return the target *ptr
    else {
        node* leftSubtreeResult = this->left->search(value);
        node* rightSubtreeResult = this->right->search(value);
        if (leftSubtreeResult)
            return leftSubtreeResult;
        else if (rightSubtreeResult)
            return rightSubtreeResult;
        else
            return NULL;
    }
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
