// HW5 Some linked list operations.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
// @Author: MIS Senior - Weber Lu

#include <iostream>
#include <string> // std::string, std::stoi
#include <regex> // std::regex, std::smatch, std::regex_match
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
    int deleteById(int index);
    // Invert the whole linklist
    void reverse();
    static void concatenate(LinkList* a, LinkList* b);
};

int main()
{
    LinkList list;
    string command; // input string

    const regex REGEX_ADD("^ADD\\s([0-9]+)$"); /* ADD 90 */
    const regex REGEX_INSERT("^INSERT\\s([0-9]+)\\sBEHIND\\s([0-9]+)$"); /* INSERT 11 BEHIND 1 */
    const regex REGEX_DELETE("^DELETE\\s([0-9]+)$"); /* DELETE 4 */
    const regex REGEX_REVERSE("^REVERSE$"); /* REVERSE */
    smatch match;

    do {
        getline(std::cin, command);
        if (regex_match(command, match, REGEX_ADD)) { 
            ssub_match sub_match = match[1]; // abstract the value to insert, match[0] is original string
            int value = stoi(sub_match.str());
            list.pushBack(value); // perform operation 'pushBack'
        }
        else if (regex_match(command, match, REGEX_INSERT)) { 
            // perform operation 'insert'
            int value = stoi(match[1].str());
            int index = stoi(match[2].str());
            list.insert(index, value);
        }
        else if (regex_match(command, match, REGEX_DELETE)) { 
            // perform operation 'deleteById'
            int index = stoi(match[1].str());
            list.deleteById(index);
        }
        else if (command.find("REVERSE") == 0) { 
            // perform operation 'reverse'
            list.reverse();
        }
        // print whole list after every command line
        if (!command.empty())
            list.print();
    } while (!command.empty());

    /*
    list.pushBack(10);
    list.print();
    list.insert(5, 6);
    list.print();
    list.insert(0, 6);
    list.print();
    
    list.reverse();
    list.print();
    list.pushBack(1);
    list.print();
    list.reverse();
    list.print();
    list.pushBack(3);
    list.print();
    list.deleteById(2);
    list.print();
    list.deleteById(5);
    list.print();

    list.insert(3, 11);
    list.print();
    list.reverse();
    list.print();*/
}

LinkList::LinkList() {
    head = NULL;
    tail = NULL;
}

void LinkList::print() { // for ( ; ptr; ptr = ptr->link) is PPT's method
    node* current = this->head;
    string result("");
    while (current) {
        result += to_string(current->data);
        result += ' ';
        current = current->next;
    }
    result.pop_back(); // remove last character ' ' with O(1) (white space)
    cout << result << endl;
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
            cout << e.what() << endl; // Problem requires: error message
            return;
        }
        // inserting a node 'newn' after node 'target'
        newn->next = target->next;
        target->next = newn;
        // if insert at last, move tail to newm
        while (tail->next)
            tail = tail->next;
    }
}

int LinkList::deleteById(int index) {
    // index = 0 or n+1 --> illegal 
    // index = 1 --> delete first node 
    // index = n --> delete last node 
    // else        --> delete middle node 
    node* target = head, *trail = head; // Point 'target' to the deleting node, 'trail' to the former node
    int data = -1;
    try {
        int length = this->size(); // O(n)
        if (index > length || index == 0)
            throw std::out_of_range("Index is out of range!!");
        else {
            for (int count = 2; count <= index; count++) {
                trail = target;
                target = target->next;
            }
            data = target->data;
            // cout << "Item to delete " << target->data << endl;
        }
    }
    catch (std::exception& e) {
        cout << e.what() << endl; // Problem requires: error message
        return -1;
    }

    // Perform deletion, if only 1 elem then goes in 1st & 2nd if()
    if (target == head) {
        head = head->next;
    }
    if (target == tail) {
        tail = trail; // trail is the last element
    }
    if (target != head && target != tail) {
        trail->next = target->next;
    }
    delete target; //freed memory
    target = NULL; //pointed dangling ptr to NULL
    return data;
}

void LinkList::reverse() {
    // https://www.geeksforgeeks.org/reverse-a-linked-list/
    node* newhead = this->tail, *newtail = this->head; // Stores original head & tail
    node* lead = head, *middle, *trail = head; // Needs 3 pointers
    middle = NULL;
    while (lead) {
        trail = middle;
        middle = lead;
        lead = lead->next;
        middle->next = trail;
    }
    this->head = newhead;
    this->tail = newtail;
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

/* Test Set 02
ADD 10
INSERT 6 BEHIND 5
INSERT 6 BEHIND 0
REVERSE
ADD 1
REVERSE
ADD 3
DELETE 2
DELETE 5
INSERT 11 BEHIND 3
REVERSE
*/

/* Ans 02
10
Index is out of range!!
10
6 10
10 6
10 6 1
1 6 10
1 6 10 3
1 10 3
Index is out of range!!
1 10 3
1 10 3 11
11 3 10 1*/

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
