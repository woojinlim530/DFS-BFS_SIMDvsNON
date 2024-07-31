#include "bfs.h"
#include <vector>
#include <chrono>
#include <iostream>

// Function declaration
std::vector<std::vector<int>> create_graph(int n);

void test_bfs_with_sizes() {
    std::vector<int> sizes = {10, 100, 1000, 5000}; // Example sizes
    
    for (int size : sizes) {
        std::cout << "Testing graph with size " << size << std::endl;
        auto graph = create_graph(size);
        int start_node = 0;

        // Test queue-based BFS
        auto start_time = std::chrono::high_resolution_clock::now();
        int visited_count = bfs_queue(graph, start_node);
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end_time - start_time;
        std::cout << "Queue-based BFS took " << duration.count() << " seconds. Visited nodes: " << visited_count << std::endl;

        // Test deque-based BFS
        start_time = std::chrono::high_resolution_clock::now();
        visited_count = bfs_deque(graph, start_node);
        end_time = std::chrono::high_resolution_clock::now();
        duration = end_time - start_time;
        std::cout << "Deque-based BFS took " << duration.count() << " seconds. Visited nodes: " << visited_count << std::endl;

        // Test list-based BFS
        start_time = std::chrono::high_resolution_clock::now();
        visited_count = bfs_list(graph, start_node);
        end_time = std::chrono::high_resolution_clock::now();
        duration = end_time - start_time;
        std::cout << "List-based BFS took " << duration.count() << " seconds. Visited nodes: " << visited_count << std::endl;

        // Test SIMD BFS
        start_time = std::chrono::high_resolution_clock::now();
        visited_count = bfs_simd_queue(graph, start_node);
        end_time = std::chrono::high_resolution_clock::now();
        duration = end_time - start_time;
        std::cout << "SIMD BFS took " << duration.count() << " seconds. Visited nodes: " << visited_count << std::endl;
    }
}

int main() {
    test_bfs_with_sizes();
    return 0;
}
