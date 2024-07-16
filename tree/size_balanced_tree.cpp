#include <iostream>

struct Node {
  int key;
  Node *left;
  Node *right;
  int size;

  Node(int key) : key(key), left(nullptr), right(nullptr), size(1) {}
};

// 更新节点大小
void updateSize(Node *node) {
  if (!node)
    return;

  node->size = 1 + (node->left ? node->left->size : 0) +
               (node->right ? node->right->size : 0);
}

// 右旋操作:
// 作用于当左子树的大小过大时，将左子节点提升为当前根节点，原根节点下降为右子节点，从而平衡树。
void rightRotate(Node *&root) {
  Node *temp = root->left;

  root->left = temp->right;
  temp->right = root;

  updateSize(root);
  updateSize(temp);

  root = temp;
}

// 左旋操作:
// 用于当右子树的大小过大时，将右子节点提升为当前根节点，原根节点下降为左子节点，从而平衡树。
void leftRotate(Node *&root) {
  Node *temp = root->right;
  root->right = temp->left;
  temp->left = root;
  updateSize(root);
  updateSize(temp);
  root = temp;
}

// 插入新节点并保持树平衡
void insert(Node *&root, int key) {
  if (!root) {
    root = new Node(key);
    return;
  }

  if (key < root->key) {
    insert(root->left, key);
    if (root->right && root->left->size > 2 * root->right->size) {
      rightRotate(root);
    }
  } else {
    insert(root->right, key);
    if (root->left && root->right->size > 2 * root->left->size) {
      leftRotate(root);
    }
  }

  updateSize(root);
}

// 找到树中的最小节点
Node *findMin(Node *node) {
  Node *current = node;

  while (current->left != nullptr) {
    current = current->left;
  }

  return current;
}

// 删除指定节点
Node *remove(Node *&root, int key) {
  if (!root)
    return nullptr;

  if (key < root->key) {
    remove(root->left, key);
  } else if (key > root->key) {
    remove(root->right, key);
  } else {
    if (!root->left || !root->right) {
      Node *temp = root->left ? root->left : root->right;
      delete root;
      root = temp;
    } else {
      // 有两个子节点，获取中序后继
      Node *temp = findMin(root->right);

      root->key = temp->key;
      root->right = remove(root->right, temp->key);
    }
  }

  if (!root)
    return nullptr;

  updateSize(root);

  // Rebalance:
  // SBT的平衡条件是通过比较节点的左右子树大小来决定是否进行旋转，所以通过简单的左旋和右旋操作就能保持树的平衡。
  // 而不需要像AVL树那样对高度"敏感"，需要明确地区分LL，LR，RR, RL类型。
  if (root->right && root->left->size > 2 * root->right->size) {
    rightRotate(root);
  } else if (root->left && root->right->size > 2 * root->left->size) {
    leftRotate(root);
  }

  return root;
}

// 中序遍历打印树
void inorderPrint(Node *root) {
  if (!root)
    return;

  inorderPrint(root->left);
  std::cout << root->key << " (" << root->size << ") ";
  inorderPrint(root->right);
}

int main() {
  Node *root = nullptr;
  insert(root, 10);
  insert(root, 5);
  insert(root, 15);
  insert(root, 20);
  insert(root, 3);
  // 加入节点8，删除节点10时会导致节点右旋
  // insert(root, 8);

  std::cout << "Inorder traversal before deletion: ";
  inorderPrint(root);
  std::cout << "\n";

  remove(root, 10); // 删除根节点测试

  std::cout << "Inorder traversal after deletion: ";
  inorderPrint(root);
  std::cout << "\n";

  return 0;
}
