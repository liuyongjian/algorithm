
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
  Dijkstra算法用于在图中找到一个节点到其他所有节点的最短路径。它适用于包含非负权重边的有向和无向图。

  核心思想是贪心策略，逐步扩展最短路径树。以下是算法的基本步骤：

  初始化：
  将所有节点的最短路径估计值设为无穷大，除了源节点，它的最短路径值设为0。
  使用一个优先队列来保存所有待处理的节点，优先队列基于节点的最短路径估计值进行排序。

  处理节点：
  从优先队列中取出具有最小估计距离的节点（开始时是源节点）。
  对于当前节点的每个邻接节点，计算通过当前节点到达它的距离。如果这个距离小于已知的最短路径，更新这个邻接节点的最短路径估计值，并在优先队列中更新它。

  重复步骤：
  重复上述过程，直到优先队列为空，或者所有可达节点都已被处理。

  终止：
  当所有节点都被访问后，算法结束。此时，源节点到图中所有其他节点的最短路径已经找到。

  关键点

  1.
  非负权重：Dijkstra算法要求图中所有边的权重非负。这是因为算法基于贪心策略，假设一旦节点的最短路径被确定，它就不会再被更新。

  2.
  优先队列：使用优先队列是为了每次能快速选出当前未处理的最近节点，保证算法的效率。

  3.
  更新邻接节点：每次从队列中取出一个节点后，都需要更新它所有邻接节点的最短路径估计。这个更新过程是通过松弛操作实现的，即检查是否可以通过当前节点来优化到达其邻接节点的路径。
  时间复杂度：使用优先队列实现的Dijkstra算法的时间复杂度是 O((V+E)logV)，其中 V
  是顶点数，E 是边数。

  注意事项
  重复元素的处理：如果顶点 v
  的最短路径被更新，新的值会被推入堆中，而堆中可能已经存在该顶点的一个或多个旧记录。这种情况下，堆中可能会有多个关于同一顶点的条目。
  这不会影响算法找到正确的最短路径，但会影响效率，因为同一个顶点可能被处理多次。

  为了处理这个效率问题，有几种策略可以考虑：

  1.
  忽略已经"完成"的顶点：在从优先队列中取出元素时，检查其是否已经被标记为完成（即
  finalized[v] ==
  true）。如果是，则忽略它，这样即使队列中有重复的顶点条目，也不会重复处理它们。
  2. 使用更高级的数据结构：使用如斐波那契堆等支持减小键值（Decrease
  Key）操作的数据结构，可以在更新距离时直接减少顶点键值，而无需重新插入新的条目。
*/

// 定义边的结构
struct Edge {
  int to;
  int weight;
};

// 定义图
struct Graph {
  int V;                    // 顶点数
  vector<vector<Edge>> adj; // 邻接表
};

// 定义比较器，用于优先队列
class Compare {
public:
  bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
    return a.second > b.second; // 优先队列，小顶堆
  }
};

// Dijkstra 算法实现
void dijkstra(Graph &graph, int src) {
  int V = graph.V;
  vector<int> dist(V, INT_MAX);     // 存储到每个顶点的最短距离
  vector<bool> finalized(V, false); // 标记顶点最短距离是否已确定

  // 优先队列，存储顶点和到该顶点的距离
  priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;

  // 从源点开始
  dist[src] = 0;
  pq.push({src, 0});

  while (!pq.empty()) {
    // 取出当前队列中距离最小的顶点
    int u = pq.top().first;
    pq.pop();

    if (finalized[u])
      continue; // 如果已经处理过，跳过

    // 标记此顶点的最短路径已确定
    finalized[u] = true;

    // 遍历所有邻接顶点
    for (auto &e : graph.adj[u]) {
      int v = e.to;
      int weight = e.weight;

      // 如果找到更短的路径，则更新
      if (!finalized[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        // 如果一个顶点的最短路径估计被更新，新的顶点-距离对将被添加到优先队列中，即使这个顶点已经在队列中。这可能导致队列中有多个相同的顶点但距离不同。
        // 可以通过检查队列中是否已存在顶点来避免这种重复添加，或者在顶点被取出时才更新距离。
        pq.push({v, dist[v]});
      }
    }
  }

  // 打印最短路径结果
  cout << "Vertex Distance from Source" << endl;
  for (int i = 0; i < V; ++i) {
    cout << i << " \t\t " << dist[i] << endl;
  }
}

int main() {
  Graph g{5};
  g.adj = {{{1, 10}, {3, 5}}, // 邻接表表示
           {{2, 1}, {3, 2}},
           {{4, 4}},
           {{1, 3}, {2, 9}, {4, 2}},
           {{0, 7}, {2, 6}}};

  dijkstra(g, 0); // 从顶点0开始

  return 0;
}
