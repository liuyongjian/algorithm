#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using std::cout;
using std::endl;
using std::pair;
using std::priority_queue;
using std::vector;

/*
  Prim算法是一种用于构建加权无向图的最小生成树（MST）的经典算法

  可以从任意节点出发来寻找最小生成树。
  某个点加入到被选取的点中后，解锁这个点出发的所有新的边。
  在所有解锁的边中选最小的边，然后看看这个边会不会形成环。
  如果会，不要当前边，继续考察剩下解锁的边中最小的边，重复第3步。
  如果不会，要当前边，将该边的指向点加入到被选取的点中，重复第2步。
  当所有点都被选取，最小生成树就得到了。

  关键点：
  1. 起始顶点的选择
  Prim算法可以从图中的任何顶点开始。选定的起始顶点作为最小生成树的第一个顶点。

  2. 使用优先队列
  使用优先队列（或最小堆）来存储所有横切边（连接树与非树顶点的边）。这样可以快速获取最小权重边，优化搜索过程。

  3. 边的选择
  在每一步中，从优先队列中选择权重最小的边。这条边是连接已经在MST中的顶点和不在MST中的顶点的边。

  4. 检查并更新
  检查这条边的目标顶点是否已经在MST中。如果不在，将其添加到MST中，并更新其邻接顶点的信息。
  如果边的目标顶点已在MST中，则舍弃这条边，继续选择下一条最小边。

  5. 更新优先队列
  每当一个新顶点加入到MST中时，需要更新优先队列。将该顶点的所有邻接边加入队列，但只有那些连接到尚未在MST中的顶点的边才会被加入。

  6. 环的预防
  由于算法只考虑连接树和非树顶点的边，因此不会形成环。这是Prim算法自然避免环形成的一个重要特性。

  7. 结束条件
  当所有的顶点都被加入到MST中时，算法结束。对于包含 V 个顶点的图，MST将包含 V−1
  条边。
*/

// 定义边的结构体
struct Edge {
  int weight;
  int to;
};

// 比较器，用于优先队列
class Compare {
public:
  bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
    return a.first > b.first; // 小顶堆
  }
};

// Prim算法实现
void prim(int V, vector<vector<Edge>> &adj) {
  vector<int> key(V, INT_MAX);  // 跟踪连接到MST的最小权重边
  vector<int> parent(V, -1);    // 跟踪MST的结构
  vector<bool> inMST(V, false); // 跟踪哪些顶点已经在MST中

  priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;

  // 从顶点0开始
  key[0] = 0;
  pq.push({0, 0}); // 权重和顶点

  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();

    if (inMST[u])
      continue; // 如果顶点已经在MST中，跳过

    inMST[u] = true; // 标记顶点u为已加入MST

    // 遍历所有与顶点u相连接的顶点v
    for (auto &edge : adj[u]) {
      int v = edge.to;
      int weight = edge.weight;

      // 如果v不在MST中，并且通过u到v的边权重小于当前记录的key[v]
      if (!inMST[v] && weight < key[v]) {
        parent[v] = u;
        key[v] = weight;
        pq.push({key[v], v});
      }
    }
  }

  // 打印构造的MST
  cout << "Edges in the MST:" << endl;
  for (int i = 1; i < V; ++i) {
    cout << parent[i] << " - " << i << " \tWeight: " << key[i] << endl;
  }
}

int main() {
  int V = 5;
  vector<vector<Edge>> adj(V);

  // 构建图
  adj[0] = {{2, 1}, {3, 3}};
  adj[1] = {{2, 0}, {3, 2}, {5, 3}, {6, 4}};
  adj[2] = {{3, 1}, {5, 4}};
  adj[3] = {{3, 0}, {5, 1}, {1, 4}};
  adj[4] = {{6, 1}, {5, 2}, {1, 3}};

  // 执行Prim算法
  prim(V, adj);

  return 0;
}
