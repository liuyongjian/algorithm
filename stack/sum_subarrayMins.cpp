#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/*
  题目：
  给定一个数组 arr，返回所有子数组最小值的累加和。

  关键点：
  1.
  高度数组的维护：对于给定的二维矩阵，我们维护一个称为“高度数组”的一维数组。该数组的每个元素代表从当前行向上，连续的
  1 的数量。 高度数组的更新是动态规划的思想的一种体现。如果当前行的某一列是
  1，那么该列的高度值在原来的基础上加 1；如果是 0，则重置为 0。
  2.
  单调栈的使用：利用单调栈来确定每个元素作为最小值可以扩展的子数组的范围。单调栈存储元素的索引，并保持栈中元素对应的高度递增。
  通过单调栈计算每个元素的左右边界。左边界是左侧第一个小于当前元素的位置，右边界是右侧第一个小于当前元素的位置
  3.
  重复值的处理策略：
  在处理具有重复值的数组时，计算所有子数组的最小值的累加和的单调栈策略需要适当的调整以处理重复元素。在单调栈的常规实现中，对于重复值的处理方式将决定左右边界的计算，这影响到如何确定一个元素是其所在子数组的最小值的范围。
  1. 非严格递减栈：
  使用一个非严格递减的单调栈可以帮助处理重复值。在这种实现中，当遇到与栈顶相等的元素时，你可以选择继续将这些元素的索引推入栈中。
  这意味着对于值相同的元素，最左边的一个元素将决定右边所有相同元素的左边界，而最右边的一个元素将被最后一个相等或更小的元素决定其右边界。
  2. 边界的计算：
  当栈中包含重复元素的索引时，左边界（left[i]）对于一组相同的值，是这组值中最左边元素的前一个小于它的索引。
  右边界（right[i]）是最右边的相同值的后一个小于它的索引。

  时间复杂度：
  1. 高度数组的更新：对于每一行，更新高度数组的时间复杂度是 O(n)，其中 n
  是列数。
  2. 单调栈计算：单调栈的操作（包括左右边界的计算）对于每一行的时间复杂度也是
  O(n)，因为每个元素最多被推入和弹出栈一次。
  整体时间复杂度：因为这些操作需要对每一行进行，所以总时间复杂度为 O(mn)，其中 m
  是行数。

  执行步骤：
  让我们逐个检查每个元素对子数组最小值和的贡献：
  1. 对于元素 1 (索引 1)：
  子数组：[1], [3, 1], [1, 2], [3, 1, 2], [1, 2, 4], [3, 1, 2, 4]
  这些子数组中，1 总是最小的。
  贡献: 1 被包含在 6 个子数组中，贡献是 1 * 6 = 6
  2. 对于元素 2 (索引 2)：
  子数组：[2], [2, 4]
  在这些子数组中，2 总是最小的。
  贡献: 2 被包含在 2 个子数组中，贡献是 2 * 2 = 4
  3. 对于元素 3 (索引 0)：
  子数组：[3]
  在这个子数组中，3 是最小的。
  贡献: 3 被包含在 1 个子数组中，贡献是 3 * 1 = 3
  4. 对于元素 4 (索引 3)：
  子数组：[4]
  在这个子数组中，4 是最小的。
  贡献: 4 被包含在 1 个子数组中，贡献是 4 * 1 = 4

  将这些贡献加起来：6 + 4 + 3 + 4 = 17。
*/

// 计算所有子数组的最小值的累加和
int sumSubarrayMins(vector<int> &arr) {
  int n = arr.size();
  vector<int> left(n), right(n);
  stack<int> stk;

  // 计算每个元素的左边界
  for (int i = 0; i < n; ++i) {
    while (!stk.empty() && arr[stk.top()] > arr[i]) {
      stk.pop();
    }
    left[i] = stk.empty() ? -1 : stk.top();
    stk.push(i);
  }

  // 清空栈以用于计算右边界
  while (!stk.empty())
    stk.pop();

  // 计算每个元素的右边界
  for (int i = n - 1; i >= 0; --i) {
    while (!stk.empty() && arr[stk.top()] >= arr[i]) {
      stk.pop();
    }
    right[i] = stk.empty() ? n : stk.top();
    stk.push(i);
  }

  // 计算所有子数组最小值的累加和
  long sum = 0;
  const long mod = 1e9 + 7; // 防止溢出，按题目要求可能需要取模
  for (int i = 0; i < n; ++i) {
    long leftCount = i - left[i];
    long rightCount = right[i] - i;
    sum = (sum + static_cast<long>(arr[i]) * leftCount * rightCount) % mod;
  }

  return sum;
}

int main() {
  vector<int> arr = {3, 1, 2, 4};
  cout << "Sum of Subarray Minimums: " << sumSubarrayMins(arr) << endl;
  return 0;
}
