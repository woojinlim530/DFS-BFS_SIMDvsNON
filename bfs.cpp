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

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

void bfs_deque(const std::vector<std::vector<int>>& graph, int start, std::vector<int>& visited) {
    std::deque<int> dq;
    dq.push_back(start);
    visited[start] = true;

    while (!dq.empty()) {
        int node = dq.front();
        dq.pop_front();

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                dq.push_back(neighbor);
            }
        }
    }
}

void bfs_linked_list(const std::vector<std::vector<int>>& graph, int start, std::vector<int>& visited) {
    std::list<int> lst;
    lst.push_back(start);
    visited[start] = true;

    while (!lst.empty()) {
        int node = lst.front();
        lst.pop_front();

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                lst.push_back(neighbor);
            }
        }
    }
}

void bfs_queue_simd(const std::vector<std::vector<int>>& graph, int start, std::vector<int>& visited) {
    std::queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        // Assuming Vec4i for 128-bit SIMD with 4 integers
        for (size_t i = 0; i < graph[node].size(); i += 4) {
            // Load 4 integers from graph[node] into SIMD register
            Vec4i neighbors;
            neighbors.load(&graph[node][i]);

            for (size_t j = 0; j < 4 && i + j < graph[node].size(); ++j) {
                int neighbor = neighbors[j];
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }
}
