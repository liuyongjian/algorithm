#include <iostream>
#include <set>
#include <string>
#include <vector>

class TrieNode {
public:
  // 需要假定所有的输入字符都是小写字母（从 'a' 到
  // 'z'）。这种方法将简化索引操作并可能提高性能，利用了数组索引来直接访问子节点，这样避免了哈希表的开销，数组的索引访问比哈希表查找要快。
  TrieNode *children[26]; // 存储26个英文字母的指针数组
  bool endOfWord;
  int count; // 记录经过此节点的单词数量

  TrieNode() : endOfWord(false), count(0) {
    for (int i = 0; i < 26; ++i) {
      children[i] = nullptr;
    }
  }

  ~TrieNode() {
    for (int i = 0; i < 26; ++i) {
      delete children[i];
    }
  }
};

class Trie {
private:
  TrieNode *root;

public:
  Trie() { root = new TrieNode(); }

  ~Trie() { delete root; }

  void insert(const std::string &word) {
    TrieNode *current = root;
    current->count++;
    for (char ch : word) {
      int index = ch - 'a';
      if (!current->children[index]) {
        current->children[index] = new TrieNode();
      }
      current = current->children[index];
      current->count++;
    }
    current->endOfWord = true;
  }

  bool search(const std::string &word) {
    TrieNode *current = findNode(word);
    return current != nullptr && current->endOfWord;
  }

  bool startsWith(const std::string &prefix) {
    return findNode(prefix) != nullptr;
  }

  void remove(const std::string &word) { remove(root, word, 0); }

  void printAllWords() {
    std::string currentWord;
    printAllWords(root, currentWord);
  }

private:
  TrieNode *findNode(const std::string &prefix) {
    TrieNode *current = root;
    for (char ch : prefix) {
      int index = ch - 'a';
      if (!current->children[index]) {
        return nullptr;
      }
      current = current->children[index];
    }
    return current;
  }

  bool remove(TrieNode *node, const std::string &word, size_t depth) {
    if (node == nullptr)
      return false;
    // 检查当前递归的深度是否已经达到单词长度。如果是，那么我们应该在当前节点做删除标记。
    if (depth == word.size()) {
      //  如果当前节点标记为单词的结尾，我们首先将其标记为非结束节点
      if (node->endOfWord) {
        node->endOfWord = false;
        // 遍历所有子节点，检查是否有非空子节点
        for (int i = 0; i < 26; ++i) {
          // 如果任何一个子节点不为空，返回 false
          // 表示不能删除此节点，因为它仍然是其他单词的一部分。
          if (node->children[i] != nullptr) {
            return false;
          }
        }
        // 如果所有子节点都是空的，返回 true 表示这个节点可以删除。
        return true;
      }
      return false;
    }

    int index = word[depth] - 'a';
    // 如果子节点存在，并且成功删除了子树，且当前节点不是其他单词的结尾
    if (node->children[index] &&
        remove(node->children[index], word, depth + 1) && !node->endOfWord) {

      delete node->children[index];

      node->children[index] = nullptr;
      // 再次检查当前节点的所有子节点，确保没有其他非空子节点存在，如果是，返回
      // true 表示当前节点也可以删除。
      for (int i = 0; i < 26; ++i) {
        if (node->children[i] != nullptr) {
          return false;
        }
      }
      return true;
    }
    // 如果在任何阶段删除操作未能执行（如未找到单词或节点不能删除因为它仍然是其他单词的一部分），函数返回
    // false。
    return false;
  }

  void printAllWords(TrieNode *node, std::string &currentWord) {
    if (node->endOfWord) {
      std::cout << currentWord << std::endl;
    }

    for (int i = 0; i < 26; ++i) {
      if (node->children[i] != nullptr) {
        currentWord.push_back('a' + i);
        printAllWords(node->children[i], currentWord);
        currentWord.pop_back();
      }
    }
  }
};

// 生成随机字符串
std::string generateRandomString(int maxLength) {
  int length = rand() % (maxLength + 1); // 随机长度
  std::string result;
  for (int i = 0; i < length; i++) {
    char ch = 'a' + rand() % 26;
    result.push_back(ch);
  }
  return result;
}

// 对数器函数
// trieTest 在 Trie 类和 std::set
// 之间执行大量的插入、删除和搜索操作，并比较结果。
void trieTest() {
  Trie trie;
  std::set<std::string> referenceSet;
  int testCount = 1000; // 测试次数
  int maxLength = 10;   // 最大字符串长度

  srand(time(NULL)); // 初始化随机数生成器

  for (int i = 0; i < testCount; i++) {
    std::string str = generateRandomString(maxLength);

    // 插入操作测试
    trie.insert(str);
    referenceSet.insert(str);

    // 删除操作测试（有一定的概率执行删除操作）
    if (rand() % 4 == 0 && !referenceSet.empty()) {
      int removeIndex = rand() % referenceSet.size();
      auto it = referenceSet.begin();
      std::advance(it, removeIndex);
      trie.remove(*it);
      referenceSet.erase(it);
    }

    // 搜索操作测试
    std::string searchStr = generateRandomString(maxLength);
    bool trieSearchResult = trie.search(searchStr);
    bool setSearchResult = referenceSet.find(searchStr) != referenceSet.end();
    if (trieSearchResult != setSearchResult) {
      std::cout << "Mismatch found for string: " << searchStr << std::endl;
      break;
    }
  }

  std::cout << "Test completed. If no mismatch found, implementation is likely "
               "correct."
            << std::endl;
}

int main() {
  trieTest();
  return 0;
}
