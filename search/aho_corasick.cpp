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

    for (auto &p : root->children) {
      p.second->fail = root;
      q.push(p.second);
    }

    while (!q.empty()) {
      TrieNode *current = q.front();

      q.pop();

      for (auto &p : current->children) {
        TrieNode *child = p.second;
        TrieNode *fallback = current->fail;

        while (fallback != nullptr &&
               fallback->children.find(p.first) == fallback->children.end()) {
          fallback = fallback->fail;
        }

        child->fail = (fallback) ? fallback->children[p.first] : root;

        q.push(child);
      }
    }
  }

  // 在给定的文本中搜索所有模式字符串。每当到达一个节点时，检查该节点及其通过失败指针链接的所有节点是否为某个模式字符串的结束节点
  void search(const string &text) {
    TrieNode *node = root;
    int index = 0; // 用于跟踪当前的字符索引
    for (char ch : text) {
      while (node != root && node->children.find(ch) == node->children.end()) {
        node = node->fail;
      }

      if (node->children.find(ch) != node->children.end()) {
        node = node->children[ch];
      }

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
