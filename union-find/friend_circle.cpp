#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

// 班上有 N
// 名学生。其中有些人是朋友，有些则不是。他们的友谊具有是传递性。如果已知 A 是 B
// 的朋友，B 是 C 的朋友，那么我们可以认为 A 也是 C
// 的朋友。所谓的朋友圈，是指所有朋友的集合。给定一个 N * N 的矩阵
// M，表示班级中学生之间的朋友关系。如果M[i][j] = 1，表示已知第 i 个和 j
// 个学生互为朋友关系，否则为不知道。你必须输出所有学生中的已知的朋友圈总数。

class UnionFind {
public:
  UnionFind(int size) : parent(size), rank(size, 0), count(size) {
    for (int i = 0; i < size; ++i) {
      parent[i] = i; // 初始化，每个节点的父节点是自己
    }
  }

  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]); // 路径压缩
    }
    return parent[x];
  }

  void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
      // 按秩合并
      if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
      } else if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
      } else {
        parent[rootY] = rootX;
        rank[rootX]++; // 如果秩相同，则选择一个作为根，并增加秩
      }
      count--; // 每次合并集合，集合数量减少
    }
  }

  int getCount() const {
    return count; // 返回当前的集合数量
  }

private:
  vector<int> parent; // 父节点数组
  vector<int> rank;   // 秩数组
  int count;          // 集合数量
};

int findCircleNum(vector<vector<int>> &isConnected) {
  int n = isConnected.size();
  UnionFind uf(n); // 初始化并查集

  for (int i = 0; i < n; ++i) {
    // 这个循环开始于 i +
    // 1，意味着只考虑矩阵中的上三角部分（因为朋友关系是相互的，所以矩阵是对称的，无需重复处理对称部分）。
    // j 是与学生 i 比较的其他学生的索引。
    for (int j = i + 1; j < n; ++j) {
      if (isConnected[i][j] == 1) {
        uf.unionSets(i, j); // 如果两个学生是朋友，合并他们的集合
      }
    }
  }

  return uf.getCount(); // 返回总的朋友圈数量
}

int main() {
  // 示例使用：
  vector<vector<int>> matrix1 = {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}};

  vector<vector<int>> matrix2 = {{1, 1, 0}, {1, 1, 1}, {0, 1, 1}};

  cout << "Number of friend circles in matrix1: " << findCircleNum(matrix1)
       << endl;
  cout << "Number of friend circles in matrix2: " << findCircleNum(matrix2)
       << endl;

  return 0;
}
