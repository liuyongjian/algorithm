#include <iostream>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 反转从 start 到 end 的路径
void reversePath(TreeNode *start, TreeNode *end) {
  TreeNode *prev = nullptr, *curr = start, *next;
  while (prev != end) {
    // 暂存当前节点的下一个节点。
    next = curr->right;
    // 将当前节点的 right 指针指向前一个节点，从而实现反转。
    curr->right = prev;
    // 更新 prev 到当前节点
    prev = curr;
    // 移动指针到下一个节点。
    curr = next;
  }
}

// 打印反转后的路径，并恢复原路径
void printPath(TreeNode *start, TreeNode *end) {
  // 反转路径从 start 到 end
  reversePath(start, end);

  // 打印从 end 到 start 的逆序路径
  TreeNode *p = end;
  while (p != nullptr) {
    cout << p->val << " ";
    if (p == start)
      break;
    p = p->right;
  }

  // 恢复原始路径
  reversePath(end, start);
}

// Morris后序遍历
void morrisPostorderTraversal(TreeNode *root) {
  // 通过引入 dummy 节点，并将其左子节点指向实际的根节点
  // root，可以统一处理根节点及其左子树的遍历，而不需要在主循环中对根节点做特殊处理。
  // 在最后打印整棵树的右边界时，可以从 dummy
  // 节点开始，这样能够确保包括根节点在内的所有节点都被正确处理和打印。
  TreeNode dummy(0); // 创建一个虚拟节点
  dummy.left = root;
  TreeNode *cur = &dummy, *prev = nullptr;

  while (cur != nullptr) {
    if (cur->left == nullptr) {
      cur = cur->right;
    } else {
      prev = cur->left;
      while (prev->right != nullptr && prev->right != cur) {
        prev = prev->right;
      }
      if (prev->right == nullptr) {
        prev->right = cur; // 建立临时链接
        cur = cur->left;
      } else {
        printPath(cur->left, prev); // 打印左子树(root)右边界的逆序
        prev->right = nullptr;      // 撤销临时链接
        cur = cur->right;
      }
    }
  }

  // 引入dummy 虚拟节点就不需要逆序打印整棵树的右边界了
  // printPath(dummy.left, nullptr);
}

int main() {
  TreeNode *root = new TreeNode(2);
  root->left = new TreeNode(1);
  root->right = new TreeNode(3);

  cout << "Morris Postorder Traversal: ";
  morrisPostorderTraversal(root); // 应输出：1 3 2
  cout << endl;

  return 0;
}
