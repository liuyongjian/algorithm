#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

class TrieNode {
public:
  map<char, TrieNode *> children;
  TrieNode *fail;
  bool endOfWord;

  TrieNode() : fail(nullptr), endOfWord(false) {}
};

class AhoCorasick {
private:
  TrieNode *root;

public:
  AhoCorasick() { root = new TrieNode(); }

  // 将模式字符串插入到Trie树中，并在模式字符串的最后一个节点设置 endOfWord 标记
  void insert(const string &word) {
    TrieNode *node = root;

    for (char ch : word) {
      if (node->children.find(ch) == node->children.end()) {
        node->children[ch] = new TrieNode();
      }

      node = node->children[ch];
    }

    node->endOfWord = true;
  }

  // 构建失败指针。使用广度优先搜索（BFS）遍历Trie树，为每个节点设置失败指针
  void buildFailureLinks() {
    queue<TrieNode *> q;

    // 初始化根节点的子节点的失败指针为根节点，并将这些子节点加入队列
    for (auto &p : root->children) {
      p.second->fail = root;
      q.push(p.second);
    }

    // 使用广度优先搜索（BFS）构建失败指针
    while (!q.empty()) {
      // q.front() 返回队列中的第一个元素，即当前正在处理的节点 current。
      TrieNode *current = q.front();
      // 通过 q.pop() 将该节点从队列中移除
      q.pop();

      // 遍历当前节点的所有子节点
      for (auto &p : current->children) {
        TrieNode *child = p.second;
        TrieNode *fallback = current->fail;

        // 寻找失败指针目标节点
        // 确保回溯不会超出Trie树的范围，并检查 fallback 节点是否有与当前字符
        // p.first 对应的子节点
        while (fallback != nullptr &&
               fallback->children.find(p.first) == fallback->children.end()) {
          // 如果没有对应的子节点，则继续沿着失败指针回溯，直到找到一个包含该字符的节点，或者回溯到根节点（失败指针为
          // nullptr）。
          fallback = fallback->fail;
        }

        // 设置子节点的失败指针
        // 1. 如果 fallback 节点（当前节点的失败指针）有一个与当前字符 p.first
        // 相匹配的子节点，则将 child 的失败指针设置为 fallback 的那个子节点。
        // 2. 如果 fallback 节点没有与当前字符 p.first 相匹配的子节点，则将
        // child 的失败指针设置为根节点 root。
        child->fail = (fallback) ? fallback->children[p.first] : root;

        // 将子节点加入队列，进行后续处理
        q.push(child);
      }
    }
  }

  // 在给定的文本中搜索所有模式字符串。每当到达一个节点时，检查该节点及其通过失败指针链接的所有节点是否为某个模式字符串的结束节点
  void search(const string &text) {
    TrieNode *node = root;
    int index = 0; // 用于跟踪当前的字符索引

    for (char ch : text) {
      // 如果当前节点的子节点中没有字符 ch，则通过失败指针 node->fail
      // 回退，直到找到一个匹配的节点或回到根节点。
      while (node != root && node->children.find(ch) == node->children.end()) {
        node = node->fail;
      }

      // 如果当前节点的子节点中有字符 ch，则移动到该子节点。
      if (node->children.find(ch) != node->children.end()) {
        node = node->children[ch];
      }

      // 使用temp确保node节点每次遍历不变，使用临时变量方便检查当前节点以及通过失败指针链连接的所有节点。不仅检查当前节点，还检查通过失败指针链连接的所有可能匹配的模式字符串
      // 比如可以在匹配 "she" 的同时发现 "he" 的匹配
      TrieNode *temp = node;

      // 检查当前节点或任何失败链接的节点是否标记为单词的结束
      while (temp != root) {
        if (temp->endOfWord) {
          cout << "Pattern found ending at index " << index << endl;
        }

        temp = temp->fail;
      }

      index++; // 更新索引
    }
  }
};

int main() {
  AhoCorasick ac;

  ac.insert("he");
  ac.insert("she");
  ac.insert("his");
  ac.insert("hers");

  ac.buildFailureLinks();
  ac.search("ushers");

  return 0;
}
