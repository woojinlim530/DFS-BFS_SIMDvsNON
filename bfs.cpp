#include "bfs.h"
#include <vector>
#include <queue>
#include <deque>
#include <list>
#include <immintrin.h>
#include <iostream>

std::vector<std::vector<int>> create_graph(int n) {
    std::vector<std::vector<int>> graph(n);
    for (int i = 0; i < n - 1; ++i) {
        graph[i].push_back(i + 1); // Connect node i to node i+1
        graph[i + 1].push_back(i); // Connect node i+1 back to node i
    }
    return graph;
}
// Queue-based BFS implementation
int bfs_queue(const std::vector<std::vector<int>>& graph, int start_node) {
    std::vector<bool> visited(graph.size(), false);
    std::queue<int> q;
    int visited_node_count = 0;

    q.push(start_node);
    visited[start_node] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        ++visited_node_count;

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return visited_node_count;
}

// Deque-based BFS implementation
int bfs_deque(const std::vector<std::vector<int>>& graph, int start_node) {
    std::vector<bool> visited(graph.size(), false);
    std::deque<int> dq;
    int visited_node_count = 0;

    dq.push_back(start_node);
    visited[start_node] = true;

    while (!dq.empty()) {
        int node = dq.front();
        dq.pop_front();
        ++visited_node_count;

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                dq.push_back(neighbor);
            }
        }
    }

    return visited_node_count;
}

// List-based BFS implementation
int bfs_list(const std::vector<std::vector<int>>& graph, int start_node) {
    std::vector<bool> visited(graph.size(), false);
    std::list<int> l;
    int visited_node_count = 0;

    l.push_back(start_node);
    visited[start_node] = true;

    while (!l.empty()) {
        int node = l.front();
        l.pop_front();
        ++visited_node_count;

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                l.push_back(neighbor);
            }
        }
    }

    return visited_node_count;
}

// SIMD-based BFS implementation
int bfs_simd_queue(const std::vector<std::vector<int>>& graph, int start_node) {
    std::vector<bool> visited(graph.size(), false);
    std::queue<int> q;
    int visited_node_count = 0;

    // SIMD-related definitions
    const int VECTOR_SIZE = 8;
    const int VECTOR_MASK = (1 << VECTOR_SIZE) - 1;

    // SIMD initialization
    __m256i simd_visited = _mm256_setzero_si256();
    __m256i mask = _mm256_set1_epi32(VECTOR_MASK);

    q.push(start_node);
    visited[start_node] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        ++visited_node_count;

        __m256i index_vec = _mm256_set1_epi32(node);
        __m256i mask_vec = _mm256_set1_epi32(1 << (node % VECTOR_SIZE));
        
        simd_visited = _mm256_or_si256(simd_visited, mask_vec);

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return visited_node_count;
}
