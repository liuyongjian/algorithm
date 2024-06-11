#include <iostream>
#include <list>
#include <memory>
#include <tuple>
#include <vector>

using std::list;
using std::make_shared;
using std::make_unique;
using std::shared_ptr;
using std::tuple;
using std::unique_ptr;
using std::vector;

class Edge; // 前置声明

class Vertex {
public:
  int id;        // 顶点的唯一标识符
  int value;     // 顶点的数据值
  int indegree;  // 入度
  int outdegree; // 出度
  list<shared_ptr<Edge>>
      edges; // 存储从该顶点出发的所有边，使用shared_ptr自动管理边的生命周期

  Vertex(int id, int value = 0)
      : id(id), value(value), indegree(0), outdegree(0) {}

  // 将函数实现与类定义分离可以提高代码的可读性和可维护性。Vertex类定义提供了一个接口，而实现细节则被放置在外部
  // 同时解决循环引用的问题
  void addEdge(shared_ptr<class Edge> edge);
  vector<Vertex *> getNeighbors() const;
};

class Edge {
public:
  Vertex *start; // 边的起始顶点
  Vertex *end;   // 边的终点顶点
  int weight;    // 边的权重

  Edge(Vertex *start, Vertex *end, int weight = 1)
      : start(start), end(end), weight(weight) {}
};

void Vertex::addEdge(shared_ptr<Edge> edge) {
  edges.push_back(
      edge); // 将边加入顶点的边列表中，shared_ptr确保多个顶点可以共享同一边的所有权
  outdegree++;
  edge->end->indegree++;
}

vector<Vertex *> Vertex::getNeighbors() const {
  vector<Vertex *> neighbors;
  for (auto &edge : edges) {
    neighbors.push_back(edge->end);
  }
  return neighbors;
}

class Graph {
public:
  vector<unique_ptr<Vertex>>
      vertices; // 存储所有顶点。使用unique_ptr确保顶点的自动销毁和图的独占所有权
  bool directed; // 指示图是否为有向图

  Graph(bool directed = true) : directed(directed) {}

  Vertex *addVertex(int id, int value = 0) {
    vertices.emplace_back(make_unique<Vertex>(
        id, value)); // 使用make_unique来安全创建并管理Vertex对象
    return vertices.back().get();
  }

  void addEdge(Vertex *start, Vertex *end, int weight = 1) {
    shared_ptr<Edge> edge = make_shared<Edge>(
        start, end, weight); // 使用make_shared来安全创建并管理Edge对象
    start->addEdge(edge);
    if (!directed) {
      shared_ptr<Edge> reverseEdge = make_shared<Edge>(end, start, weight);
      end->addEdge(reverseEdge);
    }
  }
};

class GraphConverter {
public:
  // 从邻接矩阵转换
  static Graph fromAdjacencyMatrix(const vector<vector<int>> &matrix,
                                   bool directed = true) {
    Graph graph(directed);
    for (size_t i = 0; i < matrix.size(); ++i) {
      graph.addVertex(i);
    }
    for (size_t i = 0; i < matrix.size(); ++i) {
      for (size_t j = 0; j < matrix[i].size(); ++j) {
        if (matrix[i][j] != 0) {
          graph.addEdge(graph.vertices[i].get(), graph.vertices[j].get(),
                        matrix[i][j]);
        }
      }
    }
    return graph;
  }

  // 从邻接列表转换
  static Graph fromAdjacencyList(const vector<vector<int>> &adjList,
                                 bool directed = true) {
    Graph graph(directed);
    for (size_t i = 0; i < adjList.size(); ++i) {
      graph.addVertex(i);
    }
    for (size_t i = 0; i < adjList.size(); ++i) {
      for (int j : adjList[i]) {
        graph.addEdge(graph.vertices[i].get(), graph.vertices[j].get(),
                      1); // 默认权重为 1
      }
    }
    return graph;
  }

  // 从边列表转换
  static Graph fromEdgeList(const vector<tuple<int, int, int>> &edges,
                            bool directed = true) {
    Graph graph(directed);
    for (const auto &[from, to, weight] : edges) {
      Vertex *start = graph.addVertex(from);
      Vertex *end = graph.addVertex(to);
      graph.addEdge(start, end, weight);
    }
    return graph;
  }
};

int main() {
  // Graph g(true); // 创建一个有向图

  // Vertex *v1 = g.addVertex(1, 10);
  // Vertex *v2 = g.addVertex(2, 20);
  // Vertex *v3 = g.addVertex(3, 30);

  // g.addEdge(v1, v2, 5);
  // g.addEdge(v1, v3, 15);
  // g.addEdge(v2, v3, 7);

  // for (const auto &v : g.vertices) {
  //   std::cout << "Vertex " << v->id << " has value " << v->value
  //             << " and neighbors: ";
  //   auto neighbors = v->getNeighbors();
  //   for (const Vertex *neighbor : neighbors) {
  //     std::cout << neighbor->id << " ";
  //   }
  //   std::cout << std::endl;
  // }

  // 邻接矩阵转标准图结构
  vector<vector<int>> adjMatrix = {
      {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}, {0, 0, 0, 0}};
  Graph graph = GraphConverter::fromAdjacencyMatrix(adjMatrix);
  for (const auto &v : graph.vertices) {
    std::cout << "Vertex " << v->id << " has value " << v->value
              << " and neighbors: ";
    auto neighbors = v->getNeighbors();
    for (const Vertex *neighbor : neighbors) {
      std::cout << neighbor->id << " ";
    }
    std::cout << std::endl;
  }

  // 邻接列表转换
  // vector<vector<int>> adjList = {
  //     {1, 2}, // 顶点0连接到顶点1和顶点2
  //     {2},    // 顶点1连接到顶点2
  //     {3},    // 顶点2连接到顶点3
  //     {}      // 顶点3没有连接
  // };

  // Graph graphFromAdjList = GraphConverter::fromAdjacencyList(adjList, true);

  // std::cout << "Graph from Adjacency List:" << std::endl;
  // for (const auto &vertex : graphFromAdjList.vertices) {
  //   std::cout << "Vertex " << vertex->id << " has neighbors: ";
  //   auto neighbors = vertex->getNeighbors();
  //   for (const Vertex *neighbor : neighbors) {
  //     std::cout << neighbor->id << " ";
  //   }
  //   std::cout << std::endl;
  // }

  // 边列表转换
  // vector<tuple<int, int, int>> edgeList = {
  //     {0, 1, 10}, // 从顶点0到顶点1，权重10
  //     {0, 2, 15}, // 从顶点0到顶点2，权重15
  //     {1, 2, 5},  // 从顶点1到顶点2，权重5
  //     {2, 3, 7}   // 从顶点2到顶点3，权重7
  // };

  // Graph graphFromEdgeList = GraphConverter::fromEdgeList(edgeList, true);

  // std::cout << "Graph from Edge List:" << std::endl;
  // for (const auto &vertex : graphFromEdgeList.vertices) {
  //   std::cout << "Vertex " << vertex->id << " has neighbors: ";
  //   auto neighbors = vertex->getNeighbors();
  //   for (const Vertex *neighbor : neighbors) {
  //     std::cout << neighbor->id << " ";
  //   }
  //   std::cout << std::endl;
  // }

  return 0;
}
