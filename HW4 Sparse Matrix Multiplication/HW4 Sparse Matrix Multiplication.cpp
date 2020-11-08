// HW4 Sparse Matrix Multiplication.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
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
using namespace std;

// Stores a Non-zero element.
class Vertex {
public:
    int row = 0, col = 0, value = 0;
    Vertex() {}
    Vertex(int row, int col, int value) { this->row = row; this->col = col; this->value = value; }
};

// Stores a complete matrix, contains info and list of elems.
class Matrix {
public:
    int row_count, col_count, val_count = 0;
    vector<Vertex> list;
    
    Matrix(int row, int col) {
        row_count = row;
        col_count = row;
    }
    Matrix fast_transpose();
};

Matrix ParseInputMatrix(int row, int col); // Abstract the matrix's non-zero elements. Row major.
Matrix MatrixMultiplication(Matrix *a, Matrix *b); // Perform multiplication algorithm.
void PrintMatrix(Matrix); // Print matrix's non-zero elements.

int main()
{
    int row = 0, col = 0;
    cin >> row >> col;
    Matrix m1 = ParseInputMatrix(row, col);

    cin >> row >> col;
    Matrix m2 = ParseInputMatrix(row, col);
}

Matrix ParseInputMatrix(int row, int col) {
    Matrix m(row, col); // declare and init
    char * input = new char[5];
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            // if non-zero element, pushback & valcount++
            cin >> input;
            int value = atoi(input);
            if (value != 0) {
                m.list.push_back(Vertex(r, c, value));
                m.val_count++;
            }
        }
    }
    return m;
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
