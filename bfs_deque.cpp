#include "bfs_deque.h"
#include <deque>
#include <vector>

void bfs_deque(const std::vector<std::vector<int>>& graph, int start, std::vector<int>& visited) {
    std::deque<int> q;
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
