#include "bfs_deque.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>

void run_test(int graph_size) {
    std::vector<std::vector<int>> graph(graph_size);
    std::vector<int> visited(graph_size, false);
    
    for (int i = 0; i < graph_size; ++i) {
        for (int j = 0; j < graph_size / 10; ++j) {
            int neighbor = rand() % graph_size;
            if (neighbor != i) {
                graph[i].push_back(neighbor);
            }
        }
    }

    auto start = std::chrono::high_resolution_clock::now();
    bfs_deque(graph, 0, visited);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Deque BFS with size " << graph_size << ": " << elapsed.count() << " s" << std::endl;
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    std::cout << "Running dummy tests for Deque BFS..." << std::endl;
    run_test(100);

    for (int size : {100, 1000, 10000, 100000}) {
        std::cout << "Testing with graph size: " << size << std::endl;
        run_test(size);
    }

    return 0;
}
