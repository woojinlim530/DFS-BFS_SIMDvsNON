#include <vector>
#include <deque>
#include <chrono>
#include <iostream>
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

        for (size_t i = 0; i + 4 <= graph[node].size(); i += 4)
        {
            Vec4i neighbors(&graph[node][i]); // Load 4 neighbors
            Vec4i mask = Vec4i(
                visited[graph[node][i]],
                visited[graph[node][i + 1]],
                visited[graph[node][i + 2]],
                visited[graph[node][i + 3]]);
            Vec4i zero(0);
            Vec4i one(1);

            // Check if neighbors are visited
            mask = select(mask == zero, one, zero);

            for (int j = 0; j < 4; ++j)
            {
                if (mask[j] == 1)
                {
                    visited[neighbors[j]] = true; // Mark as visited
                    dq.push_back(neighbors[j]);   // Push to queue
                }
            }
        }

        // Handle remaining neighbors that don't fit in the SIMD vector
        for (size_t i = (graph[node].size() / 4) * 4; i < graph[node].size(); ++i)
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

    // Adding edges to the graph
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n && j < i + 10; ++j)
        {
            graph[i].push_back(j);
            graph[j].push_back(i);
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
