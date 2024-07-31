#include <iostream>
#include <vector>
#include <chrono>
#include "bfs.h"

void test_bfs(const std::vector<std::vector<int>>& graph, int start) {
    std::vector<int> visited(graph.size(), false);

    auto start_time = std::chrono::high_resolution_clock::now();
    bfs_queue(graph, start, visited);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end_time - start_time;
    std::cout << "Queue BFS: " << diff.count() << " s\n";

    std::fill(visited.begin(), visited.end(), false);
    start_time = std::chrono::high_resolution_clock::now();
    bfs_deque(graph, start, visited);
    end_time = std::chrono::high_resolution_clock::now();
    diff = end_time - start_time;
    std::cout << "Deque BFS: " << diff.count() << " s\n";

    std::fill(visited.begin(), visited.end(), false);
    start_time = std::chrono::high_resolution_clock::now();
    bfs_linked_list(graph, start, visited);
    end_time = std::chrono::high_resolution_clock::now();
    diff = end_time - start_time;
    std::cout << "Linked List BFS: " << diff.count() << " s\n";

    std::fill(visited.begin(), visited.end(), false);
    start_time = std::chrono::high_resolution_clock::now();
    bfs_queue_simd(graph, start, visited);
    end_time = std::chrono::high_resolution_clock::now();
    diff = end_time - start_time;
    std::cout << "SIMD Queue BFS: " << diff.count() << " s\n";
}

int main() {
    int sizes[] = {100, 1000, 10000};  // Different sizes for testing
    for (int size : sizes) {
        std::vector<std::vector<int>> graph(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < 10; ++j) {  // Example graph structure
                int neighbor = (i + j) % size;
                graph[i].push_back(neighbor);
            }
        }
        std::cout << "Testing with graph size: " << size << "\n";
        test_bfs(graph, 0);
    }

    return 0;
}
