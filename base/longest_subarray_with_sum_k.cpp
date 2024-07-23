#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/*
题目：
给定一个由整数构成的无序数组 arr，其元素值可能为正、负或零。再给定一个整数值
K，找出 arr 的所有子数组中，累加和等于 K
的子数组中长度最大的子数组，并返回其长度。

实现细节：
为什么设置 prefixSumMap[0] = -1？

初始前缀和为0：
当开始遍历数组时，尚未累加任何元素，因此前缀和初始化为0。
在这种情况下，如果某个位置的前缀和正好等于
k，意味着从数组起始位置到这个位置的子数组的和等于 k。

处理特殊情况：
假设数组 arr 的前几个元素的和刚好等于 k，例如 arr = {k,
...}，那么从数组的第一个元素到该位置的和就是 k。 如果不设置 prefixSumMap[0] =
-1，那么在这种情况下就无法正确计算从起始位置到该位置的子数组长度。 通过设置
prefixSumMap[0] = -1，当我们在 i 位置找到当前前缀和 sum 等于 k
时，可以直接计算出子数组的长度为 i - (-1) = i + 1。
 */

int longestSubarrayWithSumK(vector<int> &arr, int k) {
  // 使用一个哈希表来存储前缀和及其第一次出现的索引
  unordered_map<int, int> prefixSumMap;
  // 初始化前缀和为0的位置，这对处理从数组开头到当前位置的子数组和为 k 是必要的
  prefixSumMap[0] = -1;

  int maxLength = 0;
  int sum = 0;

  // 遍历数组，计算每个位置的前缀和
  for (int i = 0; i < static_cast<int>(arr.size()); ++i) {
    sum += arr[i];

    // 如果当前前缀和减去 k 存在于哈希表中，说明找到了一个和为 k 的子数组
    if (prefixSumMap.find(sum - k) != prefixSumMap.end()) {
      // 更新最大长度
      maxLength = max(maxLength, i - prefixSumMap[sum - k]);
    }

    // 如果当前的前缀和还没有存储过，那么存储它和对应的索引
    if (prefixSumMap.find(sum) == prefixSumMap.end()) {
      prefixSumMap[sum] = i;
    }
  }

  return maxLength;
}

int main() {
  vector<int> arr = {1, -1, 5, -2, 3};
  int k = 3;
  int result = longestSubarrayWithSumK(arr, k);
  cout << "The length of the longest subarray with sum " << k
       << " is: " << result << endl;
  return 0;
}
