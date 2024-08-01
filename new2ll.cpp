#include <vector>
#include <list>
#include <chrono>
#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

// BFS using a linked list and recording BFS order
void bfs_linked_list(const std::vector<std::vector<int>> &graph, int start, std::vector<bool> &visited, std::vector<int> &bfs_order)
{
    std::list<int> ll;
    ll.push_back(start);
    visited[start] = true;

    while (!ll.empty())
    {
        int node = ll.front();
        ll.pop_front();

        bfs_order.push_back(node); // Record the node visit order

        for (int neighbor : graph[node])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                ll.push_back(neighbor);
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
    int n = 100000; // Adjust the size
    std::vector<std::vector<int>> graph(n);

    // Seed the random number generator
    std::srand(std::time(nullptr));

    // Generate a random graph
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (std::rand() % 2 == 0)
            { // Randomly decide to add an edge
                graph[i].push_back(j);
                graph[j].push_back(i); // Undirected graph, add both directions
            }
        }
    }

    std::vector<bool> visited(n, false);
    std::vector<int> bfs_order; // Vector to store BFS order

    // Optionally, print edges before running BFS
    std::cout << "Edges in the graph:" << std::endl;
    print_edges(graph);

    auto start_time = std::chrono::high_resolution_clock::now();
    bfs_linked_list(graph, 0, visited, bfs_order);
    auto end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end_time - start_time;
    std::cout << "Linked List BFS with size " << n << ": " << elapsed.count() << " s" << std::endl;

    // Print BFS order
    print_bfs_order(bfs_order);

    return 0;
}
