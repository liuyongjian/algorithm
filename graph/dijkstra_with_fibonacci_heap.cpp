#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

// 使用标准库的部分组件
using std::cout;
using std::endl;
using std::invalid_argument;
using std::pair;
using std::swap;
using std::vector;

class FibonacciHeap {
public:
  struct Node {
    int key;      // 键值
    int degree;   // 节点的度数
    bool mark;    // 标记节点是否丢失过孩子
    Node *parent; // 父节点
    Node *child;  // 孩子节点
    Node *left;   // 左兄弟节点
    Node *right;  // 右兄弟节点
    int vertex;   // 顶点编号，用于图算法中

    Node(int keyValue, int vertexNumber)
        : key(keyValue), degree(0), mark(false), parent(nullptr),
          child(nullptr), left(this), right(this), vertex(vertexNumber) {}
  };

  FibonacciHeap() : minNode(nullptr), nodeCount(0) {}

  // 插入新节点
  Node *insert(int key, int vertex) {
    Node *newNode = new Node(key, vertex);
    if (minNode == nullptr) {
      minNode = newNode;
      newNode->left = newNode->right = newNode;
    } else {
      addToRootList(newNode);
      if (newNode->key < minNode->key) {
        minNode = newNode;
      }
    }
    nodeCount++;
    return newNode;
  }

  // 检查堆是否为空
  bool isEmpty() const { return minNode == nullptr; }

  // 提取最小元素
  int extractMin() {
    Node *oldMin = minNode;
    if (oldMin != nullptr) {
      if (oldMin->child != nullptr) {
        Node *currentChild = oldMin->child;
        do {
          Node *nextChild = currentChild->right;
          addToRootList(currentChild);
          currentChild->parent = nullptr;
          currentChild = nextChild;
        } while (currentChild != oldMin->child);
      }
      removeFromRootList(oldMin);
      if (oldMin == oldMin->right) {
        minNode = nullptr;
      } else {
        minNode = oldMin->right;
        consolidate();
      }
      nodeCount--;
      int minVertex = oldMin->vertex;
      delete oldMin;
      return minVertex;
    }
    return -1; // 表示堆为空
  }

  // 键值减小操作
  void decreaseKey(Node *node, int newKey) {
    if (newKey > node->key) {
      throw invalid_argument("新键值必须小于当前键值。");
    }
    node->key = newKey;
    Node *parentNode = node->parent;
    if (parentNode != nullptr && node->key < parentNode->key) {
      cut(node, parentNode);
      cascadingCut(parentNode);
    }
    if (node->key < minNode->key) {
      minNode = node;
    }
  }

private:
  Node *minNode; // 指向最小节点
  int nodeCount; // 节点计数

  // 将节点添加到根列表
  void addToRootList(Node *node) {
    node->left = minNode;
    node->right = minNode->right;
    minNode->right->left = node;
    minNode->right = node;
  }

  // 从根列表中移除节点
  void removeFromRootList(Node *node) {
    node->left->right = node->right;
    node->right->left = node->left;
    if (node == minNode) {
      minNode = node->right;
    }
  }

  // 合并操作，优化堆结构
  void consolidate() {
    int maxDegree = static_cast<int>(std::log2(nodeCount)) + 1;
    vector<Node *> degreeTable(maxDegree, nullptr);
    vector<Node *> rootList;
    Node *current = minNode;
    do {
      rootList.push_back(current);
      current = current->right;
    } while (current != minNode);

    for (Node *w : rootList) {
      Node *currentNode = w;
      int d = currentNode->degree;
      while (degreeTable[d] != nullptr) {
        Node *conflictNode = degreeTable[d];
        if (currentNode->key > conflictNode->key) {
          swap(currentNode, conflictNode);
        }
        link(conflictNode, currentNode);
        degreeTable[d] = nullptr;
        d++;
      }
      degreeTable[d] = currentNode;
    }

    minNode = nullptr;
    for (Node *node : degreeTable) {
      if (node != nullptr) {
        if (minNode == nullptr) {
          minNode = node;
          node->left = node->right = node;
        } else {
          addToRootList(node);
          if (node->key < minNode->key) {
            minNode = node;
          }
        }
      }
    }
  }

  // 链接两个节点
  void link(Node *y, Node *x) {
    removeFromRootList(y);
    y->left = y->right = y;
    if (x->child == nullptr) {
      x->child = y;
    } else {
      y->left = x->child;
      y->right = x->child->right;
      x->child->right->left = y;
      x->child->right = y;
    }
    y->parent = x;
    x->degree++;
    y->mark = false;
  }

  // 剪切节点
  void cut(Node *x, Node *y) {
    x->left->right = x->right;
    x->right->left = x->left;
    if (y->child == x) {
      y->child = x->right;
    }
    y->degree--;
    addToRootList(x);
    x->parent = nullptr;
    x->mark = false;
  }

  // 级联剪切操作
  void cascadingCut(Node *y) {
    Node *z = y->parent;
    if (z != nullptr) {
      if (!y->mark) {
        y->mark = true;
      } else {
        cut(y, z);
        cascadingCut(z);
      }
    }
  }
};

void dijkstra(vector<vector<pair<int, int>>> &graph, int src) {
  int V = graph.size();
  vector<int> dist(V, INT_MAX);
  vector<FibonacciHeap::Node *> nodes(V, nullptr);
  FibonacciHeap pq;

  dist[src] = 0;
  nodes[src] = pq.insert(0, src);

  while (!pq.isEmpty()) {
    int u = pq.extractMin();

    for (const auto &neighbor : graph[u]) {
      int v = neighbor.first;
      int weight = neighbor.second;

      if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        if (nodes[v] == nullptr) {
          nodes[v] = pq.insert(dist[v], v);
        } else {
          pq.decreaseKey(nodes[v], dist[v]);
        }
      }
    }
  }

  // Print shortest distances
  for (int i = 0; i < V; ++i) {
    cout << "Vertex: " << i << " Distance from source " << src << ": "
         << dist[i] << endl;
  }
}

int main() {
  int V = 9;
  vector<vector<pair<int, int>>> graph(V);

  graph[0].push_back({1, 4});
  graph[0].push_back({7, 8});
  graph[1].push_back({0, 4});
  graph[1].push_back({2, 8});
  graph[1].push_back({7, 11});
  graph[2].push_back({1, 8});
  graph[2].push_back({3, 7});
  graph[2].push_back({5, 4});
  graph[2].push_back({8, 2});
  graph[3].push_back({2, 7});
  graph[3].push_back({4, 9});
  graph[3].push_back({5, 14});
  graph[4].push_back({3, 9});
  graph[4].push_back({5, 10});
  graph[5].push_back({2, 4});
  graph[5].push_back({3, 14});
  graph[5].push_back({4, 10});
  graph[5].push_back({6, 2});
  graph[6].push_back({5, 2});
  graph[6].push_back({7, 1});
  graph[6].push_back({8, 6});
  graph[7].push_back({0, 8});
  graph[7].push_back({1, 11});
  graph[7].push_back({6, 1});
  graph[7].push_back({8, 7});
  graph[8].push_back({2, 2});
  graph[8].push_back({6, 6});
  graph[8].push_back({7, 7});

  dijkstra(graph, 1);

  return 0;
}
