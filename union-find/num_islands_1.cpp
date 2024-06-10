#include <iostream>
#include <numeric>
#include <vector>

using std::cout;
using std::endl;
using std::pair;
using std::vector;
/*
  题目：
  一个模拟动态增加陆地的场景，并要求在每次增加陆地后计算岛屿的数量

  初始状态：

  给定一个 m 行 n 列的二维网格，初始时网格中的所有位置都充满了水（用 0 表示）。
  操作：

  我们可以进行一系列的 addLand 操作，将网格中的某些位置从水（0）变成陆地（1）。
  计算岛屿数量：

  每次执行 addLand 操作后，需要计算并返回当前网格中岛屿的数量。
  岛屿是由水平或垂直方向上相邻的陆地（1）组成的区域。
  可以假设网格的四个边缘都被水包围。

  关键点：
  遍历每个 addLand 操作，更新并查集，将新变成陆地的点与其相邻的陆地合并。
  在每次操作后，通过并查集查询当前连通分量的数量，即为当前的岛屿数量。
*/

class UnionFind {
public:
  UnionFind(int size) : parent(size), rank(size, 0), count(0) {
    std::iota(parent.begin(), parent.end(),
              0); // Initialize parent to be itself
  }

  int find(int p) {
    if (parent[p] != p) {
      parent[p] = find(parent[p]); // Path compression
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

  void incrementCount() { count++; }
  void decrementCount() { count--; }
  int getCount() const { return count; }
  void setParent(int p) { parent[p] = p; }

private:
  vector<int> parent;
  vector<int> rank;
  int count;
};

vector<int> numIslands1(int m, int n, vector<pair<int, int>> &positions) {
  UnionFind uf(m * n);
  vector<int> result;
  vector<vector<bool>> grid(m, vector<bool>(n, false));
  vector<int> directions = {0, 1, 0, -1, 0};

  for (const auto &pos : positions) {
    int r = pos.first, c = pos.second;
    // 检查该位置是否已经是陆地，如果是，直接记录当前岛屿数量。否则，将该位置标记为陆地，并增加岛屿数量。
    if (grid[r][c]) {
      result.push_back(uf.getCount());
      continue;
    }
    grid[r][c] = true;
    uf.incrementCount();

    // 将当前位置的索引计算为 index。
    int index = r * n + c;

    for (int i = 0; i < 4; ++i) {
      // 计算邻居的行列索引 nr 和 nc。
      int nr = r + directions[i], nc = c + directions[i + 1];
      // 如果邻居在网格范围内且是陆地，则检查当前节点和邻居是否属于不同的集合
      if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc]) {
        int neighborIndex = nr * n + nc;
        // 如果属于不同的集合，则合并这两个集合
        if (uf.find(index) != uf.find(neighborIndex)) {
          uf.unionSets(index, neighborIndex);
        }
      }
    }
    result.push_back(uf.getCount());
  }
  return result;
}

int main() {
  int m = 3, n = 3;
  vector<pair<int, int>> positions = {{0, 0}, {0, 1}, {1, 2}, {2, 1}};

  vector<int> result = numIslands1(m, n, positions);
  for (int count : result) {
    cout << count << " ";
  }
  cout << endl;

  return 0;
}
