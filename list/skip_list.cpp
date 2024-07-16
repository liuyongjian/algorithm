#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>

using namespace std;

class Node {
public:
  int value;
  // 指针数组，用于指向同一层的下一个节点和更高层的节点
  Node **forward;

  Node(int level, int value) {
    // 根据层级分配指针数组空间
    forward = new Node *[level + 1];
    // 参数 0 相当于将内存区域中的内容设置为
    // nullptr（在大多数现代系统上，空指针在内部表示为全0） 确保所有新节点的
    // forward 指针在使用前被设为 nullptr
    memset(forward, 0, sizeof(Node *) * (level + 1));

    this->value = value;
  }

  ~Node() { delete[] forward; }
};

class SkipList {
private:
  // 跳表中的最大层数
  int maxLevel;
  // 节点晋升到更高层的概率（默认为0.5）
  float probability;
  // 当前跳表使用的最高层级
  int currentLevel;
  // 哨兵节点，位于所有层的最前面，其值为整数的最小值
  Node *header;

  // 生成一个随机层级数，用于新插入节点的层级晋升。这个过程基于概率计算，保证了跳表的平衡性。
  int randomLevel() const {
    int level = 0;
    while ((rand() % 100) < (probability * 100)) {
      level++;
      if (level == maxLevel)
        break;
    }
    return level;
  }

public:
  SkipList(int maxLevel, float probability = 0.5)
      : maxLevel(maxLevel), probability(probability), currentLevel(0) {
    int min = numeric_limits<int>::min();

    // 创建头节点，值为最小整数
    header = new Node(maxLevel, min);
  }

  ~SkipList() {
    Node *current = header;

    while (current != nullptr) {
      // 访问下一个基础层节点
      Node *next = current->forward[0];

      delete current;

      current = next;
    }
  }

  void insert(int value) {
    // update
    // 数组用于记录每个层级上最后一个搜索位置（即在此之后需要插入新节点或删除一个节点的位置）
    Node **update = new Node *[maxLevel + 1];
    memset(update, 0, sizeof(Node *) * (maxLevel + 1));

    Node *current = header;

    // 从最高层向下查找每层比value小的最右的节点，更新update，继续下一层的查找
    for (int i = currentLevel; i >= 0; --i) {
      while (current->forward[i] != nullptr &&
             current->forward[i]->value < value) {
        current = current->forward[i];
      }

      // 标记需要更新的点，确定新值应当插入的每一层的位置
      update[i] = current;
    }

    // update 数组中记录了新节点在每层应插入的位置的前一个节点。
    // 新节点需要插入到基础层（即第0层），无论新节点是否会晋升到更高的层级。
    current = current->forward[0];

    int level = randomLevel();

    // 如果新节点层数高于当前层数，更新头节点的层
    if (level > currentLevel) {
      for (int i = currentLevel + 1; i <= level; ++i) {
        // 对于新节点的每一层，从 currentLevel + 1 到 level，将 update
        // 数组的这些层设置为头节点
        // 在每个层级中，头节点作为该层链表的起点。对于新增的层级，头节点是唯一存在的节点，直到新节点被插入。
        update[i] = header;
      }
      currentLevel = level;
    }

    Node *newNode = new Node(level, value);

    // 插入新节点到适当层
    for (int i = 0; i <= level; ++i) {
      newNode->forward[i] = update[i]->forward[i];
      update[i]->forward[i] = newNode;
    }

    // 清理临时数组
    delete[] update;
  }

  // 显示跳表的所有层
  void display() const {
    for (int i = 0; i <= currentLevel; ++i) {
      Node *node = header->forward[i];

      cout << "Level " << i << ": ";
      while (node != nullptr) {
        cout << node->value << " ";
        node = node->forward[i];
      }
      cout << endl;
    }
  }

  bool search(int value) {
    Node *current = header;

    // 从最高层向下搜索
    for (int i = currentLevel; i >= 0; --i) {
      while (current->forward[i] != nullptr &&
             current->forward[i]->value < value) {
        current = current->forward[i];
      }
    }

    // 移动到可能存在值的节点
    current = current->forward[0];

    // 检查值是否匹配
    return current != nullptr && current->value == value;
  }

  void remove(int value) {
    Node **update = new Node *[maxLevel + 1];
    Node *current = header;

    // 查找需要更新的点
    for (int i = currentLevel; i >= 0; --i) {
      while (current->forward[i] != nullptr &&
             current->forward[i]->value < value) {
        current = current->forward[i];
      }
      update[i] = current;
    }

    // 移动到待删除节点
    current = current->forward[0];

    // 如果找到，执行删除
    if (current->value == value) {
      for (int i = 0; i <= currentLevel; ++i) {
        // 检查 update[i] 的下一个节点是否是要删除的节点 current
        // 如果不是，这表示在这一层，current
        // 节点之前已经被修改或不需要进一步操作，因此可以中断循环。
        if (update[i]->forward[i] != current)
          break;

        // 将第 i 层中 current 前一个节点的 forward 指针更新为 current
        // 节点的下一个节点。 这实际上是在移除 current 节点，通过跳过 current
        // 并直接链接到其后继节点来更新链表。
        update[i]->forward[i] = current->forward[i];
      }

      delete current;

      // 当判断出某一层没有元素时（即该层的头节点指向 nullptr），循环减少
      // currentLevel 的值，这样做的目的是将跳表的高度降低到实际包含节点的最高层
      while (currentLevel > 0 && header->forward[currentLevel] == nullptr) {
        --currentLevel;
      }
    }

    delete[] update;
  }
};

int main() {
  SkipList list(5);
  list.insert(3);
  list.insert(6);
  list.insert(7);
  list.insert(9);
  list.insert(12);
  list.insert(19);
  list.insert(17);

  list.display();
  if (list.search(6)) {
    cout << "Found 6" << endl;
  } else {
    cout << "6 not found" << endl;
  }

  list.remove(6);
  list.display();

  return 0;
}
