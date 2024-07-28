#include "vectorclass.h"
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

void dfs_simd(const vector<vector<int>>& graph, int start) {
    int num_nodes = graph.size();
    vector<bool> visited(num_nodes, false);
    stack<int> s;
    s.push(start);

    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (!visited[node]) {
            visited[node] = true;
            std::cout << node << " ";

            for (int i = 0; i < graph[node].size(); i += 4) {
                Vec4i adj_nodes(&graph[node][i]);
                Vec4i visited_mask;
                for (int j = 0; j < 4; ++j) {
                    int adj_node = adj_nodes[j];
                    if (adj_node < num_nodes && !visited[adj_node]) {
                        visited_mask.insert(j, 1);
                        s.push(adj_node);
                        visited[adj_node] = true;
                    }
                }
            }
        }
    }
}
