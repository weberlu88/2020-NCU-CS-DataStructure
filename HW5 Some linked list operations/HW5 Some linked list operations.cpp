// HW5 Some linked list operations.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
using namespace std;

struct node{
    int data;
    struct node* next;
};

class LinkList {
private:
    node *head, *tail;
public:
    // Constructor, init *head *tail to null
    LinkList();
    int size();
    int find(int value);
    // Traverse and print all elements by space
    void print();
    // Add element at the end of linklist
    void pushBack(int value);
    // Insert element at given position, throw error messege while index out of bound (first elem's index is 1)
    void insert(int index, int value);
    // Delete element at given position, throw error messege while index out of bound (first elem's index is 1)
    void deleteById(int index);
    // Invert the whole linklist
    void reverse();
    static void concatenate(LinkList* a, LinkList* b);
};

int main()
{
    LinkList list;
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    list.insert(3, 999);
    list.print();
}

LinkList::LinkList() {
    head = NULL;
    tail = NULL;
}

void LinkList::print() {
    node* current = this->head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
}

int LinkList::size() {
    int size = 0;
    node* current = this->head;
    while (current) {
        size++;
        current = current->next;
    }
    return size;
}

void LinkList::pushBack(int value) {
    // init new node
    node *tmp = new node;
    tmp->data = value;
    tmp->next = NULL;

    if (head == NULL) 
        // First node, head & tail both point to first node
        tail = head = tmp;
    else {
        // Not empty, tmp is the last node; 
        tail->next = tmp; // (n-1) -> n
        tail = tail->next;
    }
}

void LinkList::insert(int index, int value) {
    if (!index) {
        // if index is 0, then insert as first node 
        node* newn = new node;
        newn->data = value;
        newn->next = head; // new node point to the origin head node
        head = newn;
        if (tail == NULL)
            tail = newn; // if list is empty before insert, new node is first & last node
    }
    else {
        // newn is the new node, insert after target node
        node* newn = new node;
        newn->data = value;
        node* target = new node;
        target = head; // target point to first elem
        // find the target node with value, throw index out of bound error
        try {
            int length = this->size(); // O(n)
            if (index > length)
                throw std::out_of_range("Index is out of range!!");
            for (int i = 1; i < index; i++)
                    target = target->next;
        }
        catch (std::exception& e) {
            cout << e.what() << endl; // Problem requires: error message + original list
            this->print();
        }
        // inserting a node 'newn' after node 'target'
        newn->next = target->next;
        target->next = newn;
        // if insert at last, move tail to newm
        while (tail->next)
            tail = tail->next;
    }
}

/* Test Set 01
ADD 5
ADD 10
ADD 90
INSERT 11 BEHIND 1
DELETE 4
INSERT 9 BEHIND 5
REVERSE
*/

/* Ans 01
5
5 10
5 10 90
5 11 10 90
5 11 10
Index is out of range!!
5 11 10
10 11 5*/

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
