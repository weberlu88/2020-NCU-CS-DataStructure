// HW8 Minimum Spanning Tree.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
// @author MIS Senior Weber Lu
// https://www.hackerearth.com/practice/algorithms/graphs/minimum-spanning-tree/tutorial/ Main Code
// https://en.wikipedia.org/wiki/Disjoint-set_data_structure
// https://www2.cs.duke.edu/courses/cps100e/fall09/notes/UnionFind.pdf

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

const int MAX = 50; 
int id[MAX], nodes, edges; // Integer array id[] of size N = nodes
pair <long long, pair<int, int> > p[MAX]; // p is the graph, with 'egdes' elements. Data structure: <weight, <x,y>>

// init the UnionFind graph p[], creates MAX singletons.
void initialize()
{
    for (int i = 0; i < MAX; ++i)
        id[i] = i;
}

// Quick-union's Find() operation: Root of i is id[id[id[...id[i]...]]]. 
int root(int x)
{
    // keep finding parent until it doesn’t change
    while (id[x] != x) {
        id[x] = id[id[x]]; // flatten the tree
        x = id[x]; // up finding
    }
    return x; // return x's root
}

// Merge union {x, ...} into union {y, ...}, both are under root(y)
void unite(int x, int y)
{
    int p = root(x);
    int q = root(y);
    id[p] = id[q]; // point id[p] to id[q]
}

long long kruskal(pair<long long, pair<int, int> > p[]) {
    int x, y; // source & destination vertix
    long long cost, minimumCost = 0;
    for (int i = 0; i < edges; ++i) {
        // Selecting edges one by one (p[i].second) in increasing order from the beginning.
        x = p[i].second.first;
        y = p[i].second.second;
        cost = p[i].first;
        
        // Check if the selected edge is creating a cycle or not
        if (root(x) != root(y)) {
            // different root -> belongs to different connected component -> adding this edge won't cause cycle
            minimumCost += cost;
            unite(x, y); // merge {x, ...} and {y, ...} in same union {x, y, ...}
        }
    }
    return minimumCost;
}

int main()
{
    // There's numOfSamples times of test data
    int numOfSamples;
    cin >> numOfSamples;
    for (int n = 1; n <= numOfSamples; ++n) {

        // Resad input and init the graph
        int x, y;
        long long weight, minimumCost;
        initialize();
        cin >> nodes >> edges;
        for (int i = 0; i < edges; ++i)
        {
            cin >> x >> y >> weight;
            p[i] = make_pair(weight, make_pair(x, y)); // push edges into the graph
        }
        // Sort the edges in the ascending order
        sort(p, p + edges);
        minimumCost = kruskal(p);
        cout << minimumCost << endl;

    }

    return 0;
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
