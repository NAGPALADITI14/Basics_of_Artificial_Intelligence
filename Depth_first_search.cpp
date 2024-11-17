#include<iostream>
#include<vector>
using namespace std;

void DFS(int node, vector<vector<int>> adj, vector<bool>& visited, vector<int>& ans)
{
    visited[node] = 1;
    ans.push_back(node);
    for (int j = 0; j < adj[node].size(); j++)
    {
        if (!visited[adj[node][j]])
        {
            DFS(adj[node][j], adj, visited, ans);
        }
    }
}

int main()
{
    int nodes, edges;
    cout << "Enter the number of nodes: ";
    cin >> nodes;
    cout << "Enter the number of edges: ";
    cin >> edges;

    vector<vector<int>> adj(nodes);
    cout << "Enter the edges (u v):" << endl;
    for (int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> visited(nodes, false);
    vector<int> dfs_result;

    DFS(0, adj, visited, dfs_result);

    cout << "DFS Traversal: ";
    for (int i = 0; i < dfs_result.size(); i++)
    {
        cout << dfs_result[i] << " ";
    }
    cout << endl;

    return 0;
}
