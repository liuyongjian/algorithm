#include <cstdlib>
#include <ctime>
#include <iostream>
#include <queue>
#include <vector>

using std::cout;
using std::endl;
using std::queue;
using std::vector;

// 判断完全二叉树（Complete Binary Tree）
// 关键点：利用队列来进行遍历并检查节点的顺序和完整性，代码逐层检查每个节点，并在遇到第一个空节点后标记end。如果在标记之后仍然发现有非空节点，那么该树就不是完全二叉树。

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 判断完全二叉树的主函数
bool isCompleteTree(TreeNode *root) {
  if (!root)
    return true;

  queue<TreeNode *> q;
  q.push(root);
  bool end = false; // 标记是否遇到了第一个空子节点

  while (!q.empty()) {
    TreeNode *node = q.front();
    q.pop();

    if (!node) {
      end = true;
    } else {
      if (end)
        return false; // 如果已经遇到空节点，再遇到非空节点则不是完全二叉树
      q.push(node->left);
      q.push(node->right);
    }
  }
  return true;
}

// 使用节点编号策略的基准检查方法
// 利用二叉树中节点的位置编号来判断该树是否为完全二叉树的一种方法。
// 这种方法基于完全二叉树的一个特性：在使用顺序存储（如数组）表示时，如果一个二叉树是完全二叉树，那么所有的节点在数组中的位置应连续无缺。
// 实际上是通过另一种方式实现这个思想：它把所有节点（包括空节点）都按层序遍历的顺序添加到一个列表中，然后检查列表中第一个空节点之后是否还有非空节点。
// 如果有，则不是完全二叉树。这种方法也隐式地使用了节点编号策略，因为如果树是完全的，所有非空节点的遍历和存储应该直接在空节点之前连续出现。
bool isCompleteTreeReference(TreeNode *root) {
  if (!root)
    return true;

  vector<TreeNode *> nodes;
  nodes.push_back(root);
  size_t i = 0;

  while (i < nodes.size() && nodes[i]) {
    nodes.push_back(nodes[i]->left);
    nodes.push_back(nodes[i]->right);
    i++;
  }

  // 检查是否有非空节点出现在空节点之后
  while (i < nodes.size()) {
    if (nodes[i])
      return false;
    i++;
  }

  return true;
}

// 用于删除树的辅助函数
void deleteTree(TreeNode *node) {
  if (!node)
    return;
  deleteTree(node->left);
  deleteTree(node->right);
  delete node;
}

// 生成随机二叉树
TreeNode *generateRandomTree(int maxDepth, int currentDepth = 0) {
  if (currentDepth == maxDepth || rand() % 3 == 0) { // 随机停止树的生长
    return nullptr;
  }

  TreeNode *node = new TreeNode(rand() % 100);
  node->left = generateRandomTree(maxDepth, currentDepth + 1);
  node->right = generateRandomTree(maxDepth, currentDepth + 1);
  return node;
}

int main() {
  srand(time(nullptr)); // 初始化随机数生成器

  bool all_tests_passed = true;

  // 使用多棵树测试函数
  for (int i = 0; i < 100; ++i) {
    TreeNode *root = generateRandomTree(5); // 生成最大深度为5的随机树

    bool result = isCompleteTree(root);
    bool referenceResult = isCompleteTreeReference(root);

    if (result != referenceResult) {
      cout << "Test " << i + 1 << ": Mismatch found - isCompleteTree says "
           << (result ? "complete" : "not complete") << ", reference says "
           << (referenceResult ? "complete" : "not complete") << endl;
      all_tests_passed = false;
    }

    deleteTree(root); // 清理内存
  }

  if (all_tests_passed) {
    cout << "All tests passed!" << endl;
  } else {
    cout << "Some tests failed." << endl;
  }

  return 0;
}
