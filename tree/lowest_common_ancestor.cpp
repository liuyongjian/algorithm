#include <iostream>

// 使用局部std声明来简化代码
using std::cout;
using std::endl;

// 在二叉树中找到两个节点a和b的最低公共祖先（Lowest Common Ancestor, LCA）

// 定义二叉树的节点结构
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 第一种方法：基础递归
TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
  if (!root || root == p || root == q) {
    return root;
  }

  TreeNode *left = lowestCommonAncestor(root->left, p, q);
  TreeNode *right = lowestCommonAncestor(root->right, p, q);

  // 如果左右子树各有一个节点，说明当前root是它们的最低公共祖先
  if (left && right) {
    return root;
  }

  // 如果只有一个子树有节点，返回那个节点
  return left ? left : right;
}

// 第二种方法：使用多结果递归策略实现
// 通过跟踪额外的状态信息——即是否在左右子树中找到了 p 和
// q——提供了更细粒度的控制。这种方法不仅返回是否找到了LCA，还返回了是否在该子树中找到了
// p 和 q。这允许在不需要等到递归到达某个特定节点的情况下就终止递归
// 这对于大型或深度较大的树结构尤其有用，因为它减少了不必要的递归深入，从而节省了计算资源和时间。
// 相较于第一种方法，这种早期返回机制更为明显和系统化，因为它不仅基于找到LCA的节点，还综合了是否已在子树中找到特定节点的信息。
struct LCAInfo {
  TreeNode *ancestor; // 最低公共祖先节点
  bool foundP;
  bool foundQ;
};

LCAInfo findLCA(TreeNode *root, TreeNode *p, TreeNode *q) {
  if (root == nullptr) {
    return {nullptr, false, false};
  }

  LCAInfo leftInfo = findLCA(root->left, p, q);
  // 递归调用首先检查左子树。如果左子树已经确定了LCA，那么就没有必要继续检查右子树或执行任何其他操作。此时递归直接终止并向上返回左子树找到的LCA结果。这是一个明确的递归提前终止情形，因为一旦找到了LCA，就无需继续搜索。
  if (leftInfo.ancestor != nullptr) {
    // 如果左子树已找到LCA，直接返回
    return leftInfo;
  }

  LCAInfo rightInfo = findLCA(root->right, p, q);
  // 类似于左子树的处理，如果右子树递归调用发现了LCA，则该信息直接返回，进一步的搜索（在其他分支或更深层的递归）将立即停止。
  if (rightInfo.ancestor != nullptr) {
    // 如果右子树已找到LCA，直接返回
    return rightInfo;
  }

  bool foundP = (root == p) || leftInfo.foundP || rightInfo.foundP;
  bool foundQ = (root == q) || leftInfo.foundQ || rightInfo.foundQ;

  if (foundP && foundQ) {
    // 如果当前节点下同时找到了p和q，则当前节点是它们的LCA
    return {root, true, true};
  }

  // 返回当前节点下p和q的查找结果，但还未确定LCA
  return {nullptr, foundP, foundQ};
}

TreeNode *lowestCommonAncestor2(TreeNode *root, TreeNode *p, TreeNode *q) {
  LCAInfo result = findLCA(root, p, q);
  return result.ancestor;
}

int main() {
  /* 创建示例树：
       3
      / \
     5   1
    / \ / \
   6  2 0  8
  */
  TreeNode *root = new TreeNode(3);
  root->left = new TreeNode(5);
  root->right = new TreeNode(1);
  root->left->left = new TreeNode(6);
  root->left->right = new TreeNode(2);
  root->left->right->right = new TreeNode(4);
  root->right->left = new TreeNode(0);
  root->right->right = new TreeNode(8);

  TreeNode *p = root->left->left;         // Node 5
  TreeNode *q = root->left->right->right; // Node 1

  TreeNode *lca = lowestCommonAncestor2(root, p, q);
  cout << "The lowest common ancestor of " << p->val << " and " << q->val
       << " is " << lca->val << endl;

  return 0;
}
