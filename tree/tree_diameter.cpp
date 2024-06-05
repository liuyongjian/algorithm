#include <algorithm>
#include <iostream>

using std::cout;
using std::endl;
using std::max;

// 关键点：在递归过程中同时处理计算节点深度和更新最大直径两个任务。使用的是多任务递归策略

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

struct TreeInfo {
  int diameter;
  int height;
};

// 辅助函数，用于递归计算树的深度和直径
TreeInfo calculateTreeInfo(TreeNode *node) {
  if (!node)
    return {0, 0}; // 空树没有直径，也没有高度

  // 递归计算左右子树的信息
  TreeInfo leftInfo = calculateTreeInfo(node->left);
  TreeInfo rightInfo = calculateTreeInfo(node->right);

  // 当前节点的最大直径可能是左子树、右子树的直径，或者穿过当前节点的左右子树的路径长度
  int currentDiameter = max(leftInfo.height + rightInfo.height,
                            max(leftInfo.diameter, rightInfo.diameter));

  // 当前节点的高度是左子树或右子树高度的最大值加1
  int currentHeight = max(leftInfo.height, rightInfo.height) + 1;

  return {currentDiameter, currentHeight};
}

// 计算二叉树的直径
int treeDiameter(TreeNode *root) {
  TreeInfo treeInfo = calculateTreeInfo(root);
  return treeInfo.diameter;
}

void deleteTree(TreeNode *node) {
  if (node == nullptr)
    return;
  deleteTree(node->left);
  deleteTree(node->right);
  delete node;
}

int main() {
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->left->left = new TreeNode(4);
  root->left->right = new TreeNode(5);

  cout << "二叉树的最大距离（直径）是: " << treeDiameter(root) << endl;

  deleteTree(root);
  return 0;
}
