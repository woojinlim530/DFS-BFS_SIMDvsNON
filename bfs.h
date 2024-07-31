#ifndef BFS_H
#define BFS_H

#include <vector>

// Function prototypes
int bfs_queue(const std::vector<std::vector<int>>& graph, int start_node);
int bfs_deque(const std::vector<std::vector<int>>& graph, int start_node);
int bfs_list(const std::vector<std::vector<int>>& graph, int start_node);
int bfs_simd_queue(const std::vector<std::vector<int>>& graph, int start_node);

// Function declaration
std::vector<std::vector<int>> create_graph(int n);

#endif // BFS_H
