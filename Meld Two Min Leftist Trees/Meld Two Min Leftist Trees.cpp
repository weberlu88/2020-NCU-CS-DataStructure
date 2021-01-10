// Meld Two Min Leftist Trees.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
// @author: MIS Senior Weber Lu
// Data Structure https://www.geeksforgeeks.org/leftist-tree-leftist-heap/
// Parse Array-style Heap into Tree-style Heap https://www.youtube.com/watch?v=t0Cq6tVNRBA
// Merge Algorithm https://en.wikipedia.org/wiki/Leftist_tree

#include <iostream>
#include <algorithm>    // std::min max
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <utility>

using namespace std;

class LeftistNode {
public:
    int element; // priority
    int dist; // s-value, shortest path from the root to an external node
    LeftistNode* leftChild, * rightChild; // leftchild & rightchild
    LeftistNode(int element, LeftistNode* lt = NULL, LeftistNode* rt = NULL, int np = 1)
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
    LeftistNode* Merge(LeftistNode* x, LeftistNode* y);
    // Internal method to swap node's two children. 
    void swapChildren(LeftistNode* t);
    // Internal method to insert nodes in level order recursively
    LeftistNode* insertLevelOrder(LeftistNode* root, int index, int value);
    /* Internal method to compute the "height" of a tree.  Farthest leaf node's height = 1. External node's height = 0. */
    int height(LeftistNode* node);

    /* Deal with Heap transformation between 'Array-style' & 'Tree-style'. */
    int size = 0; // non zero elements
    int capacity = 0; // length of array in array representation. len =  2 ^ (tree height)  - 1
    vector<int> items;

    void setItems();

    int getRightChildIndex(int parentIndex) { return parentIndex * 2 + 2; }
    int getLeftChildIndex(int parentIndex) { return parentIndex * 2 + 1; }
    int getParentIndex(int childIndex) { return (childIndex - 1) / 2; } // auto flooring

    bool hasRightChild(int index) { return getRightChildIndex(index) < size; }
    bool hasLeftChild(int index) { return getLeftChildIndex(index) < size; }
    bool hasParent(int index) { return getParentIndex(index) >= 0; }

    int rightChild(int index) { return items[getRightChildIndex(index)]; }
    int leftChild(int index) { return items[getLeftChildIndex(index)]; }
    int parent(int index) { return items[getParentIndex(index)]; }

public:
    // Construct empty leftist heap 
    LeftistHeap();
    // Construct the leftist heap with input array
    LeftistHeap(vector<int> inputArr);
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
LeftistHeap::LeftistHeap(vector<int> inputArr)
{
    items = inputArr;
    size = items.size();

    // Init the Heap structure
    if (size)
    {
        // Create the root node, call insertLevelOrder() to complete the heap, calculate s-value as well
        int index = 0, value = items[0];
        root = insertLevelOrder(root, index, value);
    }
}

// Internal method to insert nodes in level order recursively
LeftistNode* LeftistHeap::insertLevelOrder(LeftistNode* root, int index, int value)
{
    // Recursively case for recursion
    if (index < size) {

        // create the node with NULL childs
        LeftistNode* temp = new LeftistNode(value);
        root = temp;

        // insert left child, if the node has
        if (hasLeftChild(index) && leftChild(index))
            root->leftChild = insertLevelOrder(root->leftChild, getLeftChildIndex(index), leftChild(index));

        // insert right child, if the node has
        if (hasRightChild(index) && rightChild(index))
            root->rightChild = insertLevelOrder(root->rightChild, getRightChildIndex(index), rightChild(index));

        // calculate its s-value (Lheap's s-val right <= left)
        if (hasRightChild(index) && rightChild(index))
            root->dist = root->rightChild->dist + 1;
    }
    // Base case for recursion
    return root;
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
    size += rhs.size;
    rhs.size = 0;
    rhs.capacity = 0;
    // reset items[] by converting tree to array ################ @@@@@
    rhs.items.clear();
}

// Internal method to merge two roots. (MinHeap)
LeftistNode* LeftistHeap::Merge(LeftistNode* x, LeftistNode* y)
{
    if (x == NULL) { return y; }
    if (y == NULL) { return x; }
    
    // make sure A.key is smaller, if A.key > B.key then SWAP(A, B)
    if (x->element > y->element) {
        LeftistNode* temp = x;
        x = y;
        y = temp;
    }

    // recursive call merging 'r-child' with another one heap
    x->rightChild = Merge(x->rightChild, y);

    // after merged, left child doesn't exist, so swing right child to the left side
    // x.s was, and remains, 1
    if (x->leftChild == NULL) 
        swapChildren(x); 
    // left child does exist, so compare s-values
    // since we know the right child has the lower s-value, we can just add one to its s-value
    else {
        if (x->leftChild->dist < x->rightChild->dist) 
            swapChildren(x);
        x->dist = x->rightChild->dist + 1;
    }
    return x;
}

// Internal method to swap node's two children. 
void LeftistHeap::swapChildren(LeftistNode* t)
{
    LeftistNode* temp = t->leftChild;
    t->leftChild = t->rightChild;
    t->rightChild = temp;
}

/* Compute the "height" of a tree.  Farthest leaf node's height = 1. External node's height = 0. */
int LeftistHeap::height(LeftistNode* node)
{
    if (node == NULL)
        return 0;
    else
        /* compute the height of each subtree, use the larger one */
        return max(height(node->leftChild), height(node->rightChild)) + 1;
}

int main()
{
    int size1, size2;
    cin >> size1 >> size2;
    cin.ignore(); // Ignore NEWLINE

    int priority;
    //vector<int> element1, element2;
    string line;

    getline(cin, line);
    std::istringstream this_line(line);
    std::istream_iterator<int> begin(this_line), end;
    std::vector<int> element1(begin, end);

    getline(cin, line);
    std::istringstream this_line2(line);
    std::istream_iterator<int> begin2(this_line2), end2;
    std::vector<int> element2(begin2, end2);

    cout << endl << element1.size() << endl;
    cout << element2.size() << endl;

    LeftistHeap heap1(element1);
    LeftistHeap heap2(element2);

    heap1.Merge(heap2);

}

/*
// Test Case 00
9 3
1 3 7 11 15 19 0 23 21 0 0 27
6 8 0 25
>> 3
>> 1 3 6 11 15 8 7 23 21 0 0 25 0 19 0 0 0 0 0 0 0 0 0 0 0 0 0 27

// Test Case 01
5 4
4 6 8 8 6
3 5 6 9
>> 2
>> 3 4 5 6 6 9 0 8 6 8
*/