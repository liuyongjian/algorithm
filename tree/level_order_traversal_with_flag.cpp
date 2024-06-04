#include <iostream>
#include <queue>

// 在树的按层遍历（广度优先搜索）中，有时我们需要明确知道每一层的结束，这样可以让我们更好地处理和理解树的层级结构。
// 例如，在可视化树结构、树结构的序列化和反序列化或者在算法中需要根据层级做特定处理的场景中，了解每层的界限是非常有用的。

using std::cout;
using std::endl;
using std::queue;

struct TreeNode {
  int value;
  TreeNode *left;
  TreeNode *right;

  TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

void levelOrderTraversal(TreeNode *root) {
  if (root == nullptr)
    return;

  queue<TreeNode *> q;
  q.push(root);

  while (!q.empty()) {
    int levelSize = q.size(); // 当前层的节点数

    for (int i = 0; i < levelSize; ++i) {
      TreeNode *current = q.front();
      q.pop();

      // 访问当前节点
      cout << current->value << " ";

      // 将当前节点的子节点加入队列
      if (current->left != nullptr) {
        q.push(current->left);
      }
      if (current->right != nullptr) {
        q.push(current->right);
      }
    }

    // 这里表示一层的结束
    cout << endl; // 打印换行符来分隔各层
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
