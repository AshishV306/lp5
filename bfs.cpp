#include <iostream>
#include <queue>
#include <omp.h>
#include <vector>
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
    void parallelBFS(int start)
    {
        vector<int> visited(V, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            cout << v << " ";
#pragma omp parallel for
            for (int i = 0; i < adj[v].size(); i++)
            {
                int n = adj[v][i];
                if (!visited[n])
                {
                    #pragma omp critical
                    visited[n] = true;
                    q.push(n);
                }
            }
        }
    }
    void serialBFS(int start)
    {
        vector<int> visited(V, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            cout << v << " ";
//#pragma omp parallel for
            for (int i = 0; i < adj[v].size(); i++)
            {
                int n = adj[v][i];
                if (!visited[n])
                {
                    visited[n] = true;
                    q.push(n);
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

    // cout << "Breadth-First Search (BFS): ";
    // g.parallelBFS(0);
    // cout << endl;

    auto start_s = chrono::high_resolution_clock::now();
    cout<<"Serial BFS: ";
    g.serialBFS(0);
    auto end_s = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> time_s = end_s - start_s;
    cout<<"\nTime: "<<time_s.count()<<"ms"<<endl;

    auto start_p = chrono::high_resolution_clock::now();
    cout<<"Paralel BFS: ";
    g.parallelBFS(0);
    auto end_p = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> time_p = end_p - start_p;
    cout<<"\nTime: "<<time_p.count()<<"ms"<<endl;

    return 0;
}
