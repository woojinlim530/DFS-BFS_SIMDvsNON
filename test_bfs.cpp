#include <iostream>
#include <vector>
#include <chrono>
#include "bfs.h"

void run_bfs_tests(const std::vector<std::vector<int>>& graph, int start, const std::string& size_label) {
    std::vector<int> visited(graph.size(), false);

    auto start_time = std::chrono::high_resolution_clock::now();
    bfs_queue(graph, start, visited);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end_time - start_time;
    std::cout << size_label << " Queue BFS: " << diff.count() << " s\n";

    std::fill(visited.begin(), visited.end(), false);
    start_time = std::chrono::high_resolution_clock::now();
    bfs_deque(graph, start, visited);
    end_time = std::chrono::high_resolution_clock::now();
    diff = end_time - start_time;
    std::cout << size_label << " Deque BFS: " << diff.count() << " s\n";

    std::fill(visited.begin(), visited.end(), false);
    start_time = std::chrono::high_resolution_clock::now();
    bfs_linked_list(graph, start, visited);
    end_time = std::chrono::high_resolution_clock::now();
    diff = end_time - start_time;
    std::cout << size_label << " Linked List BFS: " << diff.count() << " s\n";

    std::fill(visited.begin(), visited.end(), false);
    start_time = std::chrono::high_resolution_clock::now();
    bfs_queue_simd(graph, start, visited);
    end_time = std::chrono::high_resolution_clock::now();
    diff = end_time - start_time;
    std::cout << size_label << " SIMD Queue BFS: " << diff.count() << " s\n";
}

void dummy_tests(const std::vector<std::vector<int>>& graph, int start) {
    std::vector<int> dummy(graph.size(), false);

    for (int i = 0; i < 3; ++i) {
        bfs_queue(graph, start, dummy);
        bfs_deque(graph, start, dummy);
        bfs_linked_list(graph, start, dummy);
        bfs_queue_simd(graph, start, dummy);
    }
}

std::vector<std::vector<int>> generate_graph(int size) {
    std::vector<std::vector<int>> graph(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < 10; ++j) {  // Example graph structure
            int neighbor = (i + j) % size;
            graph[i].push_back(neighbor);
        }
    }
    return graph;
}

int main() {
    std::vector<std::pair<int, std::string>> sizes = {
        {1024, "1K"}, 
        {2048, "2K"}, 
        {4096, "4K"}, 
        {8192, "8K"}, 
        {16384, "16K"},
        {32768, "32K"},
        {65536, "64K"},
        {131072, "128K"},
        {262144, "256K"},
        {524288, "512K"},
        {1048576, "1M"}
    };

    for (const auto& [size, label] : sizes) {
        auto graph = generate_graph(size);
        std::cout << "Testing with graph size: " << label << "\n";
        
        dummy_tests(graph, 0);  // Run dummy tests before the actual tests
        std::cout <<"dummy test success\n";
        run_bfs_tests(graph, 0, label);  // Run actual BFS tests
    }

    return 0;
}
