#include <iostream>
#include <vector>

using namespace std;

/*
题目：
给定一个二维数组
matrix，你可以从任意位置出发，向上、下、左、右四个方向移动，要求返回从该矩阵中可以走出的最长的递增链的长度。

思路：
使用深度优先搜索（DFS）结合动态规划（通过记忆化技术）来求解二维数组中最长递增路径的长度。
关键在于使用DFS从每个单元格开始探索可能的递增路径，并通过一个记忆化矩阵（缓存）存储每个单元格的结果以避免重复计算。

关键点
1. 记忆化矩阵（缓存）：
使用一个二维数组 cache 来存储从每个单元格开始的最长递增路径的长度。
如果某个单元格的最长递增路径已计算，直接从 cache 获取结果，避免重复计算。
2. 递归DFS搜索：
对每个单元格使用DFS探索所有可能的递增路径。
检查四个方向（上、下、左、右）是否存在递增序列，递归地计算递增路径的长度。
更新当前单元格的最长路径长度，这是当前位置值加上从邻近单元格开始的最长递增路径长度。
3. 方向数组：
使用方向数组 directions 来简化对四个邻接方向的遍历，使代码更简洁。
4. 边界和合法性检查：
在移动到新位置前，首先确认新位置是否在矩阵范围内，且值大于当前单元格的值。

时间复杂度：
1.
DFS：对于每个单元格，DFS最多可能访问矩阵中的所有单元格一次。但由于记忆化的使用，每个单元格实际上只被完全遍历一次。
2.
记忆化的影响：记忆化确保每个单元格的DFS结果被计算一次且仅一次，每次后续访问都直接返回结果。
3. 整体时间复杂度：因此，算法的时间复杂度为O(m×n)，其中 m 和
n分别是矩阵的行数和列数。
*/

// 方向数组，表示上下左右四个方向的移动（行和列的变化）
const int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// 检查给定的新位置 (x, y) 是否在大小为 m x n 的网格或矩阵的边界内，
// 其中 m 是行数，n 是列数。
bool isValid(int x, int y, int m, int n) {
  return x >= 0 && x < m && y >= 0 && y < n;
}

// 从(x, y)位置出发，使用DFS和记忆化搜索寻找最长递增路径
int dfs(vector<vector<int>> &matrix, int x, int y, vector<vector<int>> &cache) {
  // 如果已经计算过这个位置，直接返回结果
  if (cache[x][y] != 0) {
    return cache[x][y];
  }

  // 初始长度为1，即包含当前单元格自身
  int maxLength = 1;

  // 探索四个方向
  for (auto dir : directions) {
    int newX = x + dir[0], newY = y + dir[1];

    // 检查新位置是否合法并且是否可以形成递增路径
    if (isValid(newX, newY, matrix.size(), matrix[0].size()) &&
        matrix[newX][newY] > matrix[x][y]) {
      int length = 1 + dfs(matrix, newX, newY, cache);
      maxLength = max(maxLength, length);
    }
  }

  // 保存结果到缓存
  cache[x][y] = maxLength;
  return maxLength;
}

// 主函数来处理整个矩阵
int longestIncreasingPath(vector<vector<int>> &matrix) {
  if (matrix.empty() || matrix[0].empty()) {
    return 0;
  }

  int m = matrix.size(), n = matrix[0].size();
  vector<vector<int>> cache(m, vector<int>(n, 0));
  int longestPath = 0;

  // 对每个单元格应用DFS搜索
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      longestPath = max(longestPath, dfs(matrix, i, j, cache));
    }
  }

  return longestPath;
}

// 测试代码
int main() {
  vector<vector<int>> matrix = {{1, 2, 3}, {6, 4, 5}, {7, 8, 9}};

  cout << "The longest increasing path is: " << longestIncreasingPath(matrix)
       << endl;
  return 0;
}
