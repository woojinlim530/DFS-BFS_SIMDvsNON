#include <vector>
#include <deque>
#include <chrono>
#include <iostream>

void bfs_deque(const std::vector<std::vector<int>> &graph, int start, std::vector<int> &visited)
{
    std::deque<int> dq;
    dq.push_back(start);
    visited[start] = true;

    while (!dq.empty())
    {
        int node = dq.front();
        dq.pop_front();

        for (int neighbor : graph[node])
        {
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
    int n = 1000000; // Larger graph
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
    bfs_deque(graph, 0, visited);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Deque BFS with size " << n << ": " << duration.count() << " s" << std::endl;
    
    return 0;
}
