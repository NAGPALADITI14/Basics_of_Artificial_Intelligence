#include<iostream>
#include<queue>
#include<vector>

using namespace std;
vector<int> BFS(int nodes, vector<vector<int>> adj)
{
    queue<int> q;
    vector<bool> visited(nodes);
    fill(visited.begin(), visited.end(), 0);
    int val;
    q.push(0);
    visited[0] = 1;
    vector<int> ans;
    while (!q.empty())
    {
        val = q.front();
        q.pop();
        ans.push_back(val);
        for (int j = 0; j < adj[val].size(); j++)
        {
            if (!visited[adj[val][j]])
            {
                visited[adj[val][j]] = 1;
                q.push(adj[val][j]);
            }
        }
    }
    return ans;
}

int main()
{
    int vertices, edges;
    cout << "Enter the number of nodes: ";
    cin >> vertices;
    cout << "Enter the number of edges: ";
    cin >> edges;

    vector<vector<int>> adj(vertices);
    cout << "Enter the edges (u v):" << endl;
    for (int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); 
    }

    vector<int> bfs_result = BFS(vertices, adj);
    cout << "BFS Traversal: ";
    for (int i = 0; i < bfs_result.size(); i++)
    {
        cout << bfs_result[i] << " ";
    }
    cout << endl;

    return 0;
}
