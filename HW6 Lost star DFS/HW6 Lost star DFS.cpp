﻿// HW6 Lost star DFS.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
// Debug dynamic array https://docs.microsoft.com/en-us/troubleshoot/cpp/expand-pointer-%20debugger-watch-window
// Range-based for loop on a dynamic array https://stackoverflow.com/questions/15904896/range-based-for-loop-on-a-dynamic-array/15919834#15919834

#include <iostream>
#include <vector>
using namespace std;
/* wrap range of dynamic array in a std::pair and overload begin() and end() */
namespace std {
    template <typename T> T* begin(std::pair<T*, T*> const& p)
    {
        return p.first;
    }
    template <typename T> T* end(std::pair<T*, T*> const& p)
    {
        return p.second;
    }
}

class Graph {
private:
    bool** adjMatrix; // Adjacency Matrix representation in C++, which size is numVertices*numVertices 
    bool* visited; // An array marks visited vertex as 'true'
    int numVertices, width, height;

public:
    // Initialize the matrix to zero
    Graph(int width, int height);

    // Add edges
    void addEdge(int i, int j);
    // Remove edges
    void removeEdge(int i, int j);
    // Print the martix
    void toString();
    // DFS algorithm
    void DFS(int vertex); // still has buggggggggggggggg
    // De-Constructor
    //~Graph();
};

/* Convert the maze(input string) into Adjacency Matrix */
Graph parseString(int width, int height);

int main()
{
    int width, height;
    cin >> height >> width;
    //Graph g(width, height);
    Graph g = parseString(width, height);
    //g.addEdge(1, 2);
    g.toString();

    g.DFS(18);
}

Graph::Graph(int width, int height) {
    this->width = width;
    this->height = height;
    numVertices = width*height;

    // init visited array
    visited = new bool[numVertices]; 
    for (int i = 0; i < numVertices; i++)
        visited[i] = false;

    // init to zero edges (use for loop, shoundn't memset)
    adjMatrix = new bool* [numVertices];
    for (int i = 0; i < numVertices; i++) {
        adjMatrix[i] = new bool[numVertices];
        for (int j = 0; j < numVertices; j++)
            adjMatrix[i][j] = false;
    }
}

void Graph::addEdge(int i, int j) {
    adjMatrix[i][j] = true;
    adjMatrix[j][i] = true;
}

void Graph::removeEdge(int i, int j) {
    adjMatrix[i][j] = false;
    adjMatrix[j][i] = false;
}

void Graph::toString() {
    for (int i = 0; i < numVertices; i++) {
        cout << i << " : ";
        for (int j = 0; j < numVertices; j++)
            cout << adjMatrix[i][j] << " ";
        cout << "\n";
    }
}

void Graph::DFS(int vertex) {
    visited[vertex] = true;
    bool* adjArray = adjMatrix[vertex];

    cout << vertex << " ";

    for (auto&& i : std::make_pair(adjArray, adjArray + numVertices))
        if (!visited[i])
            DFS(i);
}

/*
Graph::~Graph() {
    for (int i = 0; i < numVertices; i++)
        delete[] adjMatrix[i];
    delete[] adjMatrix;
}*/

// 位移量 to reach neighbor
struct Offsets {
    int vert;
    int horiz;
};

Graph parseString(int width, int height) {
    // 1. Read the input maze string, store with an extra large maze. (m+2) * (n+2) size.
    vector<bool> maze; // true -> vertex
    for (int j = 0; j < width + 2; j++) // wall at first row
        maze.push_back(false);
    for (int i = 0; i < height; i++) {
        maze.push_back(false);
        for (int j = 0; j < width; j++) {
            char node; 
            cin >> node;
            (node == '*') ? maze.push_back(true) : maze.push_back(false); // if '*' -> add true
        }
        maze.push_back(false);
    }
    for (int j = 0; j < width + 2; j++) // wall at last row
        maze.push_back(false);

    // 2. Create a graph and init adjMatrix
    Graph g(width, height);
    int index, next_index;
    int next_row, next_col;
    int src, dest;
    Offsets moves[8] = {
        {-1, -1}, //NW
        {0, -1}, //W
        {1, -1}, //SW
        {1, 0}, //S
        {1, 1}, //SE
        {0, 1}, //E
        {-1, 1}, //NE
        {-1, 0}  //N
    };
    for (int row = 1; row < height + 1; row++) {
        for (int col = 1; col < width + 1; col++) {
            index = row * (width + 2) + col;
            //cout << index;
            if (maze[index]) {
                //If vertix, Check the 8 neighbors is connected or not, then create its edges
                for (auto move : moves) {
                    next_row = row + move.vert;
                    next_col = col + move.horiz;
                    next_index = next_row * (width + 2) + next_col;
                    if (maze[next_index]) {
                        src = (row - 1) * (width)+(col - 1);
                        dest = (next_row - 1) * (width)+(next_col - 1);
                        g.addEdge(src, dest);
                        cout << src << "->" << dest << endl;
                    }
                }
            }
        }
    }

    return g;
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
