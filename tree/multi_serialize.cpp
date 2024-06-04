#include <iostream>
#include <vector>
using namespace std;

struct MultiNode {
  int value;
  vector<MultiNode *> children;

  MultiNode(int val) : value(val) {}
};

struct BinaryNode {
  int value;
  BinaryNode *left;
  BinaryNode *right;

  BinaryNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// 多叉树转换为二叉树
BinaryNode *encode(MultiNode *root) {
  if (!root)
    return nullptr;

  BinaryNode *bNode = new BinaryNode(root->value);
  if (!root->children.empty()) {
    bNode->left = encode(root->children[0]);
  }

  BinaryNode *current = bNode->left;
  for (vector<MultiNode *>::size_type i = 1; i < root->children.size(); ++i) {
    current->right = encode(root->children[i]);
    current = current->right;
  }
  return bNode;
}

// 二叉树重建为多叉树
MultiNode *decode(BinaryNode *root) {
  if (!root)
    return nullptr;

  MultiNode *mNode = new MultiNode(root->value); // 创建多叉树节点
  BinaryNode *current =
      root->left; // 从二叉树的左孩子开始处理，这表示多叉树的第一个子节点

  while (current) {
    mNode->children.push_back(decode(current)); // 递归转换当前子节点
    current =
        current->right; // 移动到右兄弟，继续处理。right
                        // 指向同一父节点下的下一个子节点（即作为右兄弟）。
  }

  return mNode; // 返回重建的多叉树节点
}

// 打印多叉树结构
void printMultiNode(MultiNode *node, int level = 0) {
  if (!node)
    return;
  for (int i = 0; i < level; ++i)
    cout << "  ";
  cout << node->value << "\n";
  for (MultiNode *child : node->children) {
    printMultiNode(child, level + 1);
  }
}

int main() {
  // 创建多叉树
  MultiNode *root = new MultiNode(1);
  root->children.push_back(new MultiNode(2));
  root->children.push_back(new MultiNode(3));
  root->children.push_back(new MultiNode(4));

  root->children[0]->children.push_back(new MultiNode(5));
  root->children[0]->children.push_back(new MultiNode(6));

  root->children[2]->children.push_back(new MultiNode(7));

  // 转换为二叉树并打印
  BinaryNode *bRoot = encode(root);
  MultiNode *decodedRoot = decode(bRoot);

  cout << "Original MultiNode Tree:\n";
  printMultiNode(root);
  cout << "\nDecoded MultiNode Tree from BinaryNode:\n";
  printMultiNode(decodedRoot);

  return 0;
}
