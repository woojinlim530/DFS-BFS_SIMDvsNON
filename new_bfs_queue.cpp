#include <vector>
#include <queue>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

// BFS implementation
void bfs_queue(const std::vector<std::vector<int>> &graph, int start, std::vector<int> &visited)
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

// Function to add edges to the graph
void add_edge(std::vector<std::vector<int>> &graph, int from, int to)
{
    graph[from].push_back(to);
}

// Function to initialize the graph with random edges
void initialize_graph(std::vector<std::vector<int>> &graph, int num_edges)
{
    int graph_size = graph.size();
    for (int i = 0; i < num_edges; ++i)
    {
        int from = rand() % graph_size;
        int to = rand() % graph_size;
        if (from != to)
        {
            add_edge(graph, from, to);
        }
    }
}

int main()
{
    srand(static_cast<unsigned>(time(nullptr))); // Seed for randomness

    int graph_size = 1000; // Increase graph size here
    int num_edges = 5000;  // Increase number of edges here
    std::vector<std::vector<int>> graph(graph_size);
    std::vector<int> visited(graph_size, false);

    // Initialize the graph with random edges
    initialize_graph(graph, num_edges);

    // Run BFS
    auto start_time = std::chrono::high_resolution_clock::now();
    bfs_queue(graph, 0, visited);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end_time - start_time;

    std::cout << "Queue BFS with size " << graph_size << ": " << elapsed_time.count() << " s" << std::endl;

    //Optional: Print visited nodes for verification
    for (int i = 0; i < graph_size; ++i)
    {
        std::cout << "Node " << i << ": " << (visited[i] ? "Visited" : "Not Visited") << std::endl;
    }

    return 0;
}
