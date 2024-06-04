#include <iostream>

using std::cout;
using std::endl;

// 给定一个节点，要找到它的后继节点
// 关键点：分几种情况讨论：
// 如果节点有右子树：在这种情况下，后继节点是右子树中的最左节点。因为根据中序遍历的定义，你首先访问左子节点，然后是根节点，最后是右子节点。
// 如果节点没有右子树：向上寻找该节点的最低祖先节点，且该祖先节点的左子树包含该节点。

class Node {
public:
  int value;
  Node *left;
  Node *right;
  Node *parent;

  Node(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr) {}

  // 析构函数自动删除所有子节点
  ~Node() {
    delete left;
    delete right;
  }
};

Node *findSuccessor(Node *node) {
  if (node == nullptr) {
    // 如果节点为空，则没有后继节点
    return nullptr;
  }

  if (node->right != nullptr) {
    // 如果节点有右子树，则后继节点是右子树中最左边的节点
    Node *current = node->right; // 开始于右子节点
    while (current->left != nullptr) {
      current = current->left; // 沿左子树一直往下走到底
    }
    return current; // 返回最左节点，即后继节点
  }

  // 如果没有右子树，后继节点是“最低”的祖先节点，其中给定节点位于该祖先节点的左子树中
  Node *current = node->parent; // 向上追溯祖先节点
  // 如果current = nullptr 直接跳出循环 return nullptr
  // 或者找到的祖先节点的左子树包含该节点，返回 当前的current 即祖先节点
  while (current != nullptr && current->right == node) {
    node = current;            // 向上移动到父节点
    current = current->parent; // 继续向上寻找
  }
  return current; // 当前的current即为所求的后继节点
}

int main() {
  /*
    创建一个简单的树:
        1
       / \
      2   3
     /
    4
  */
  Node *root = new Node(1);
  Node *node2 = new Node(2);
  Node *node3 = new Node(3);
  Node *node4 = new Node(4);

  root->left = node2;
  root->right = node3;
  node2->parent = root;
  node3->parent = root;

  node2->left = node4;
  node4->parent = node2;

  Node *successor = findSuccessor(node4);
  if (successor) {
    cout << "The successor of node " << node4->value << " is "
         << successor->value << endl;
  } else {
    cout << "The node has no successor." << endl;
  }

  // 只需删除根节点，其余节点将通过递归析构函数自动删除
  delete root;

  return 0;
}
