#include <vector>
#include <deque>
#include <chrono>
#include <iostream>
#include <random>
#include "vectorclass.h" // Ensure the correct path to the VectorClass library

// BFS using SIMD with a deque and recording BFS order
void bfs_simd_queue(const std::vector<std::vector<int>> &graph, int start, std::vector<int> &visited, std::vector<int> &bfs_order)
{
    std::deque<int> dq;
    dq.push_back(start);
    visited[start] = true;

    while (!dq.empty())
    {
        int node = dq.front();
        dq.pop_front();

        bfs_order.push_back(node); // Record the node visit order

        size_t num_neighbors = graph[node].size();
        size_t num_simd_batches = num_neighbors / 4;

        // Process neighbors in batches of 4 using SIMD
        for (size_t batch = 0; batch < num_simd_batches; ++batch)
        {
            size_t offset = batch * 4;

            // Load 4 neighbors
            Vec4i neighbors;
            neighbors.load(&graph[node][offset]);

            // Create masks for visited status
            Vec4i visited_indices;
            visited_indices.load(&visited[neighbors[0]]);
            Vec4ib visited_mask = visited_indices == 0; // Create mask for unvisited nodes

            Vec4i one(1);
            Vec4i zero(0);

            // Use the mask to determine which neighbors should be processed
            Vec4i to_process = select(visited_mask, one, zero);

            for (int i = 0; i < 4; ++i)
            {
                if (to_process[i] == 1)
                {
                    int neighbor = neighbors[i];
                    visited[neighbor] = true; // Mark as visited
                    dq.push_back(neighbor);   // Push to queue
                }
            }
        }

        // Handle remaining neighbors that don't fit in the SIMD vector
        for (size_t i = num_simd_batches * 4; i < num_neighbors; ++i)
        {
            int neighbor = graph[node][i];
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                dq.push_back(neighbor);
            }
        }
    }
}

// Print edges of the graph
void print_edges(const std::vector<std::vector<int>> &graph)
{
    for (int u = 0; u < graph.size(); ++u)
    {
        for (int v : graph[u])
        {
            if (u < v) // To avoid printing the same edge twice in an undirected graph
            {
                std::cout << "{" << u << ", " << v << "}" << std::endl;
            }
        }
    }
}

// Print BFS order
void print_bfs_order(const std::vector<int> &bfs_order)
{
    std::cout << "BFS Order:" << std::endl;
    for (int node : bfs_order)
    {
        std::cout << node << " ";
    }
    std::cout << std::endl;
}

int main()
{
    int n = 100000; // Graph size set to 100,000
    std::vector<std::vector<int>> graph(n);
    std::vector<int> visited(n, false);
    std::vector<int> bfs_order; // Vector to store BFS order

    // Create a random graph
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, n - 1);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 10; ++j)
        { // Adjust this to control the average number of edges per node
            int neighbor = dis(gen);
            if (neighbor != i && std::find(graph[i].begin(), graph[i].end(), neighbor) == graph[i].end())
            {
                graph[i].push_back(neighbor);
                graph[neighbor].push_back(i); // Undirected graph, add both directions
            }
        }
    }

    // Optionally, print edges before running BFS
    std::cout << "Edges in the graph:" << std::endl;
    print_edges(graph);

    auto start = std::chrono::high_resolution_clock::now();
    bfs_simd_queue(graph, 0, visited, bfs_order);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "SIMD Queue BFS with size " << n << ": " << duration.count() << " s" << std::endl;

    // Print BFS order
    print_bfs_order(bfs_order);

    return 0;
}
