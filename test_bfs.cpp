#include "bfs.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Function prototypes
void run_test(int num_nodes);
void run_dummy_test(int num_nodes);

// Function to run a dummy test to warm up the system
void run_dummy_test(int num_nodes) {
    std::vector<std::vector<int>> dummy_graph(num_nodes);
    std::vector<int> dummy_visited(num_nodes, false);

    // Randomly connect nodes in the dummy graph
    std::srand(std::time(nullptr));
    for (int i = 0; i < num_nodes; ++i) {
        for (int j = i + 1; j < num_nodes; ++j) {
            if (std::rand() % 2 == 0) {
                dummy_graph[i].push_back(j);
                dummy_graph[j].push_back(i); // Undirected graph
            }
        }
    }

    // Run all BFS algorithms with dummy data
    bfs_queue(dummy_graph, 0, dummy_visited);
    bfs_deque(dummy_graph, 0, dummy_visited);
    bfs_linked_list(dummy_graph, 0, dummy_visited);
    bfs_queue_simd(dummy_graph, 0, dummy_visited);
}

// Function to run the BFS tests with actual data
void run_test(int num_nodes) {
    // Initialize the graph with random edges
    std::vector<std::vector<int>> graph(num_nodes);
    std::vector<int> visited(num_nodes, false);

    // Randomly connect nodes
    std::srand(std::time(nullptr));
    for (int i = 0; i < num_nodes; ++i) {
        for (int j = i + 1; j < num_nodes; ++j) {
            if (std::rand() % 2 == 0) {
                graph[i].push_back(j);
                graph[j].push_back(i); // Undirected graph
            }
        }
    }

    // Print graph size
    std::cout << "Testing with graph size: " << num_nodes << std::endl;

    // Run dummy tests before actual tests
    std::cout << "Running dummy tests..." << std::endl;
    run_dummy_test(num_nodes);

    // Measure BFS with Queue
    auto start = std::chrono::high_resolution_clock::now();
    bfs_queue(graph, 0, visited);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Queue BFS: " << elapsed.count() << " s" << std::endl;

    // Reset visited vector
    std::fill(visited.begin(), visited.end(), false);

    // Measure BFS with Deque
    start = std::chrono::high_resolution_clock::now();
    bfs_deque(graph, 0, visited);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Deque BFS: " << elapsed.count() << " s" << std::endl;

    // Reset visited vector
    std::fill(visited.begin(), visited.end(), false);

    // Measure BFS with Linked List
    start = std::chrono::high_resolution_clock::now();
    bfs_linked_list(graph, 0, visited);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Linked List BFS: " << elapsed.count() << " s" << std::endl;

    // Reset visited vector
    std::fill(visited.begin(), visited.end(), false);

    // Measure BFS with SIMD Queue
    start = std::chrono::high_resolution_clock::now();
    bfs_queue_simd(graph, 0, visited);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "SIMD Queue BFS: " << elapsed.count() << " s" << std::endl;
}

int main() {
    // Define graph sizes to test
    std::vector<int> sizes = {100, 1000, 10000, 100000, 1000000};

    for (int size : sizes) {
        run_test(size);
    }

    return 0;
}
