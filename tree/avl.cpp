#include <algorithm>
#include <iostream>

using namespace std;

// 定义AVL树的节点
class Node {
public:
  int key;
  Node *left;
  Node *right;
  int height;

  Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

// 定义AVL树类
class AVLTree {
public:
  Node *root;

  AVLTree() : root(nullptr) {}

  // 获取节点的高度
  int height(Node *node) {
    if (!node)
      return 0;
    return node->height;
  }

  // 更新节点的高度
  void updateHeight(Node *node) {
    node->height = 1 + max(height(node->left), height(node->right));
  }

  // 计算节点的平衡因子
  int getBalance(Node *node) {
    if (!node)
      return 0;
    return height(node->left) - height(node->right);
  }

  // 右旋操作
  // y 是需要进行右旋的节点
  Node *rightRotate(Node *y) {
    // x 是y的左子节点，将成为旋转后的新根节点。
    Node *x = y->left;
    // T2 是x的右子节点，它将成为y的左子节点。
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
  }

  // 左旋操作
  // x 是需要进行左旋的节点
  Node *leftRotate(Node *x) {
    // y 是x的右子节点，将成为旋转后的新根节点
    Node *y = x->right;
    // T2 是y的左子节点，它将成为x的右子节点
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
  }

  Node *rebalance(Node *node) {
    // 首先更新当前节点的高度
    updateHeight(node);

    // 计算当前节点的平衡因子
    int balance = getBalance(node);

    // 如果当前节点的平衡因子大于1，并且左子节点的平衡因子大于等于0，说明是左左不平衡
    // 执行右旋操作以恢复平衡
    if (balance > 1 && getBalance(node->left) >= 0) {
      return rightRotate(node);
    }

    // 如果当前节点的平衡因子小于-1，并且右子节点的平衡因子小于等于0，说明是右右不平衡
    // 执行左旋操作以恢复平衡
    if (balance < -1 && getBalance(node->right) <= 0) {
      return leftRotate(node);
    }

    // 如果当前节点的平衡因子大于1，并且左子节点的平衡因子小于0，说明是左右不平衡
    // 首先对左子节点进行左旋转成左左不平衡，然后对当前节点执行右旋以恢复平衡
    if (balance > 1 && getBalance(node->left) < 0) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }

    // 如果当前节点的平衡因子小于-1，并且右子节点的平衡因子大于0，说明是右左不平衡
    // 首先对右子节点进行右旋转成右右不平衡，然后对当前节点执行左旋以恢复平衡
    if (balance < -1 && getBalance(node->right) > 0) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }

    // 如果不需要旋转，直接返回当前节点
    return node;
  }

  // 插入节点
  Node *insert(Node *node, int key) {
    if (!node)
      return new Node(key);

    if (key < node->key) {
      // 不能直接 insert(node->left, key)
      // 插入新节点可能导致一个或多个旋转（左旋或右旋）。每次旋转都可能改变子树的根节点。
      // 如果不重新设置 node->left 或
      // node->right，任何旋转带来的改变都不会反映到整个树结构中，这会导致数据结构的不一致，进而影响树的操作
      node->left = insert(node->left, key);
    } else if (key > node->key) {
      node->right = insert(node->right, key);
    } else {
      return node;
    }

    return rebalance(node);
  }

  void insert(int key) { root = insert(root, key); }

  // 找到树中的最小节点
  Node *findMin(Node *node) {
    Node *current = node;
    while (current->left != nullptr) {
      current = current->left;
    }
    return current;
  }

  // 删除节点
  Node *deleteNode(Node *root, int key) {
    if (root == nullptr) {
      return root;
    }

    // 递归找到要删除的节点
    if (key < root->key) {
      root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
      root->right = deleteNode(root->right, key);
    } else {
      // 找到要删除的节点
      if (root->left == nullptr || root->right == nullptr) {
        Node *temp = root->left ? root->left : root->right;

        // 无子节点或只有一个子节点
        if (temp == nullptr) {
          temp = root;
          root = nullptr;
        } else {
          // 有一个子节点
          *root = *temp; // 复制内容
        }
        delete temp;
      } else {
        // 有两个子节点，获取中序后继
        Node *temp = findMin(root->right);

        // 将后继的值复制到这个节点
        root->key = temp->key;

        // 删除后继
        root->right = deleteNode(root->right, temp->key);
      }
    }

    if (!root)
      return root;

    return rebalance(root);
  }

  void deleteKey(int key) { root = deleteNode(root, key); }

  // 辅助函数，用于打印树的结构
  void printInOrder(Node *node) {
    if (node) {
      printInOrder(node->left);
      cout << node->key << " ";
      printInOrder(node->right);
    }
  }

  void print() {
    printInOrder(root);
    cout << endl;
  }
};

// 主函数来演示AVL树
int main() {
  AVLTree tree;

  // 插入元素
  tree.insert(9);
  tree.insert(5);
  tree.insert(10);
  tree.insert(0);
  tree.insert(6);
  tree.insert(11);
  tree.insert(-1);
  tree.insert(1);
  tree.insert(2);

  // 打印中序遍历的结果
  cout << "Initial AVL Tree (In-Order): ";
  tree.print();

  // 删除几个元素
  tree.deleteKey(10);
  tree.deleteKey(1);

  // 再次打印中序遍历的结果
  cout << "AVL Tree after deletions (In-Order): ";
  tree.print();

  return 0;
}
