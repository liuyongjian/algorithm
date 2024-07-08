#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 在每个字符之间插入一个特殊字符 #，并在字符串的首尾添加开始和结束标记 ^ 和
// $，以防止在后续处理中数组越界。 这样做还可以确保即使是长度为 1
// 的字符也被视为回文中心，简化后续的回文检查逻辑。
string preprocess(const string &s) {
  if (s.empty())
    return "^$";
  string ret = "^"; // 开始标记，防止越界

  for (char c : s) {
    ret += "#" + string(1, c);
  }

  ret += "#$"; // 结束标记，防止越界

  return ret;
}

string manacher(string s) {
  string T = preprocess(s);
  int n = T.length();
  // p 是一个数组，其中 p[i] 表示以 T[i] 为中心的最长回文半径。
  vector<int> p(n, 0);
  // C 是当前找到的最长回文的中心位置，R 是对应的右边界。
  int C = 0, R = 0;

  for (int i = 1; i < n - 1; i++) {
    // 利用 i_mirror = 2 * C - i 确定位置 i 关于中心 C 的对称点。
    int i_mirror = 2 * C - i;
    // 如果 i 在当前最长回文的右边界 R 内，通过对称性确定 p[i] 的初值。
    if (R > i) {
      p[i] = min(R - i, p[i_mirror]);
    }

    // 通过扩展比较 T 中的字符来尝试增加 p[i]，直到不再匹配为止。
    // while条件成立时，意味着以 i 为中心的回文可以进一步向外扩展一个字符

    // 假设预处理后的字符串 T 为 #a#b#a#b#a#，现在以 i=4（对应原字符串中的第一个
    // b）为中心，我们有：
    // 初始 p[4] = 0（意味着最小的回文是 b 本身）。
    // 检查 T[4 + 1 + 0] (T[5]) 是否等于 T[4 - 1 - 0] (T[3])，即 # 是否等于#。
    // 如果相等，p[4] 增加 1，现在 p[4] = 1。 接着再检查 T[4 + 1 + 1]
    // (T[6])是否等于 T[4 - 1 - 1] (T[2])，即 a 是否等于 a。 如果相等，p[4]
    // 再次增加1，现在 p[4] = 2。
    while (T[i + 1 + p[i]] == T[i - 1 - p[i]]) {
      // 此时，p[i] 的值将增加
      // 1，表示回文半径增长。这个过程会持续进行，直到找到的字符不再形成回文为止。
      p[i]++;
    }

    // 若扩展后的回文右边界超出 R，更新中心 C 和右边界 R。
    if (i + p[i] > R) {
      C = i;
      R = i + p[i];
    }
  }

  int max_length = 0;
  int center_index = 0;

  // 遍历 p 找到最长回文的长度和中心位置
  for (int i = 1; i < n - 1; i++) {
    if (p[i] > max_length) {
      max_length = p[i];
      center_index = i;
    }
  }

  // 并从原字符串 s 中提取出最长回文子串。
  return s.substr((center_index - 1 - max_length) / 2, max_length);
}

int main() {
  string s = "cabacbad";

  cout << "The longest palindromic substring is: " << manacher(s) << endl;

  return 0;
}
