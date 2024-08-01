#ifndef BFS_QUEUE_SIMD_H
#define BFS_QUEUE_SIMD_H

#include <vector>

void bfs_queue_simd(const std::vector<std::vector<int>>& graph, int start, std::vector<int>& visited);

#endif // BFS_QUEUE_SIMD_H
