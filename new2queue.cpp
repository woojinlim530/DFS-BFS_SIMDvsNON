#include <vector>
#include <queue>
#include <chrono>
#include <iostream>

void bfs_queue(const std::vector<std::vector<int>> &graph, int start, std::vector<bool> &visited)
{
    std::queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        for (int neighbor : graph[node])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

void print_edges(const std::vector<std::vector<int>> &graph)
{
    for (int u = 0; u < graph.size(); ++u)
    {
        for (int v : graph[u])
        {
            std::cout << "{" << u << ", " << v << "}" << std::endl;
        }
    }
}

int main()
{
    int n = 100000; // Adjust the size
    std::vector<std::vector<int>> graph(n);

    // Example: Manually adding edges for demonstration
    // Replace this with actual edge addition logic
    for (int i = 0; i < n - 1; ++i)
    {
        graph[i].push_back(i + 1);
        graph[i + 1].push_back(i); // Undirected graph, add both directions
    }

    std::vector<bool> visited(n, false);

    // Optionally, print edges before running BFS
    std::cout << "Edges in the graph:" << std::endl;
    print_edges(graph);

    auto start_time = std::chrono::high_resolution_clock::now();
    bfs_queue(graph, 0, visited);
    auto end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end_time - start_time;
    std::cout << "Queue BFS with size " << n << ": " << elapsed.count() << " s" << std::endl;

    return 0;
}
