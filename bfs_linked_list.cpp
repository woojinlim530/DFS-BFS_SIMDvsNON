#include "bfs_linked_list.h"
#include <list>
#include <vector>

void bfs_linked_list(const std::vector<std::vector<int>>& graph, int start, std::vector<int>& visited) {
    std::list<int> q;
    q.push_back(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop_front();

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push_back(neighbor);
            }
        }
    }
}
