// HW3.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
// @Author 'Weber Lu, MIS Senior'
// Process:
// 1) Read infix string
// 2) Convert infix to postfix

#include <iostream>
#include <string>
#include <stack>
using namespace std;

// Read infix string
string ReadInput();
// Convert infix to postfix
string ToPostfix(string infix);

int main()
{
    string input = ReadInput();
    std::cout << input << endl;
    ToPostfix(input);
}

string ReadInput() {
    string input;
    cin >> input;
    return input;
}

string ToPostfix(string infix) {
    string postfix = ""; // return value
    stack <char> stack;

    for (char c : infix) {
        // If c is operand -> output. Operand = 1, 2, 3, a, b, x, y...
        if (isalnum(c)) {
            postfix += c;
        }
        // If c is right-parenthesis, rparen ) -> pop until left-parenthesis
        else if (c == ')') {
            while (stack.top() != '(') {
                postfix += stack.top();
                stack.pop();
            }
            stack.pop(); // remove ( either
        }
        // If c is other operator, ex: +, -, *, /... -> pop operators in stack whose isp is greater or equal to c -> push c in stack
        else {
            while (true) {

            }
            stack.push(c);
        }
    }

    // the input of infix is end, clear the stack
    while (!stack.empty()) {
        stack.pop();
    }
    return postfix;
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
