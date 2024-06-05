#include <cmath>
#include <iostream>

using std::cout;
using std::endl;
using std::max;
using std::pow;

// 关键点：高度为 ℎ，那么节点数应为 2的h+1次幂 -1

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

struct TreeInfo {
  int height;    // 当前节点为根的子树高度
  int nodeCount; // 子树中的节点总数
};

// 辅助函数，同时计算高度和节点数
TreeInfo computeTreeInfo(TreeNode *node) {
  if (!node) {
    return {0, 0}; // 空树高度为0，节点数为0
  }

  TreeInfo left = computeTreeInfo(node->left);
  TreeInfo right = computeTreeInfo(node->right);

  int height = max(left.height, right.height) + 1;
  int nodeCount = left.nodeCount + right.nodeCount + 1;

  return {height, nodeCount};
}

// 判断二叉树是否是满二叉树
bool isFullBinaryTree(TreeNode *root) {
  TreeInfo info = computeTreeInfo(root);
  // 使用数学公式来验证节点数是否符合满二叉树的定义
  int expectedNodeCount = pow(2, info.height) - 1;
  return info.nodeCount == expectedNodeCount;
}

// 方法2 直接递归判断
bool isFullBinaryTree2(TreeNode *node) {
  // 如果节点为空，则按照满二叉树的定义，空树也是满二叉树
  if (node == nullptr) {
    return true;
  }

  // 如果节点的左子树和右子树都为空，这也是一个满二叉树的条件
  if (node->left == nullptr && node->right == nullptr) {
    return true;
  }

  // 如果左右子节点都存在，递归检查左子树和右子树
  if (node->left != nullptr && node->right != nullptr) {
    return isFullBinaryTree(node->left) && isFullBinaryTree(node->right);
  }

  // 如果一个节点只有一个子节点，则不是满二叉树
  return false;
}

int main() {
  // 构建一个示例树
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->left->left = new TreeNode(4);
  root->left->right = new TreeNode(5);
  root->right->left = new TreeNode(6);
  root->right->right = new TreeNode(7);

  // 检查是否为满二叉树
  cout << "该树" << (isFullBinaryTree(root) ? "是" : "不是") << "满二叉树。"
       << endl;

  return 0;
}
