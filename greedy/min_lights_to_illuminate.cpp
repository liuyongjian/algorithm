#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

/*
  题目：
  给定一个字符串str，只由'X'和'.'两种字符构成。
  'X'表示墙，不能放灯，也不需要点亮。
  '.'表示居民点，可以放灯，需要点亮。
  如果灯放在位置i，可以让i-1、i和i+1三个位置被点亮。
  返回如果点亮str中所有需要点亮的位置，至少需要几盏灯。

  关键点：
  贪心策略：每次放置灯的位置应尽可能利用灯的最大照明范围。这意味着每当遇到一个未被照明的居民点('.'),
  应考虑在当前或紧接的未来位置放置灯，以最大化其覆盖范围。

  最远点放置原则：为了最大化每盏灯的覆盖效果，我们通常选择在当前遇到的未照亮的居民点后第二个位置放置灯（即如果当前位置是i，放置灯的位置为i+2），前提是i+2位置也是居民点。
  这样做的原因是，放置在i+2的灯不仅能照亮i+2位置，还能照亮i+1和i位置，从而达到一盏灯照亮三个连续的居民点的最优效果。

  边界条件处理：处理字符串两端以及接壤墙('X')的情况。当靠近字符串的结尾或者墙的位置时，可能无法在最理想的位置放置灯，这时需要根据实际情况灵活调整灯的放置位置。
*/

// illuminated: 被照明的
int minLightsToIlluminate(const string &str) {
  size_t n = str.length();
  size_t i = 0;
  int lights = 0;

  while (i < n) {
    if (str[i] == 'X') {
      i++;
    } else {
      // i如果是 '.' 不管什么条件 灯的数量都会加一
      lights++;
      if (i + 2 < n && str[i + 2] == '.') {
        i += 3; // 灯放在i+2位置， i跳到i+3的位置继续循环
      } else {
        i += 2; // 灯放在i+1或i位置， i跳到i+2的位置继续循环
      }
    }
  }
  return lights;
}

// 对数器，用于验证算法的准确性
bool check(const string &str, int expected) {
  vector<bool> illuminated(str.size(), false);
  size_t count = 0;
  size_t i = 0;
  while (i < str.size()) {
    if (str[i] == '.' && !illuminated[i]) {
      // 这里尝试找到放灯的最佳位置
      if (i + 2 < str.size() && str[i + 2] == '.') {
        for (size_t j = i; j <= i + 2 && j < str.size(); ++j)
          illuminated[j] = true;
        count++;
        i += 3; // 跳过已覆盖的区域
      } else if (i + 1 < str.size() && str[i + 1] == '.') {
        for (size_t j = i; j <= i + 1 && j < str.size(); ++j)
          illuminated[j] = true;
        count++;
        i += 2;
      } else {
        illuminated[i] = true;
        count++;
        i += 1;
      }
    } else {
      i++;
    }
  }

  for (size_t i = 0; i < str.size(); ++i) {
    if (str[i] == '.' && !illuminated[i])
      return false;
  }
  return count == static_cast<size_t>(expected);
}

int main() {
  string str = "XX...XX..X.XX...XX.";
  int expectedLights = minLightsToIlluminate(str);
  cout << "Minimum lights needed: " << expectedLights << endl;
  cout << "Check result: " << (check(str, expectedLights) ? "PASS" : "FAIL")
       << endl;
  return 0;
}
