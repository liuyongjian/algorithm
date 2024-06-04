#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <iostream>
#include <queue>
#include <unordered_map>

using std::cout;
using std::endl;
using std::max;
using std::queue;
using std::unordered_map;

struct TreeNode {
  int value;
  TreeNode *left;
  TreeNode *right;

  TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

int maxWidthOfTree(TreeNode *root) {
  if (root == nullptr)
    return 0;

  queue<TreeNode *> q;
  q.push(root);
  int maxWidth = 0; // 用于记录最大宽度

  while (!q.empty()) {
    int levelSize = q.size();            // 当前层的节点数
    maxWidth = max(maxWidth, levelSize); // 更新最大宽度

    for (int i = 0; i < levelSize; ++i) {
      TreeNode *current = q.front();
      q.pop();

      // 访问当前节点
      cout << current->value << " ";

      // 将当前节点的子节点加入队列
      if (current->left != nullptr) {
        q.push(current->left);
      }
      if (current->right != nullptr) {
        q.push(current->right);
      }
    }

    // 这里表示一层的结束
    cout << endl; // 打印换行符来分隔各层
  }

  return maxWidth; // 返回最大宽度
}

// 基准方法：通过递归的方式来计算每个层级的宽度，而不是使用队列。这种方法在逻辑上有所不同，可以提供有效的对照。
void calculateWidthAtEachLevel(TreeNode *node, int level,
                               unordered_map<int, int> &widthMap) {
  if (!node)
    return;
  widthMap[level]++; // Increment the count of nodes at the current level
  calculateWidthAtEachLevel(node->left, level + 1, widthMap);
  calculateWidthAtEachLevel(node->right, level + 1, widthMap);
}

int calculateMaxWidth(TreeNode *root) {
  unordered_map<int, int>
      widthMap; // Maps each level to its width (number of nodes)
  calculateWidthAtEachLevel(root, 0, widthMap);

  int maxWidth = 0;
  for (auto &it : widthMap) {
    maxWidth = max(maxWidth,
                   it.second); // Find the maximum width across all levels
  }
  return maxWidth;
}

// Generate a random tree
TreeNode *generateRandomTree(int depth) {
  // 当 rand() % 3
  // 的结果为0时（大约有1/3的概率），条件为真。这意味着在约三分之一的情况下，函数会返回
  // nullptr，即不会为当前节点创建左子或右子。
  // 这样做的结果是，一些分支会早些结束，而其他分支可能会继续延伸，创建出不同深度和形状的树。
  // 目的是为了随机生成不同形状和大小的树，包括更深的树和一些更不平衡的结构。
  if (depth == 0 || rand() % 3 == 0) { // Randomly stop
    return nullptr;
  }
  TreeNode *root = new TreeNode(rand() % 100);
  root->left = generateRandomTree(depth - 1);
  root->right = generateRandomTree(depth - 1);
  return root;
}

void deleteTree(TreeNode *root) {
  if (root == nullptr)
    return;
  deleteTree(root->left);
  deleteTree(root->right);
  delete root;
}

void testMaxWidth() {
  srand(time(nullptr)); // Seed random number generator
  int testCases = 100;  // Number of test cases

  for (int i = 0; i < testCases; ++i) {
    cout << "----------------------" << endl;
    cout << "Test case " << (i + 1) << ": " << endl;

    TreeNode *root = generateRandomTree(5);
    if (!root) {
      cout << "Tree is empty." << endl;
      continue;
    }

    int expectedWidth = calculateMaxWidth(root);
    int actualWidth = maxWidthOfTree(root);

    cout << "Expected Max width = " << expectedWidth
         << ", Actual Max width = " << actualWidth << endl;

    if (expectedWidth != actualWidth) {
      cout << "Error: Widths do not match!" << endl;
    }

    deleteTree(root);
  }
  cout << "----------------------" << endl;
}

int main() {
  testMaxWidth();
  return 0;
}
