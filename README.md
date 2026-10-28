# Memory Locality and Branch Predictability in BFS: An Analysis of Data Structures and SIMD Optimization

An empirical performance analysis investigating the impact of frontier data structures (Queue, Deque, Linked List), Agner Fog's Vector Class Library (SIMD), memory locality (cache-miss ratios via Linux `perf`), and branch predictability on Breadth-First Search (BFS) execution in C++.

* [Direct Link to Full Research Report (PDF)](./Memory%20Locality%20and%20Branch%20Predictability%20in%20BFS.pdf)

---

## Overview

Breadth-First Search (BFS) is a fundamental graph traversal algorithm that explores all vertices at the current depth before advancing to subsequent levels. In practical implementations, traversal throughput is heavily constrained by:

1. **Frontier Container Overhead**: Memory allocation patterns and push/pop latency across standard containers.
2. **Memory Hierarchy Limits**: Data cache misses incurred when the working set of visited vertices and adjacency structures outgrows the CPU cache.
3. **Branch Predictor Pressure**: Pipeline stalls caused by unpredictable visited checks in irregular/random graphs.

This project quantitatively profiles BFS across four core dimensions:
* **Container Benchmark**: `std::queue` vs. `std::deque` vs. Linked List.
* **Vectorized Execution**: Standard Deque BFS vs. SIMD-optimized Deque BFS using Agner Fog's Vector Class Library.
* **Cache Locality Profiling**: Correlation between graph node scale ($N = 10$ to $10,000$) and cache-miss percentages.
* **Branch Predictability**: Branch misprediction and cache behavior on Random Graphs vs. Linear Topologies.

---

## Experimental Setup & Tools

* **Benchmarking Harness**: C++ `std::chrono` for high-resolution timing (averaged over 10 iterations per node configuration to eliminate random noise).
* **Hardware Profiling**: Linux `perf` subsystem for tracking hardware performance counters (`cache-references`, `cache-misses`, `branch-instructions`, `branch-misses`).
* **Vectorization**: Agner Fog's C++ Vector Class Library (`vectorclass`) applied to visited-list and traversal tracking.
* **Source Files**:
  * `new2queue.cpp` / `new2queue.h`: `std::queue` based BFS
  * `new2deque.cpp` / `new2deque.h`: `std::deque` based BFS
  * `new2ll.cpp` / `new2ll.h`: Linked List based BFS
  * `new2simd.cpp` / `new2simd.h`: SIMD-accelerated Deque BFS

---

## Benchmark Results & Empirical Findings

### 1. Data Structure Comparison (Queue vs. Deque vs. Linked List)

Average execution time (seconds) across node counts:

| Nodes ($N$) | Deque (s) | Queue (s) | Linked List (s) |
|---|---|---|---|
| **10** | **0.0000031412** | 0.0000033909 | 0.0000038413 |
| **100** | 0.0000915683 | **0.0000911877** | 0.0000945236 |
| **1,000** | 0.0072954740 | 0.0073052250 | **0.0072592350** |
| **10,000** | 0.7101527000 | 0.7122860000 | **0.7064300000** |

* **Small Graphs ($N = 10$)**: `std::deque` demonstrated the lowest latency due to efficient buffer management, while the Linked List was the least efficient ($0.0000031412$s vs $0.0000038413$s).
* **Large Graphs ($N = 10,000$)**: The Linked List marginally surpassed standard queue containers in execution time ($0.70643$s vs $0.712286$s).

---

### 2. SIMD Optimization (Deque vs. SIMD Deque)

Evaluating standard Deque BFS against Deque BFS with SIMD-vectorized visited-state and traversal processing:

| Nodes ($N$) | Standard Deque (s) | SIMD Deque (s) | Speedup Factor |
|---|---|---|---|
| **10** | 0.0000031412 | 0.0000012703 | **~2.47x** |
| **100** | 0.0000915683 | 0.0000094526 | **~9.69x** |
| **1,000** | 0.0072954740 | 0.0003335608 | **~21.87x** |
| **10,000** | 0.7101527000 | 0.0363679800 | **~19.53x** |
| **100,000** | 70.34690000 | 3.47051000 | **~20.27x** |

* **Throughput Scaling**: SIMD optimization delivered a **2x to 23x speedup** across all evaluated node counts.
* **Vector Utilization**: Applying vector operations to the visited list and BFS order list significantly reduced scalar instruction overhead, maintaining high efficiency as node counts reached 100,000.

---

### 3. Memory Locality & Cache-Miss Analysis

Using Linux `perf`, cache-reference and cache-miss metrics were recorded across node sizes from 10 to 10,000:

* **Threshold Effect at $N \approx 300$**: The cache-miss percentage rises sharply once the graph exceeds approximately 300 nodes, transitioning from ~16% to over 34%, plateauing near ~40% at $N = 10,000$.
* **Analysis**: Beyond 300 nodes, the working set size exceeds CPU cache capacity. The increase in per-node execution time at scale directly correlates with this increased cache-miss rate.

---

### 4. Branch Predictability (Linear vs. Random Graph at $N = 10,000$)

Comparing a deterministic linear topology ($1 \to 2 \to 3 \to \dots$) against an irregular random graph:

| Metric | Linear Graph | Random Graph | Difference |
|---|---|---|---|
| **Average Branch Miss %** | 0.25% | 0.73% | **+0.48%** (~2.9x higher) |
| **Average Cache Miss %** | ~28.5% | ~39.8% | **+11.3%** |

* **Branch Penalty**: Stochastic edge generation creates high-entropy conditions (near 50-50 branch probability via `rand() % 2`), degrading hardware branch predictor accuracy.
* **Predictability-Cache Coupling**: The linear graph achieved a lower cache-miss rate (~28.5% vs ~39.8%). Predictable branch paths enable hardware prefetchers to anticipate memory accesses along the traversal frontier.

---

## Compilation & Usage

### Prerequisites
* GCC or Clang supporting C++17
* Agner Fog's Vector Class Library (`vectorclass`) in the include path
* Linux `perf` subsystem for hardware profiling

### Build

```bash
# Compile Deque BFS baseline
g++ -O3 -std=c++17 new2deque.cpp -o bfs_deque

# Compile SIMD-optimized BFS
g++ -O3 -mavx2 -std=c++17 -I./vectorclass new2simd.cpp -o bfs_simd
