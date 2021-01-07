// Meld Two Min Leftist Trees.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
// Data Structure https://www.geeksforgeeks.org/leftist-tree-leftist-heap/
// Parse Array-style Heap into Tree-style Heap https://www.youtube.com/watch?v=t0Cq6tVNRBA
// Merge Algorithm https://en.wikipedia.org/wiki/Leftist_tree

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class LeftistNode {
public:
    int element; // priority
    int dist; // s-value, shortest path from the root to an external node
    LeftistNode* leftChild, * rightChild; // leftchild & rightchild
    LeftistNode(int& element, LeftistNode* lt = NULL, LeftistNode* rt = NULL, int np = 0)
    {
        this->element = element;
        rightChild = rt;
        leftChild = lt,
        dist = np;
    }
};

class LeftistHeap {
private:
    LeftistNode* root;
    // Internal method to merge two roots.
    LeftistNode* Merge(LeftistNode* h1, LeftistNode* h2);
    // Internal method to swap node's two children. 
    void swapChildren(LeftistNode* t);

    /* Deal with Heap transformation between 'Array-style' & 'Tree-style'. */
    int capacity = 0;
    vector<int> items;
    int getRightChildIndex(int parentIndex) { return parentIndex * 2 + 2; }
    int getLeftChildIndex(int parentIndex) { return parentIndex * 2 + 1; }
    int getParentIndex(int childIndex) { return (childIndex - 1) / 2; } // auto flooring

    bool hasRightChild(int index) { return getRightChildIndex(index) > capacity; }
    bool hasLeftChild(int index) { return getLeftChildIndex(index) > capacity; }
    bool hasParent(int index) { return getParentIndex(index) >= 0; }

    int rightChild(int index) { return items[getRightChildIndex(index)]; }
    int leftChild(int index) { return items[getLeftChildIndex(index)]; }
    int parent(int index) { return items[getParentIndex(index)]; }

public:
    // Construct empty leftist heap 
    LeftistHeap();
    // Construct the leftist heap with input array
    LeftistHeap(vector<int> input);
    // Copy constructor. 
    LeftistHeap(LeftistHeap& rhs);
    /* Merge rhs into the priority queue. rhs becomes empty. rhs must be different from this.*/
    void Merge(LeftistHeap& rhs);
    /* Print with 'Array-style'.*/
    void printArrayStyle();
    /* Print with 'Tree-style'.*/
    void printTreeStyle();
};

// Construct empty leftist heap 
LeftistHeap::LeftistHeap()
{
    root = NULL;
}

// Construct the leftist heap with input array
LeftistHeap::LeftistHeap(vector<int> input)
{
    root = NULL;
    return;
}

// Copy constructor. 
LeftistHeap::LeftistHeap(LeftistHeap& rhs)
{
    root = NULL;
    *this = rhs;
}

/* Merge rhs into the priority queue. rhs becomes empty. rhs must be different from this.*/
void LeftistHeap::Merge(LeftistHeap& rhs)
{
    if (this == &rhs)
        return;
    root = Merge(root, rhs.root); // merge itself with rhs
    rhs.root = NULL;
}

// Internal method to merge two roots.
LeftistNode* LeftistHeap::Merge(LeftistNode* h1, LeftistNode* h2)
{
    return NULL;
}

// Internal method to swap node's two children. 
void LeftistHeap::swapChildren(LeftistNode* t)
{
    LeftistNode* temp = t->leftChild;
    t->leftChild = t->rightChild;
    t->rightChild = temp;
}

int main()
{
    int size1, size2;
    cin >> size1 >> size2;

    int priority;
    vector<int> input1, input2;
    for (int i = 1; i <= size1; ++i) {
        cin >> priority;
        input1.push_back(priority);
    }
    for (int i = 1; i <= size2; ++i) {
        cin >> priority;
        input2.push_back(priority);
    }

    cout << input1.size() << endl;
    cout << input2.size() << endl;

    // LeftistHeap heap1;
    // LeftistHeap heap2;

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
