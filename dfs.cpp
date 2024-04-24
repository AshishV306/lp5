#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>
#include<chrono>

using namespace std;

class Graph
{
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V)
    {
        this->adj = vector<vector<int>>(V);
        this->V = V;
    }
    void addEdge(int v, int w)
    {
        adj[v].push_back(w);
        adj[w].push_back(v);
    }
    void parallelDFS(int start)
    {
        vector<bool> visited(V, false);
        stack<int> stk;
        stk.push(start);
        while (!stk.empty())
        {
            int v = stk.top();
            stk.pop();
            if (!visited[v])
            {
                cout << v << " ";
                visited[v] = true;
#pragma omp parallel for
                for (int i = 0; i < adj[v].size(); i++)
                {
                    int n = adj[v][i];
                    if (!visited[n])
                    {
                        stk.push(n);
                    }
                }
            }
        }
    }
    void serialDFS(int start)
    {
        vector<bool> visited(V, false);
        stack<int> stk;
        stk.push(start);
        while (!stk.empty())
        {
            int v = stk.top();
            stk.pop();
            if (!visited[v])
            {
                cout << v << " ";
                visited[v] = true;
//#pragma omp parallel for
                for (int i = 0; i < adj[v].size(); i++)
                {
                    int n = adj[v][i];
                    if (!visited[n])
                    {
                        stk.push(n);
                    }
                }
            }
        }
    }
};

int main()
{
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    // cout << "Depth-first search (DFS): ";
    // g.parallelDFS(0);
    // cout << endl;

    auto start_s = chrono::high_resolution_clock::now();
    cout<<"Serial DFS: ";
    g.serialDFS(0);
    auto end_s = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> time_s = end_s - start_s;
    cout<<"\nTime: "<<time_s.count()<<"ms"<<endl;

    auto start_p = chrono::high_resolution_clock::now();
    cout<<"Paralel DFS: ";
    g.parallelDFS(0);
    auto end_p = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> time_p = end_p - start_p;
    cout<<"\nTime: "<<time_p.count()<<"ms"<<endl;

    return 0;
}