#include <iostream>
#include <limits>

// 使用命名空间中的特定成员
using std::cout;
using std::endl;
using std::numeric_limits;

// 关键点：对于每个节点，我们需要保证它的值在一个特定的范围内（由其父节点的值界定）。
// 左子节点的值必须小于其父节点的值，而右子节点的值必须大于其父节点的值。
// 通过递归传递最大和最小值限制，我们可以确保整棵树符合BST的定义

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {} // 构造函数
};

// 辅助函数，用于递归检查二叉树是否为BST
bool isValidBSTHelper(TreeNode *node, long long lower, long long upper) {
  if (!node)
    return true; // 如果节点为空，返回true

  int val = node->val;
  // 检查当前节点值是否在允许的范围内
  if (val <= lower || val >= upper)
    return false;

  // 递归检查右子树，并更新下界
  if (!isValidBSTHelper(node->right, val, upper))
    return false;
  // 递归检查左子树，并更新上界
  if (!isValidBSTHelper(node->left, lower, val))
    return false;

  return true;
}

bool isValidBST(TreeNode *root) {
  return isValidBSTHelper(root, numeric_limits<long long>::min(),
                          numeric_limits<long long>::max());
}

int main() {
  // 创建一个示例二叉树: [2, 1, 3]
  TreeNode *root = new TreeNode(2);
  root->left = new TreeNode(1);
  root->right = new TreeNode(3);

  if (isValidBST(root)) {
    cout << "The tree is a BST." << endl;
  } else {
    cout << "The tree is not a BST." << endl;
  }

  return 0;
}
