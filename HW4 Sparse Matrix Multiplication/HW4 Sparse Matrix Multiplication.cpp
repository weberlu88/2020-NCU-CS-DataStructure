﻿// HW4 Sparse Matrix Multiplication.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
// @Author: NCU MIS Senior - Weber Lu
// 1) Read two input matrices, and pasre into vector<Vertex> seperately.
// 2) Do matrix multiplication algorithm, get the result.
// 3) Print the result in format.
// Notes:
// a) Each matrix stores its 'Non-zero' elements in a vector<Vertex>.
// b) Do not use normal matrix multiplication algorithm with O(n^3)
// c) Eligible algorithm: ...

#include <iostream>
#include <stdlib.h>     /* atoi */
#include <vector>
#include <algorithm>
using namespace std;

// Stores a Non-zero element.
class Vertex {
public:
    int row = 0, col = 0, value = 0;
    Vertex() {}
    Vertex(int row, int col, int value) { this->row = row; this->col = col; this->value = value; }
    bool operator<(const Vertex &r) const;
};

// Stores a complete matrix, contains info and list of elems.
class Matrix {
public:
    int row_count, col_count, val_count = 0;
    vector<Vertex> list;
    
    Matrix(int row, int col) {
        row_count = row;
        col_count = col;
    }
    // T-transform, as row major order. Return result.
    Matrix lazyTranspose();
    Matrix fastTranspose(); 
    // Perform matrix multiplication algorithm. Return result. (this = A, another = B)
    Matrix multiplication(Matrix another);
    // Pushback a vertex to list, valcount++ either.
    void storeSum(Vertex v);
    // Print matrix's non-zero elements only.
    void print(); 
    // Print in n*m matrix format.
    void prettyPrint();
};

// Abstract the matrix's non-zero elements. Row major.
Matrix ParseInputMatrix(int row, int col); 

//Compare two int value, if former is smaller then return -1.
int compare(int a, int b) {
    if (a < b)
        return -1;
    else if (a == b)
        return 0;
    return 1;
}

int main()
{
    int row = 0, col = 0;
    cin >> row >> col;
    Matrix m1 = ParseInputMatrix(row, col);

   // cin >> row >> col;
   // Matrix m2 = ParseInputMatrix(row, col);

    // testing T-transpose
    Matrix trans = m1.lazyTranspose();
    cout << "\n";
    trans.prettyPrint();

    // Matrix result = m1.multiplication(m2);
    // result.print();
}

Matrix ParseInputMatrix(int row, int col) {
    Matrix m(row, col); // declare and init
    char * input = new char[10];
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            // if non-zero element, pushback & valcount++
            cin >> input;
            int value = atoi(input); // convert string to int. Code review on var 'input' type: char(x), int(o) will be easier.
            if (value != 0) 
                m.list.push_back(Vertex(r, c, value));
        }
    }
    m.val_count = m.list.size();
    return m;
}

// over load the operator<, compare 'row' , if equal then compare 'col'
bool Vertex::operator<(const Vertex& r) const {
    if (row != r.row)
        return row < r.row;
    return col < r.col;
}

void Matrix::print() {
    for (auto v : this->list)
        cout << v.row << " " << v.col << " " << v.value << endl;
}

void Matrix::prettyPrint() {
    int current_pointer = 0;
    for (int r = 0; r < this->row_count; r++) {
        for (int c = 0; c < this->col_count; c++) {
            // if elem exists in 'list' means non-zero value
            if (this->list[current_pointer].row == r && this->list[current_pointer].col == c)
                cout << this->list[current_pointer++].value << " "; // print vertex's value, and ++ pointer
            else
                cout << "0 "; // vertex's value is 0
        }
        cout << endl;
    }
}

void Matrix::storeSum(Vertex v) {
    if (v.value == 0) 
        return;
    this->list.push_back(v);
    this->val_count = this->list.size();
}

Matrix Matrix::lazyTranspose() {
    // init transpose matrix's header
    Matrix trans(this->col_count, this->row_count);
    trans.val_count = this->val_count;

    // Exchange every row & col 
    for (auto v : this->list) {
        Vertex newv(v.col, v.row, v.value); // swap
        trans.list.push_back(newv);
    }

    // sort by row then col, make sure it's row major order. O(nlogn)
    std::sort(trans.list.begin(), trans.list.end());
    return trans;
}

Matrix Matrix::multiplication(Matrix another) {
    Matrix* result = new Matrix(this->row_count, another.col_count);
    // Check can mutiply ?
    if (this->col_count != another.row_count) {
        cout << "Incompatible matrices" << endl;
        return *result;
    }
    // repalce another one with its transpose
    another = another.lazyTranspose();
    // need to pushback a dummy vertex? Yes!
    // ...

    int sum = 0, rowBegin = 0;
    int currentRow = this->list[0].row; // Current calculating row number of result matrix
    int currentCol = another.list[0].row; // Current calculating col number of result matrix
    for (int i = 0; i < this->val_count; ) { // "i" is index of vector in "this", increase manually
        for (int j = 0; j < another.val_count; ) { // "j" is index of vector in "another", increase manually
            if (this->list[i].row != currentRow) { 
                // Row number == currentRow in matrix "this" ends, go on next row. WTF is this comment ?!
                storeSum(Vertex(currentRow, currentCol, sum));
                i = rowBegin;
                for (; another.list[j].row == currentCol; j++)
                    ;
                currentCol = another.list[j].row;
            }
            else if (another.list[j].row != currentCol) {
                storeSum(Vertex(currentRow, currentCol, sum));
                i = rowBegin;
                currentCol = another.list[j].row;
            }
            else switch (compare(this->list[i].col, another.list[j].col)) {
            case -1: // A doen't has corresponding column, advance next term on A
                i++; break;
            case 0: // Has corresponding vertex, mutiply them
                sum += (this->list[i++].value * another.list[j++].value); break;
            case 1: // A doen't has corresponding column, advance next term on A
                j++; break;
            }
        } // end of for loop(B)
        // Find next row of A/this
        for (; this->list[i].row == currentRow; )
            ;
        rowBegin = i;
        currentRow = this->list[i].row;
    } // end of for loop(A)
    return *result;
}

/*Test Set 1
3 3
3 4 0
0 3 2
2 0 4
3 3
0 0 0
0 1 0
0 0 0

ANS 1
0 1 4  <-- 0列1行，值為4
1 1 3  <-- 1列1行，值為3
---
0	4	0
0	3	0
0	0	0
*/

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
