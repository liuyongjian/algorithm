#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

/*
  题目:
  计算岛屿数量。
  给定一个二维数组 matrix，其中的值要么是 1 要么是 0。相邻（上下左右方向）的 1
  被认为属于同一个岛屿。要求返回 matrix 中岛屿的数量。

  关键点：只需向右和向下检查相邻单元格，或者只向上和向左合并，因为每个单元格在处理时都会考虑它之前的相邻单元格，避免重复工作并提高效率。
*/

class UnionFind {
public:
  // parent(m * n)：创建一个大小为 m * n
  // 的向量，用来存储每个元素的父节点。在并查集中，每个元素最初的父节点是它自己，表示每个元素最开始都是一个独立的集合。
  // rank(m * n, 0)：创建一个大小为 m *
  // n，初始值为0的向量，用来存储每个集合的秩。秩用于优化并查集的性能，通常代表了集合的高度或深度。
  UnionFind(int m, int n) : parent(m * n), rank(m * n, 0), count(0) {
    for (int i = 0; i < m * n; ++i) {
      parent[i] = i;
    }
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

  void setParent(int p) {
    int rootP = find(p);
    if (parent[rootP] == rootP) {
      count++;
    }
  }

  int getCount() { return count; }

private:
  vector<int> parent;
  vector<int> rank;
  int count;
};

int numIslands(vector<vector<char>> &grid) {
  if (grid.empty())
    return 0;
  int m = grid.size();
  int n = grid[0].size();
  UnionFind uf(m, n);

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      // 检查是否为陆地: 如果当前元素 grid[i][j] 是
      // '1'，则对其进行处理，考虑它与四周的连接关系
      if (grid[i][j] == '1') {
        // 设置父节点: 调用 setParent(i * n +
        // j)，确保当前的陆地块在并查集中是活跃的，并可能增加岛屿计数。
        uf.setParent(i * n + j);
        // 向上合并：如果当前元素的上方元素 grid[i-1][j] 也是 '1'，则调用
        // unionSets(i * n + j, (i-1) * n + j)，合并当前元素和上方元素的集合
        if (i > 0 && grid[i - 1][j] == '1') {
          uf.unionSets(i * n + j, (i - 1) * n + j);
        }
        // 向左合并：如果当前元素的左方元素 grid[i][j-1] 也是 '1'，则调用
        // unionSets(i * n + j, i * n + (j-1))，合并当前元素和左方元素的集合。
        if (j > 0 && grid[i][j - 1] == '1') {
          uf.unionSets(i * n + j, i * n + (j - 1));
        }
      }
    }
  }

  return uf.getCount();
}

// 方式二： 使用深度优先遍历
class IslandCounter {
public:
  // 方向数组，用于简化移动逻辑：下，上，右，左
  vector<int> dx{1, -1, 0, 0};
  vector<int> dy{0, 0, 1, -1};

  // 标记并探索整个岛屿
  void markIsland(vector<vector<char>> &grid, int x, int y, int n, int m) {
    // 将当前位置标记为'0'以避免重复访问
    grid[x][y] = '0';

    // 遍历四个方向
    for (int i = 0; i < 4; ++i) {
      int nx = x + dx[i];
      int ny = y + dy[i];

      // 检查新位置是否在边界内，并且是否为'1'
      if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == '1') {
        markIsland(grid, nx, ny, n, m);
      }
    }
  }

  // 计算岛屿数量的主函数
  int numIslands(vector<vector<char>> &grid) {
    if (grid.empty())
      return 0;
    int n = grid.size();
    int m = grid[0].size();
    int num_islands = 0;

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (grid[i][j] == '1') {
          markIsland(grid, i, j, n, m);
          num_islands++; // 完成一次标记后岛屿数量加一
        }
      }
    }

    return num_islands;
  }
};

int main() {
  vector<vector<char>> grid = {{'1', '1', '0', '0', '0'},
                               {'1', '1', '0', '0', '0'},
                               {'0', '0', '1', '0', '0'},
                               {'0', '0', '0', '1', '1'}};

  cout << "Number of islands: " << numIslands(grid) << endl;

  IslandCounter ic;
  cout << "Number of island calculated with DFS: " << ic.numIslands(grid)
       << endl;
  return 0;
}
