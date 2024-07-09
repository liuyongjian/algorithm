#include <iostream>

using namespace std;

// 定义二叉树节点结构体
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Morris中序遍历
void morrisInorderTraversal(TreeNode *root) {
  // 仅需要cur和mostRight这两个变量
  TreeNode *cur = root;
  TreeNode *mostRight = nullptr;

  while (cur != nullptr) {
    if (cur->left == nullptr) {
      cout << cur->val << " "; // 访问当前节点
      cur = cur->right;        // 移动到右子树
    } else {
      // 找到当前节点左子树的最右节点
      mostRight = cur->left;
      while (mostRight->right != nullptr && mostRight->right != cur) {
        mostRight = mostRight->right;
      }

      if (mostRight->right == nullptr) {
        // 建立临时链接
        mostRight->right = cur;
        cur = cur->left; // 移动到左子树
      } else {
        // 撤销临时链接
        mostRight->right = nullptr;
        cout << cur->val << " "; // 访问当前节点
        cur = cur->right;        // 移动到右子树
      }
    }
  }
}

int main() {
  // 构建一个简单的树： 1 <- 2 -> 3
  TreeNode *root = new TreeNode(2);
  root->left = new TreeNode(1);
  root->right = new TreeNode(3);

  cout << "Morris Inorder Traversal: ";
  morrisInorderTraversal(root); // 应输出：1 2 3
  cout << endl;

  return 0;
}
