#include <iostream>
#include <vector>
using namespace std;


void dfs_recursive(const vector<vector<int>>& graph, int node, vector<bool>& visited) {
    if (visited[node]) return;
    visited[node] = true;
    cout << node << " ";

    for (int neighbor : graph[node]) {
        dfs_recursive(graph, neighbor, visited);
    }
}

void dfs_recursive_wrapper(const vector<vector<int>>& graph, int start) {
    vector<bool> visited(graph.size(), false);
    dfs_recursive(graph, start, visited);
}
