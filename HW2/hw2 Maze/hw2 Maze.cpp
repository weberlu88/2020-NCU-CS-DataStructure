// hw2 Maze.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
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

// Create a graph with given vertices,
// and maintain an adjacency list
Graph::Graph(int vertices) {
    numVertices = vertices;
    adjLists = new list<int>[vertices];
}

// Add edges to the graph
void Graph::addEdge(int src, int dest) {
    adjLists[src].push_back(dest);
    adjLists[dest].push_back(src);
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

int main()
{
    //std::cout << "Hello World!\n";
    int width, height;
    cin >> width;
    cin >> height;
    cout << height << " " << width << endl;

    Graph g = parseString(width, height);

    //Graph g(4);
    //g.addEdge(0, 1);
    //g.addEdge(0, 2);
    //g.addEdge(1, 2);
    ////g.addEdge(2, 0);
    //g.addEdge(2, 3);
    //g.printGraph();
    system("pause");
}

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

    return Graph(width*height);
}
/* test1
3 3
0 1 1
0 1 1
1 0 0
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
