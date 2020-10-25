// HW3.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
// @Author 'Weber Lu, MIS Senior'
// Process:
// 1) Read infix string
// 2) Convert infix to postfix

#include <iostream>
#include <string>
#include <stack>
#include <map>
using namespace std;

// Read infix string
string ReadInput();
// Convert infix to postfix
string ToPostfix(string infix);

int main()
{
    std::string input = ReadInput();
    std::cout << ToPostfix(input) << endl;
}

string ReadInput() {
    string input;
    cin >> input;
    return input;
}

string ToPostfix(string infix) {
    string postfix = ""; // return value
    stack <char> stack;
    map<char, int> isp; // operator's in stack precedence, 在stack中的優先度
    isp.insert(pair<char, int>('+', 12));
    isp.insert(pair<char, int>('-', 12));
    isp.insert(pair<char, int>('*', 13));
    isp.insert(pair<char, int>('/', 13));
    isp.insert(pair<char, int>('%', 13));
    isp[')'] = 19;
    isp['('] = 0; // 左括弧在stack中等待又括弧才被pop, 優先度0
    map<char, int> icp(isp); // incoming precedence, 進入stack的優先度
    icp['('] = 20; // 左括弧必定進stack, 優先度最大

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
        // If c is other operator, ex: +, -, *, /... 
        // -> pop operators in stack whose isp is greater or equal to c's icp -> push c in stack
        else {
            // 想像stack的優先度必由小至大，要pop掉大於等於自己的，才能push進去
            while (!stack.empty() && isp[stack.top()] >= icp[c]) { 
                postfix += stack.top();
                stack.pop();
            }
            stack.push(c);
        }
    }

    // the input of infix is end, clear the stack
    while (!stack.empty()) {
        postfix += stack.top();
        stack.pop();
    }
    return postfix;
}

/*
* test case 1:
1+3*5/4
135*4/+
* test case 2:
a+(b*c-(1/2-3)*d)*e
abc*12/3-d*-e*+
*/
