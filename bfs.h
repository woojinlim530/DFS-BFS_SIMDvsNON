#ifndef BFS_H
#define BFS_H

#include <vector>
#include <queue>
#include <deque>
#include <list>
#include "vectorclass.h"  // Ensure this is the correct path for your VectorClass header

// BFS using queue
void bfs_queue(const std::vector<std::vector<int>>& graph, int start, std::vector<int>& visited);

// BFS using deque
void bfs_deque(const std::vector<std::vector<int>>& graph, int start, std::vector<int>& visited);

// BFS using linked list
void bfs_linked_list(const std::vector<std::vector<int>>& graph, int start, std::vector<int>& visited);

// SIMD BFS using queue
void bfs_queue_simd(const std::vector<std::vector<int>>& graph, int start, std::vector<int>& visited);

#endif  // BFS_H
