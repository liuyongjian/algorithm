#include <iostream>
#include <queue>

using std::cout;
using std::endl;
using std::queue;

// 树的按层遍历（也称为广度优先搜索，BFS）
// 关键点: 使用队列辅助实现

struct TreeNode {
  int value;
  TreeNode *left;
  TreeNode *right;

  TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// 按层遍历函数
void levelOrderTraversal(TreeNode *root) {
  if (root == nullptr)
    return;

  queue<TreeNode *>
      q; // 注意这里如果使用是queue<TreeNode> 来存储树的节点
         // 每当你将一个节点加入队列时，实际上是创建了该节点的一个副本。这意味着队列中存储的是原始树节点的副本，而不是原始节点本身。
  q.push(root);

  while (!q.empty()) {
    TreeNode *current = q.front();
    q.pop();

    // 访问当前节点
    cout << current->value << " ";

    // 如果当前节点存在子节点，将所有子节点加入队列
    if (current->left != nullptr) {
      q.push(current->left);
    }
    if (current->right != nullptr) {
      q.push(current->right);
    }
  }
}

int main() {
  // 创建树的节点
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->left->left = new TreeNode(4);
  root->left->right = new TreeNode(5);
  root->right->left = new TreeNode(6);
  root->right->right = new TreeNode(7);

  // 按层遍历
  cout << "Level order traversal of the tree:" << endl;
  levelOrderTraversal(root);

  return 0;
}
