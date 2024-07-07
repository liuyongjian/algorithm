#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 函数用于构建部分匹配表
vector<int> buildPartialMatchTable(const string &pattern) {
  int m = pattern.length();
  vector<int> lps(m, 0); // 长度为m的数组，初始化为0
  // 对于模式串中任意位置 i，len 表示直到该位置（不包括 i
  // 本身）的子串中，最长的相同的前缀和后缀的长度。
  int len = 0;
  int i = 1; // lps的当前位置

  while (i < m) {
    // 表示当前已知最长前缀的下一个字符）相匹配，那么增加 len
    if (pattern[i] == pattern[len]) {
      len++;
      lps[i] = len;
      i++;
    } else { // 不匹配
      // 如果当前字符不匹配且 len 不为 0，则尝试找到次长的相同前缀和后缀。
      // 这通过回溯到 lps[len - 1] 实现，len - 1 表示最长前缀的前一位置，lps[len
      // - 1] 给出了次长匹配的长度。
      if (len != 0) {
        len = lps[len - 1];
      } else { // 如果len为0
        lps[i] = 0;
        i++;
      }
    }
  }

  return lps;
}

// KMP搜索函数
void KMPSearch(const string &text, const string &pattern) {
  int n = text.length();
  int m = pattern.length();

  vector<int> lps = buildPartialMatchTable(pattern);

  int i = 0; // 文本的索引
  int j = 0; // 模式的索引(可以根据lps数组向前跳)

  while (i < n) {
    if (pattern[j] == text[i]) {
      i++;
      j++;
    }

    // 检查模式串的指针 j 是否已经到达模式串的末尾（j ==
    // m），如果是，说明我们找到了一个完整的模式匹配
    if (j == m) {
      cout << "Found pattern at index " << (i - j) << endl;
      // 一旦找到一个匹配，它不会停止搜索，而是使用部分匹配表（也称为最长前缀后缀表或LPS表）来决定下一步的搜索开始位置。
      // 在找到一个匹配之后继续寻找下一个可能的匹配，同时避免了重复的工作和不必要的比较。

      // 在某些情况下，模式串中可能存在重叠的匹配情况。例如，如果模式串是
      // "aba"，在文本 "ababa" 中，我们有两次匹配："aba" 和
      // "aba"，这两个匹配是部分重叠的。 如果我们简单地将 j 重置到 0
      // 并继续搜索，则可能会错过第二个重叠的匹配。
      j = lps[j - 1];
    } else if (i < n && pattern[j] != text[i]) { // 不匹配
      if (j != 0) {
        // 如果模式串的指针 j 不在起始位置，这意味着我们有一部分已经匹配了。
        // 在这种情况下，我们不需要从模式串的起始位置重新开始匹配，而是可以根据部分匹配表
        // lps 回退到上一个可能的匹配位置。
        // 这样可以跳过那些我们已经知道不匹配的部分。
        j = lps[j - 1];
      } else {
        // 如果 j 已经跳到了模式串的起始位置（j ==
        // 0），这表示我们还没有成功匹配任何部分，所以只能将文本串的指针 i
        // 向前移动一位，尝试下一个新的开始位置。
        i++;
      }
    }
  }
}

int main() {
  string text = "ABABDABACDABABCABAB";
  string pattern = "ABABCABAB";

  KMPSearch(text, pattern);

  return 0;
}
