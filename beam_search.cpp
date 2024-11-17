#include<iostream>
#include<vector>
#include<queue>

using namespace std;

void bfs_constant_width(vector<vector<int>> adj, vector<int> visited, int start, int width) {
    queue<int> q;
    q.push(start);
    visited[start] = 1;

    while (!q.empty()) {
        int nodes_explored = 0;
        int current_level_size = q.size();
        while (nodes_explored < width && current_level_size--) {
            int front = q.front();
            q.pop();
            cout << front << " ";
            nodes_explored++;
            for (int i = 0; i < adj[front].size(); i++) {
                if (adj[front][i] && !visited[i]) {
                    q.push(i);
                    visited[i] = 1;
                }
            }
        }
    }
}

void bfs_constant_level(vector<vector<int>> adj, vector<int> visited, int start) {
    queue<int> q;
    q.push(start);
    visited[start] = 1;

    while (!q.empty()) {
        int current_level_size = q.size();
        while (current_level_size--) {
            int front = q.front();
            q.pop();
            cout << front << " ";
            for (int i = 0; i < adj[front].size(); i++) {
                if (adj[front][i] && !visited[i]) {
                    q.push(i);
                    visited[i] = 1;
                }
            }
        }
    }
}

void bfs_variable_width(vector<vector<int>> adj, vector<int> visited, int start, vector<int> level_width) {
    queue<int> q;
    q.push(start);
    visited[start] = 1;
    int level = 0;

    while (!q.empty()) {
        int current_level_size = q.size();
        int nodes_explored = 0;
        int width = level_width[level];
        while (nodes_explored < width && current_level_size--) {
            int front = q.front();
            q.pop();
            cout << front << " ";
            nodes_explored++;

            for (int i = 0; i < adj[front].size(); i++) {
                if (adj[front][i] && !visited[i]) {
                    q.push(i);
                    visited[i] = 1;
                }
            }
        }

        level++;
        if (level >= level_width.size()) break;
    }
}

int main() {
    int nodes,edges;
    cout << "Enter the number of nodes: ";
    cin >> nodes;
    cout << "Enter the number of edges: ";
    cin >> edges;
    vector<vector<int>> adj(nodes, vector<int>(nodes));
    int v1,v2,cost;

    for(int i = 0;i<edges;i++)
    {
        cout<<"Enter vertices and then cost (v1 v2 cost): ";
        cin>>v1>>v2>>cost;
        adj[v1][v2] = cost;
    }
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            
            cout<<adj[i][j]<<" ";
        }
        cout<<endl;
    }
    int start;
    cout << "Enter the starting node: ";
    cin >> start;

    vector<int> visited(nodes, 0);
    int constant_width = 2; 
    vector<int> level_width = {2, 3, 1}; 

    cout << "\nBFS with constant width:\n";
    visited.assign(nodes, 0);
    bfs_constant_width(adj, visited, start, constant_width);

    cout << "\n\nBFS with constant level:\n";
    visited.assign(nodes, 0);
    bfs_constant_level(adj, visited, start);

    cout << "\n\nBFS with variable width:\n";
    visited.assign(nodes, 0);
    bfs_variable_width(adj, visited, start, level_width);

    return 0;
}
