#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::sort;
using std::vector;

/*
  Kruskal算法是一种求解最小生成树（MST）的贪心算法，它适用于加权无向图。

  总是从权值最小的边开始考虑，依次考察权值依次变大的边。
  当前的边要么进入最小生成树的集合，要么丢弃。
  如果当前的边进入最小生成树的集合中不会形成环，就要当前边。
  如果当前的边进入最小生成树的集合中会形成环，就不要当前边。
  考察完所有边之后，最小生成树的集合也得到了。

  关键点：
  1. 边的排序
  按权重排序：算法的第一步是将图中的所有边按照权重从小到大进行排序。这是因为Kruskal算法的核心思想是贪心地选择最小的边，前提是这条边不会与已选择的边形成环。

  2. 使用并查集
  并查集的作用：并查集是Kruskal算法中用于快速判断两个顶点是否属于同一个集合（即是否已经连接）的数据结构。通过并查集可以快速检查加入一条边是否会形成环。
  路径压缩和按秩合并：使用路径压缩和按秩合并优化并查集的操作，提高了算法的效率。

  3. 选择边构建MST
  贪心选择：遍历排序后的边列表，对于每条边，使用并查集检查其两个顶点是否已经连通：
  如果已连通，忽略这条边（因为加入会形成环）。
  如果未连通，将这条边加入MST并合并其两个顶点所在的集合。

  4. 环的检测
  防止环形成：核心的检测环操作是通过并查集完成的，确保MST中不会包含任何环，这是构建有效MST的必要条件。
*/

// 边结构体，包括起点、终点和权重
struct Edge {
  int src, dest, weight;
};

// 用于比较两条边的权重，用于排序
bool compareEdge(const Edge &a, const Edge &b) { return a.weight < b.weight; }

// 并查集结构，用于检测添加的边是否形成环
class UnionFind {
private:
  vector<int> root, rank;

public:
  UnionFind(int size) : root(size), rank(size, 0) {
    for (int i = 0; i < size; ++i) {
      root[i] = i;
    }
  }

  // 查找操作
  int find(int x) {
    if (root[x] != x) {
      root[x] = find(root[x]); // 路径压缩
    }
    return root[x];
  }

  // 合并操作
  void unionSet(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
      if (rank[rootX] > rank[rootY]) {
        root[rootY] = rootX;
      } else if (rank[rootX] < rank[rootY]) {
        root[rootX] = rootY;
      } else {
        root[rootY] = rootX;
        rank[rootX] += 1;
      }
    }
  }
};

// Kruskal算法实现
void kruskal(vector<Edge> &edges, int V) {
  sort(edges.begin(), edges.end(), compareEdge); // 按权重排序边
  UnionFind uf(V);
  vector<Edge> mst; // 存储最小生成树的边

  for (Edge &e : edges) {
    if (uf.find(e.src) != uf.find(e.dest)) {
      uf.unionSet(e.src, e.dest);
      mst.push_back(e);
      if (mst.size() == static_cast<size_t>(V - 1))
        break;
    }
  }

  // 打印最小生成树的边
  cout << "Edges in the Minimum Spanning Tree:" << endl;
  for (const Edge &e : mst) {
    cout << e.src << " - " << e.dest << " : " << e.weight << endl;
  }
}

int main() {
  vector<Edge> edges = {
      {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4} // 创建图的边
  };
  int V = 4; // 图的顶点数量

  kruskal(edges, V);
  return 0;
}
