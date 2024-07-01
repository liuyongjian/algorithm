#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/*
  题目：
  给定一个只包含正整数的数组arr，对任意子数组sub，计算(sub的累加和)×(sub中的最小值)。求所有子数组中，这个值的最大值是多少？

  关键点：
  1. 前缀和数组：通过构建一个前缀和数组来快速计算任何子数组的累加和。前缀和数组
  prefixSum[i] 表示数组中从第一个元素到第 i-1
  个元素的累加和。利用前缀和数组，可以在常数时间内计算任何子数组的累加和。
  2.
  单调栈的应用：使用单调栈可以有效地找到每个元素作为子数组中最小值时能向左和向右扩展到的边界。单调栈维持元素索引的一个递增顺序，从而当遍历到新的元素时，可以迅速找到左侧和右侧第一个小于当前元素的位置。

  时间复杂度：
  1. 前缀和的计算：时间复杂度为O(n)，其中 n 是数组的长度。
  2.
  单调栈的构建和元素边界的计算：虽然涉及两次遍历（一次从左到右计算左边界，一次从右到左计算右边界），但每个元素只被压栈和出栈一次，因此总的时间复杂度也是O(n)。
  3. 最大值的计算：需要对每个元素计算其对应的值，也是O(n)
*/

long long maxSumOfSubarrays(const vector<int> &arr) {
  int n = arr.size();
  vector<long long> prefixSum(n + 1, 0);
  // 计算前缀和
  for (int i = 0; i < n; ++i) {
    prefixSum[i + 1] = prefixSum[i] + arr[i];
  }

  // 用于记录每个元素作为最小值时能扩展到的左右边界
  vector<int> left(n), right(n);
  stack<int> st;

  // 计算左边界
  for (int i = 0; i < n; ++i) {
    while (!st.empty() && arr[st.top()] > arr[i]) {
      st.pop();
    }
    left[i] = st.empty() ? 0 : st.top() + 1;
    st.push(i);
  }

  // 清空栈，用于计算右边界
  while (!st.empty())
    st.pop();

  // 计算右边界
  for (int i = n - 1; i >= 0; --i) {
    // 在确定右边界时，如果当前元素的值小于或等于栈顶元素的值，那么栈顶元素将被弹出。这是因为栈顶元素作为子数组的最小值时，其区间应该终止于当前元素的前一个位置。
    // 即使是相等的元素也应该被视为一个新的起点，因此它们的区间不会重叠。这样可以保证每个元素作为子数组最小值时，其对应的累加和乘以最小值的计算是准确的。
    while (!st.empty() && arr[st.top()] >= arr[i]) {
      st.pop();
    }
    right[i] = st.empty() ? n : st.top();
    st.push(i);
  }

  // 计算最大值
  long long maxResult = 0;
  for (int i = 0; i < n; ++i) {
    // 有了每个元素的左右边界，就可以通过前缀和数组快速计算出以当前元素为最小值的所有子数组的累加和
    long long sum = prefixSum[right[i]] - prefixSum[left[i]];
    maxResult = max(maxResult, sum * arr[i]);
  }

  return maxResult;
}

int main() {
  vector<int> arr = {1, 3, 2, 5, 6}; // 示例数组
  cout << "Maximum value: " << maxSumOfSubarrays(arr) << endl;
  return 0;
}
