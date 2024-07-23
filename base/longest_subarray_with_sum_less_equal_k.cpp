#include <deque>
#include <iostream>
#include <limits> // 引入用于数值限制的库
#include <map>
#include <vector>

using namespace std;

/*
题目：
给定一个整数数组 arr，数组中的值可能是正数、负数或者0。再给定一个整数值 K。找到
arr 的所有子数组中，哪个子数组的累加和小于等于 K，并且是长度最大的，返回其长度。

要求：
时间复杂度O(n)

算法思路：
1. 预计算最小累加和和其索引
反向遍历数组：从数组的最后一个元素开始，向前遍历。这个步骤的目的是为了预先计算从每个位置
i到数组末尾可能的最小累加和及其结束索引。
这样做的好处是，当我们需要确定从任何位置开始向后扩展的子数组是否满足条件时，可以直接查看这个预计算的信息，而不需要重新计算累加和。

计算逻辑：对于每个位置 i，我们检查其后一个位置 i+1 的 minSum。如果 minSum[i+1]
是负数，这意味着将 i 到 i+1 的累加和加上 arr[i]
可能会得到一个更小的累加和，因此我们将这个累加和以及对应的索引存储在 minSum[i]
和 minSumEndIndex[i] 中。如果 minSum[i+1] 不是负数，minSum[i] 就简单地是
arr[i]，并且对应的索引就是 i。

2. 查找满足条件的最长子数组
正向遍历数组：从数组的第一个元素开始，向后遍历，尝试构建从当前位置开始的所有可能的子数组。

利用预计算的结果：对于每个起始位置 i，使用之前计算的 minSum 和 minSumEndIndex
来快速跳转至子数组的最远右边界，同时累加和小于等于 K。如果添加下一个 minSum
会导致总和超过 K，则停止当前的扩展，并检查当前的长度是否是最长的。

关键点：
这种方法利用了动态规划的思想，预先计算出从每个索引 i
到数组末尾的最小累积和以及这个累积和的最右边界，然后用这些预计算的结果来快速求解问题。

利用了数组的反向遍历来优化累积和的计算，并通过正向遍历结合预先计算的结果快速找到解。这是一种在动态规划框架下使用空间换时间的策略，非常适合解决复杂度较高的问题，提高效率。
 */
int longestSubarrayWithSumLessEqualK(vector<int> &arr, int K) {
  int n = arr.size();

  vector<int> segmentMinSums(n, 0); // 存储从每个索引开始的段的最小累加和
  vector<int> segmentEndIndices(n,
                                0); // 存储产生最小累加和的子数组的结束位置索引

  // 从后向前计算最小累加和及其索引
  segmentMinSums[n - 1] = arr[n - 1];
  segmentEndIndices[n - 1] = n - 1;

  // 从后向前计算最小累加和及其索引
  for (int i = n - 2; i >= 0; --i) {
    // 如果当前元素加上后一个元素的最小累加和小于0，则更新当前元素的最小累加和
    if (segmentMinSums[i + 1] < 0) {
      segmentMinSums[i] =
          arr[i] + segmentMinSums[i + 1]; // 当前元素和后续段的最小累加和

      segmentEndIndices[i] =
          segmentEndIndices[i + 1]; // 更新当前段的结束索引为后续段的结束索引
    } else {
      segmentMinSums[i] = arr[i]; // 当前元素本身即为最小累加和
      segmentEndIndices[i] = i;   // 当前段的结束索引即为当前索引
    }
  }

  int maxLength = 0;
  int sum = 0;
  // i 是每次尝试寻找满足条件子数组的起始点
  int i = 0;
  while (i < n) {
    sum = 0;
    // j 是用来根据预计算的 segmentEndIndices
    // 进行跳跃，尝试扩展子数组到尽可能远的位置。
    int j = i;

    while (j < n) {
      if (sum + segmentMinSums[j] > K)
        break;

      sum += segmentMinSums[j];

      maxLength = max(maxLength, segmentEndIndices[j] - i + 1);

      j = segmentEndIndices[j] + 1;
    }

    i = j; // 当内层循环结束，`i` 直接跳转到 `j`，避免重复检查已经计算过的区间
  }

  return maxLength;
}

int main() {
  vector<int> arr = {1, 2, -1, 5, -2, 3}; // 示例数组
  int K = 5;                              // 目标累加和上限

  int result = longestSubarrayWithSumLessEqualK(arr, K);
  cout << "累加和小于等于 " << K << " 的最长子数组长度为: " << result << endl;

  return 0;
}
