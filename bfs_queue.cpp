#include "bfs.h"
#include <queue>
#include <deque>
#include <list>
#include <vector>
#include "vectorclass.h"

void bfs_queue(const std::vector<std::vector<int>>& graph, int start, std::vector<int>& visited) {
    std::queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();


        const auto& neighbors = graph[node];

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}
