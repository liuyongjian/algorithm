#include <iostream>
#include <stack>
#include <vector>

using std::cout;
using std::endl;
using std::stack;
using std::vector;

// 关键点：
// 1.
// 递归探索：使用递归或栈来实现深入探索每一个分支，直到该路径结束，然后回溯至最近的分叉点继续探索未访问的分支。
// 2. 标记访问：和 BFS 类似，DFS 也需要标记已访问的顶点，以防止循环访问。

void dfs(int v, vector<bool> &visited, vector<vector<int>> &adj) {
  visited[v] = true;
  cout << v << " ";

  for (int u : adj[v]) {
    if (!visited[u]) {
      dfs(u, visited, adj);
    }
  }
}

// 使用栈迭代实现
void dfs_iterative(int start, vector<vector<int>> &adj) {
  vector<bool> visited(adj.size(), false);
  stack<int> st;

  st.push(start);
  while (!st.empty()) {
    int v = st.top();
    st.pop();

    if (!visited[v]) {
      visited[v] = true;
      cout << v << " ";

      // 为了按正确顺序访问，需要逆序压入栈
      for (int i = adj[v].size() - 1; i >= 0; i--) {
        int u = adj[v][i];
        if (!visited[u]) {
          st.push(u);
        }
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

  vector<bool> visited(adj.size(), false);

  cout << "DFS traversal starting from vertex 0:\n";
  dfs(0, visited, adj);

  cout << "\n";

  cout << "DFS traversal (iterative) starting from vertex 0:\n";
  dfs_iterative(0, adj);

  return 0;
}
