#include <vector>
#include <deque>
#include <chrono>
#include <iostream>
#include "vectorclass.h" // Ensure the correct path to the VectorClass library

void bfs_simd_queue(const std::vector<std::vector<int>> &graph, int start, std::vector<int> &visited)
{
    std::deque<int> dq;
    dq.push_back(start);
    visited[start] = true;

    while (!dq.empty())
    {
        int node = dq.front();
        dq.pop_front();

        for (size_t i = 0; i + 4 <= graph[node].size(); i += 4)
        {
            Vec4i neighbors(&graph[node][i]);
            Vec4i mask = Vec4i(visited[graph[node][i]], visited[graph[node][i + 1]], visited[graph[node][i + 2]], visited[graph[node][i + 3]]);
            Vec4i zero(0);
            Vec4i one(1);

            mask = select(mask == zero, one, zero);
            for (int j = 0; j < 4; ++j)
            {
                if (mask[j] == 1)
                {
                    visited[neighbors[j]] = true;
                    dq.push_back(neighbors[j]);
                }
            }
        }

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

int main()
{
    int n = 10000; // Larger graph
    std::vector<std::vector<int>> graph(n);
    std::vector<int> visited(n, false);

    // Adding edges to the graph
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n && j < i + 10; ++j)
        {
            graph[i].push_back(j);
            graph[j].push_back(i);
        }
    }

    auto start = std::chrono::high_resolution_clock::now();
    bfs_simd_queue(graph, 0, visited);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "SIMD Queue BFS with size " << n << ": " << duration.count() << " s" << std::endl;

    return 0;
}
