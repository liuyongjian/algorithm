#include <iostream>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

struct TreeNode {
  int value;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : value(x), left(nullptr), right(nullptr) {}
};

// 序列化函数
string serialize(TreeNode *root) {
  if (!root)
    return "[]";

  string result;
  queue<TreeNode *> q;

  q.push(root);

  while (!q.empty()) {
    TreeNode *node = q.front();

    q.pop();

    if (node) {
      result += to_string(node->value) + ",";
      q.push(node->left);
      q.push(node->right);
    } else {
      result += "null,";
    }
  }

  result.pop_back(); // Remove the last comma

  return "[" + result + "]";
}

// 反序列化函数
TreeNode *deserialize(string data) {
  if (data == "[]")
    return nullptr;

  stringstream ss(data.substr(1, data.size() - 2)); // Remove brackets
  string item;

  getline(
      ss, item,
      ','); // 用于从输入流中读取字符串，直到遇到指定的分隔符，此处用来从字符串流
            // ss 中提取出下一个节点值或 "null" 标记。

  TreeNode *root = new TreeNode(stoi(item));
  queue<TreeNode *> q;
  q.push(root);

  while (!q.empty()) {
    TreeNode *node = q.front();

    q.pop();

    if (getline(ss, item, ',')) {
      if (item != "null") {
        node->left = new TreeNode(stoi(item));
        q.push(node->left);
      }
    }

    if (getline(ss, item, ',')) {
      if (item != "null") {
        node->right = new TreeNode(stoi(item));
        q.push(node->right);
      }
    }
  }

  return root;
}

int main() {
  // 测试代码
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->right->left = new TreeNode(4);
  root->right->right = new TreeNode(5);

  string serialized = serialize(root);
  cout << "Serialized tree: " << serialized << endl;

  TreeNode *deserializedRoot = deserialize(serialized);
  string reserialized = serialize(deserializedRoot);
  cout << "Reserialized tree: " << reserialized << endl;

  return 0;
}
