#include <iostream>
#include <queue>
#include <vector>

using std::cout;
using std::endl;
using std::queue;
using std::vector;

// 关键点：
// 1. 使用队列来存储每一层遍历过程中的顶点。当前顶点出队时，其相邻顶点入队。
// 2.
// 标记访问：为防止重复访问，需要一个数组或哈希表来标记已访问的顶点。每访问一个顶点时，应标记为已访问。

void bfs(int start, vector<vector<int>> &adj) {
  vector<bool> visited(adj.size(), false);
  queue<int> q;

  visited[start] = true;
  q.push(start);

  while (!q.empty()) {
    int v = q.front();
    q.pop();
    cout << v << " ";

    for (int u : adj[v]) {
      if (!visited[u]) {
        visited[u] = true;
        q.push(u);
      }
    }
  }
}

int main() {
  vector<vector<int>> adj = {
      {1, 2},    // 邻接表表示从顶点0出发可以到达顶点1和2
      {0, 3, 4}, // 顶点1可以到达顶点0, 3, 4
      {0, 4},    // 顶点2可以到达顶点0和4
      {1},       // 顶点3可以到达顶点1
      {1, 2}     // 顶点4可以到达顶点1和2
  };

  cout << "BFS traversal starting from vertex 0:\n";
  bfs(0, adj);

  return 0;
}
