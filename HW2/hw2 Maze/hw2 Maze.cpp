﻿// hw2 Maze.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
#include <iostream>
#include <list>
#include <vector> 
using namespace std;

/* Adjacency List C++ */
class Graph
{
    int numVertices;
    list<int>* adjLists;

    public:
        Graph(int vertices);
        void addEdge(int src, int dest);
        void BFS(int startVertex);
        void printGraph();
};

/* Convert the maze(string) into Adjacency List */
Graph parseString(int width, int height);

int main()
{
    int width, height;
    cin >> width >> height;

    Graph g = parseString(width, height);
    g.printGraph();

    /*Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.printGraph();*/
    system("pause");
}

// Create a graph with given vertices,
// and maintain an adjacency list
Graph::Graph(int vertices) {
    numVertices = vertices;
    adjLists = new list<int>[vertices];
}

// Add edges to the graph, if edge exists do nothing.
void Graph::addEdge(int src, int dest) {
    std::list<int>::iterator findIter = find(adjLists[src].begin(), adjLists[src].end(), dest);
    if (findIter == adjLists[src].end()) {
        adjLists[src].push_back(dest);
        adjLists[dest].push_back(src);
    }
}

// Print the graph
void Graph::printGraph() {
    for (int d = 0; d < numVertices; ++d) {
        cout << "\n Vertex "
            << d << ":";
        for (auto x : adjLists[d])
            cout << "-> " << x;
        printf("\n");
    }
}

// 位移量 to reach neighbor
struct Offsets {
    int vert;
    int horiz;
};
Graph parseString(int width, int height) {
    // Read the input maze string, store with an extra large maze. (m+2) * (n+2) size.
    vector<bool> maze;
    for (int j = 0; j < width+2; j++) // wall at first row
        maze.push_back(1);
    for (int i = 0; i < height; i++) {
        maze.push_back(1);
        for (int j = 0; j < width; j++) {
            int node; cin >> node;
            maze.push_back(node);
        }
        maze.push_back(1);
    }
    for (int j = 0; j < width+2; j++) // wall at last row
        maze.push_back(1);

    //print
    cout << "\nprint maze:";
    for (int i = 0; i < (height+2) * (width+2); i++) {
        if (i % (width+2) == 0)
            cout << endl;
        cout << maze[i] << " ";
    }
    cout << "\n";

    //Create a graph stores adjList
    Graph g(height*width);
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
    //for (int i = width + 2; i <= (height + 1) * (width + 2); i++) { //skip some walls
    int index, next_index;
    int next_row, next_col;
    int src, dest;
    for (int row = 1; row < height + 1; row++) {
        for (int col = 1; col < width + 1; col++) {
            index = row * (width + 2) + col;
            //cout << index;
            if ( !maze[index] ) {
                //Check the 8 neighbors is connected or not
                for (auto move : moves) {
                    next_row = row + move.vert;
                    next_col = col + move.horiz;
                    next_index = next_row * (width + 2) + next_col;
                    if ( !maze[next_index] ) {
                        src = (row-1) * (width) + (col-1);
                        dest = (next_row-1) * (width) + (next_col-1);
                        g.addEdge(src, dest);
                        //cout << src << "->" << dest << endl;
                    }
                }
            }
        }
    }
    return g;
}
/* test1
3 3
0 1 1
0 1 1
1 0 0

test2
5 5
0 1 1 0 1
1 0 1 0 0
0 1 1 1 1
1 0 0 1 1
1 1 1 0 0
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
