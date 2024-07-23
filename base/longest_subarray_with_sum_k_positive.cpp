#include <algorithm> // 引入算法库，以确保可以使用 std::max
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::max;
using std::vector;

/*
题目：
给定一个正整数组成的无序数组 arr，给定一个正整数值 K。找到 arr
的所有子数组里，哪个子数组的累加和等于 K，并且是长度最大的，返回其长度。

解决思路：
题目中提到的子数组指的是原数组中连续的一部分。在数组和字符串的上下文中，"子数组"（subarray）或者"子序列"（substring）通常意味着连续的元素组成。这与"子序列"（subsequence）不同，后者可以包含原数组中非连续的元素，只要保持原有的顺序即可。

使用滑动窗口（又称为滑动窗口技术）是解决这种类型问题的一种非常有效的方法，尤其是当目标是找到和为固定值的连续子数组时。然而，滑动窗口方法通常适用于所有数组元素都为非负数的情况，因为这样可以保证窗口的右边界只向一个方向移动。

当数组只包含非负数时，滑动窗口方法是一个特别有效的解决方案。这是因为窗口内的和只会随着窗口的扩大而增加或随着窗口的缩小而减少，从而保证了窗口边界的单调性。这种算法属于双指针类型，其中两个指针代表窗口的起始和结束位置，这两个指针通常只向前移动。
*/

int longestSubarrayWithSumKPositive(vector<int> &arr, int K) {
  int start = 0, sum = 0, maxLength = 0;

  for (int end = 0; end < static_cast<int>(arr.size()); end++) {
    sum += arr[end]; // 将当前元素加到和中

    // 当和超过K时，逐步减去起始元素直到和小于等于K
    while (sum > K && start <= end) {
      sum -= arr[start];
      start++;
    }

    // 检查是否找到和为K的子数组
    if (sum == K) {
      maxLength = max(maxLength, end - start + 1); // 更新最大长度
    }
  }

  return maxLength;
}

int main() {
  vector<int> arr = {1, 2, 3, 2, 3, 2,
                     1, 1, 1, 1, 2}; // 示例数组，应确保只有非负数
  int K = 6;                         // 目标和

  int result = longestSubarrayWithSumKPositive(arr, K);
  cout << "Maximum length of a subarray with sum " << K << " is: " << result
       << endl;

  return 0;
}
