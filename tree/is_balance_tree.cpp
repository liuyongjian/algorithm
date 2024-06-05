#include <algorithm>
#include <cstdlib>
#include <iostream>

// 使用命名空间std中的特定成员
using std::abs;
using std::cout;
using std::endl;
using std::max;

// 判断平衡二叉树
// 关键点：设计一个递归函数，该函数返回两个信息：一是树的高度，二是该树是否平衡。
// 递归地检查每个节点的平衡性和高度。如果任何子树的高度差超过1，或者任何子树本身不平衡，它返回-1。否则，它返回该节点为根的子树的高度

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

struct TreeInfo {
  int height;
  bool isBalanced;

  TreeInfo(int h, bool b) : height(h), isBalanced(b) {}
};

// 辅助函数：判断二叉树是否平衡并返回树的信息
TreeInfo checkBalance(TreeNode *node) {
  if (node == nullptr) {
    return TreeInfo(0, true); // 空树高度为0，且平衡
  }

  TreeInfo leftInfo = checkBalance(node->left);
  if (!leftInfo.isBalanced)
    return TreeInfo(-1, false); // 如果左子树不平衡，立即返回

  TreeInfo rightInfo = checkBalance(node->right);
  if (!rightInfo.isBalanced)
    return TreeInfo(-1, false); // 如果右子树不平衡，立即返回

  if (abs(leftInfo.height - rightInfo.height) > 1) {
    return TreeInfo(-1, false); // 左右子树高度差大于1，不平衡
  }

  // 返回当前节点的高度和平衡状态
  return TreeInfo(max(leftInfo.height, rightInfo.height) + 1, true);
}

// 公开函数：检查树是否平衡
bool isBalanced(TreeNode *root) { return checkBalance(root).isBalanced; }

int main() {
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->left->left = new TreeNode(4);
  root->left->right = new TreeNode(5);
  root->right->right = new TreeNode(6);
  root->left->left->left = new TreeNode(7);

  cout << "该树" << (isBalanced(root) ? "" : "不") << "平衡。" << endl;

  return 0;
}
