#include <iostream>
#include <string>

using namespace std;

/*
题目：
给定一个只包含字符 'G' 和 'B' 的数组，可以选择将所有的 'G' 移动到左侧、所有的
'B' 移动到右侧， 或者将所有的 'G' 移动到右侧、所有的 'B' 移动到左侧。
只能在相邻字符之间进行交换操作，要求计算出至少需要多少次交换。

分析：
这个算法属于数组排序类别中的一个特殊情况。具体来说，它可以被归类为一个基于计数的排序或者交换计数问题，
因为主要任务是统计在特定规则下将数组中的元素（这里是 'G' 和
'B'）重新排列所需要的最小交换次数。

通过计算每个需要移动的字符到其目标位置的距离来累计总的交换次数。这种方法假设每个字符的移动是独立的，
且可以直接通过交换到达目标位置，实际应用中这个数值代表了理想情况下的最小交换次数。

关键点：
1.
计数交换：对于每个要移动到左侧的字符，计算它当前位置与它应当到达的目标位置之间的差距。这个差值即为需要的交换次数。
2. 动态目标索引：为 'G' 或 'B' 维护一个目标索引，这个索引指示下一个 'G' 或 'B'
应该放置的位置。
3. 选择最小值：比较两种情况下的交换次数，取最小值，以实现最优解。

贪心策略：
1. 局部最优选择：
每当遇到目标字符toLeft，算法立即计算将其从当前位置移动到最前面未被占用的目标位置所需的最小步骤（交换次数）。
这一步骤是基于当前字符的位置和目标位置之间的直接距离来计算的，旨在尽快将该字符移动到正确位置。
2. 更新目标位置：
对于每个正确移动到位的 toLeft 字符，targetIndex（目标位置索引）随即更新，
以确保下一个 toLeft字符有一个正确的位置可移动至。
这一连续的更新保证了每次操作都是针对当前未解决的最前面的问题。
3. 最终目标：
通过逐个处理每个 toLeft
字符并将其移动到应有位置，贪心算法逐步构建最终的字符串结构，最后达到将所有
toLeft 字符全部排到左侧的目标。

时间复杂度：
每种情况需要 O(n) 时间来遍历字符串一次。
*/

int minSwapsToArrange(const string &s, char toLeft) {
  int swapCount = 0;   // 需要的交换次数
  int targetIndex = 0; // 目标索引位置

  for (size_t i = 0; i < s.size(); ++i) {
    if (s[i] == toLeft) {
      swapCount += i - targetIndex;
      targetIndex++;
    }
  }
  return swapCount;
}

int minSwapsToSort(const string &s) {
  // 计算将 'G' 移动到左侧，'B' 移动到右侧所需的交换次数
  int swapsGB = minSwapsToArrange(s, 'G');
  // 计算将 'B' 移动到左侧，'G' 移动到右侧所需的交换次数
  int swapsBG = minSwapsToArrange(s, 'B');

  // 返回两种情况下最小的交换次数
  return min(swapsGB, swapsBG);
}

int main() {
  string input;
  cout << "请输入包含 'G' 和 'B' 的字符串: ";

  cin >> input;

  int result = minSwapsToSort(input);
  cout << "最少需要的交换次数是: " << result << endl;

  return 0;
}
