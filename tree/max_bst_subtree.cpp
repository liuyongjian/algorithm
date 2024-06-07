#include <climits> // 为了使用 INT_MIN 和 INT_MAX
#include <iostream>

using std::cout;
using std::endl;
using std::max;
using std::min;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

struct TreeInfo {
  bool isBST; // 判断这个节点所在子树是否是BST
  int size;   // 子树的节点数
  int min;    // 子树中的最小值
  int max;    // 子树中的最大值
};

// 功能：计算二叉树中最大的BST子树的大小
TreeInfo maxBSTSubtree(TreeNode *node, int &maxSize) {
  // 基本情况
  if (node == nullptr) {
    return {true, 0, INT_MAX, INT_MIN};
  }

  // 递归计算左右子树的信息
  TreeInfo leftInfo = maxBSTSubtree(node->left, maxSize);
  TreeInfo rightInfo = maxBSTSubtree(node->right, maxSize);

  // 当前节点的信息
  TreeInfo currInfo;
  if (leftInfo.isBST && rightInfo.isBST && leftInfo.max < node->val &&
      node->val < rightInfo.min) {
    currInfo.isBST = true;
    currInfo.size = leftInfo.size + rightInfo.size + 1;
    currInfo.min = min(leftInfo.min, node->val);
    currInfo.max = max(rightInfo.max, node->val);
    // 下面这种写法是不对的，临界条件如果此时节点是叶子节点，左右子树都是空，此时它的leftInfo.min的值为INT_MAX，rightInfo.max的值为INT_MIN
    // 所以需要min(leftInfo.min, node->val)和max(rightInfo.max,
    // node->val)判断一下
    // currInfo.min = leftInfo.min; currInfo.max = rightInfo.max;

    // 更新找到的最大BST的大小
    // 将 maxSize
    // 保持为独立的变量有助于明确它的作用和修改点，这样做也更符合单一职责原则
    // Info 结构体的设计目的是封装单个节点的状态，而 maxSize
    // 是一个跨多个节点的全局状态
    maxSize = max(maxSize, currInfo.size);
  } else {
    currInfo.isBST = false;
    currInfo.size = 0; // 这颗子树不是BST
  }

  return currInfo;
}

// 返回树中最大BST的大小
int largestBSTSubtree(TreeNode *root) {
  int maxSize = 0;
  maxBSTSubtree(root, maxSize);
  return maxSize;
}

int main() {
  TreeNode *root = new TreeNode(10);
  root->left = new TreeNode(5);
  root->right = new TreeNode(15);
  root->left->left = new TreeNode(1);
  root->left->right = new TreeNode(8);
  root->right->right = new TreeNode(7);

  cout << "最大BST的大小是: " << largestBSTSubtree(root) << endl;

  return 0;
}
