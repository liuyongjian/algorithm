#include <iostream>
#include <queue>
#include <vector>

using std::cout;
using std::endl;
using std::queue;
using std::vector;

/*
  图的拓扑排序算法：

  在图中找到所有入度为0的点输出。
  把所有入度为0的点在图中删除，继续找入度为0的点输出，周而复始。
  图的所有点都被删除后，依次输出的顺序就是拓扑排序。
  要求：有向图且其中没有环。

  拓扑排序是对有向无环图（DAG）的顶点进行排序的一种方法，使得对于任何从顶点 u
  到顶点 v 的有向边，u 在排序中都出现在 v 之前。
  通常，这种排序用于解决数据依赖问题，如任务调度、课程规划等。

  关键点:
  使用队列处理入度为0的顶点。从队列中逐个取出顶点，将这些顶点添加到拓扑排序的结果中，并更新其相邻顶点的入度（即移除从当前顶点发出的边）。
  每当相邻顶点的入度变为0时，就将这个顶点加入队列。

  结果的不唯一性：Kahn 的算法不总是产生唯一的拓扑排序结果。
*/

// 函数用于添加边到图中
void addEdge(vector<int> adj[], int src, int dest) { adj[src].push_back(dest); }

// 使用了基于 Kahn's
// 算法的拓扑排序方法，该方法使用一个队列来存储所有入度为0的顶点，并逐一处理这些顶点。
void topologicalSort(vector<int> adj[], int V) {
  // 创建一个数组来存储所有顶点的入度
  vector<int> in_degree(V, 0);

  // 计算每个顶点的入度
  for (int u = 0; u < V; u++) {
    for (int v : adj[u]) {
      in_degree[v]++;
    }
  }

  // 创建一个队列并将所有入度为0的顶点加入队列
  queue<int> q;
  for (int i = 0; i < V; i++) {
    if (in_degree[i] == 0) {
      q.push(i);
    }
  }

  // 用于存储拓扑排序的结果
  vector<int> top_order;

  // 开始执行拓扑排序
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    top_order.push_back(u);

    // 遍历每个顶点的邻接点，并减少其入度
    for (int v : adj[u]) {
      if (--in_degree[v] == 0) {
        q.push(v);
      }
    }
  }

  // 检查是否有环
  if (top_order.size() != static_cast<size_t>(V)) {
    cout << "There is a cycle in the graph." << endl;
    return;
  }

  // 打印拓扑排序的结果
  for (int i : top_order) {
    cout << i << " ";
  }
  cout << endl;
}

int main() {
  int V = 6;          // 顶点数
  vector<int> adj[V]; // 邻接表

  // 添加边
  addEdge(adj, 5, 2);
  addEdge(adj, 5, 0);
  addEdge(adj, 4, 0);
  addEdge(adj, 4, 1);
  addEdge(adj, 2, 3);
  addEdge(adj, 3, 1);

  cout << "Topological sort of the given graph:\n";
  topologicalSort(adj, V);

  return 0;
}
