#include <iostream>
#include <mutex>
#include <numeric>
#include <omp.h>
#include <thread>
#include <vector>

using std::cout;
using std::endl;
using std::mutex;
using std::pair;
using std::ref;
using std::thread;
using std::vector;

/*
  题目：
  计算岛屿数量。

  给定一个二维数组 matrix，其中的值要么是 1 要么是 0。相邻（上下左右方向）的 1
  被认为属于同一个岛屿。要求返回 matrix 中岛屿的数量。

  扩展：如果岛屿数量极大设计一种可行的并行计算方案

  关键点:
  使用OpenMP或其他并行框架，将网格划分为多个子区域，并行处理每个子区域。在并行过程中，使用互斥锁保护共享资源。
*/

class UnionFind {
public:
  vector<int> parent;
  vector<int> rank;
  int count;

  UnionFind(int size) : parent(size), rank(size, 0), count(0) {
    iota(parent.begin(), parent.end(), 0);
  }

  int find(int p) {
    if (parent[p] != p) {
      parent[p] = find(parent[p]);
    }
    return parent[p];
  }

  void unionSets(int p, int q) {
    int rootP = find(p);
    int rootQ = find(q);
    if (rootP != rootQ) {
      if (rank[rootP] > rank[rootQ]) {
        parent[rootQ] = rootP;
      } else if (rank[rootP] < rank[rootQ]) {
        parent[rootP] = rootQ;
      } else {
        parent[rootQ] = rootP;
        rank[rootP]++;
      }
      count--;
    }
  }
};

// void processSegment(vector<vector<int>> &grid, int startRow, int endRow,
//                     UnionFind &uf, int m, int n) {
//   for (int i = startRow; i < endRow; i++) {
//     for (int j = 0; j < n; j++) {
//       if (grid[i][j] == 1) {
//         int index = i * n + j;
//         if (i > 0 && grid[i - 1][j] == 1)
//           uf.unionSets(index, (i - 1) * n + j);
//         if (i < m - 1 && grid[i + 1][j] == 1)
//           uf.unionSets(index, (i + 1) * n + j);
//         if (j > 0 && grid[i][j - 1] == 1)
//           uf.unionSets(index, i * n + (j - 1));
//         if (j < n - 1 && grid[i][j + 1] == 1)
//           uf.unionSets(index, i * n + (j + 1));
//       }
//     }
//   }
// }

void processSegment(vector<vector<int>> &grid, int startRow, int endRow,
                    UnionFind &uf, int m, int n) {
  vector<pair<int, int>> directions = {
      {-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 上，下，左，右

  for (int i = startRow; i < endRow; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == 1) {
        int index = i * n + j; // 当前位置的线性索引

        for (auto &dir : directions) {
          int ni = i + dir.first, nj = j + dir.second; // 计算相邻坐标
          if (ni >= 0 && ni < m && nj >= 0 && nj < n && grid[ni][nj] == 1) {
            int neighborIndex = ni * n + nj; // 相邻位置的线性索引
            uf.unionSets(index, neighborIndex);
          }
        }
      }
    }
  }
}

int countIslands(vector<vector<int>> &grid) {
  int m = grid.size(), n = grid[0].size();
  UnionFind uf(m * n);

  vector<thread> threads;
  int numThreads = 4; // Example: use 4 threads
  int segmentSize = m / numThreads;
  for (int i = 0; i < numThreads; ++i) {
    int startRow = i * segmentSize;
    int endRow = (i == numThreads - 1) ? m : (i + 1) * segmentSize;
    threads.push_back(
        thread(processSegment, ref(grid), startRow, endRow, ref(uf), m, n));
  }

  for (auto &t : threads) {
    t.join();
  }

  // Reduce the results from the union find
  int totalIslands = 0;
  for (int i = 0; i < m * n; ++i) {
    if (uf.find(i) == i && grid[i / n][i % n] == 1) {
      totalIslands++;
    }
  }
  return totalIslands;
}

// 使用OpenMP进行并行处理
int countIslands1(vector<vector<int>> &grid) {
  int m = grid.size(), n = grid[0].size();
  UnionFind uf(m * n);

#pragma omp parallel for
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (grid[i][j] == 1) {
        processSegment(grid, i, i + 1, uf, m, n);
      }
    }
  }

  int totalIslands = 0;
  for (int i = 0; i < m * n; ++i) {
    if (uf.find(i) == i && grid[i / n][i % n] == 1) {
      totalIslands++;
    }
  }
  return totalIslands;
}

int main() {
  vector<vector<int>> grid = {{1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 1},
                              {1, 0, 1, 1, 1, 1, 1}, {1, 0, 1, 0, 0, 0, 0},
                              {1, 0, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 1},
                              {1, 1, 1, 1, 1, 1, 1}};

  int numIslands = countIslands(grid);
  int numIslands1 = countIslands1(grid);
  cout << "Number of islands: " << numIslands << endl;
  cout << "Number of islands calculate with OpenMP: " << numIslands1 << endl;

  return 0;
}
