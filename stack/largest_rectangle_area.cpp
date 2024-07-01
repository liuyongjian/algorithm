#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/*
  题目：
  给定一个非负数组 arr，表示直方图，返回直方图的最大长方形面积。

  关键点：
  1. 单调栈结构：单调栈是解决这类问题的核心工具。它帮助我们在 O(n)
  时间内找到每个柱子左右两边第一个低于它的柱子的索引。栈内保持的是柱子的索引，且栈中的柱子高度是递增的。这样可以确保对于栈中的任意柱子，其右边的柱子（在高度上）无法向左扩展超过该柱子。
  2.
  最大面积的计算：一旦有了每个柱子的左右边界，就可以计算以每个柱子为高的矩形的面积，即
  高度 * (右边界 - 左边界 - 1)。遍历所有柱子，更新并维护最大面积值。

  时间复杂度：
  1.
  单次遍历的栈操作：虽然算法包括两次遍历（一次从左至右，一次从右至左），但每个柱子在每次遍历中仅被推入和弹出栈一次。因此，单调栈操作的时间复杂度是
  O(n)。
  2.
  总体时间复杂度：由于每个柱子被处理的时间是常数级别的，加上前缀和的计算，整体算法的时间复杂度保持在
  O(n)，其中 n 是直方图中柱子的数量。
*/

int largestRectangleArea(vector<int> &heights) {
  int n = heights.size();
  vector<int> left(n), right(n, n);

  stack<int> mono_stack;
  // 找到每个柱子左边第一个比它矮的柱子的索引
  for (int i = 0; i < n; ++i) {
    while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) {
      mono_stack.pop();
    }
    left[i] = mono_stack.empty() ? -1 : mono_stack.top();
    mono_stack.push(i);
  }

  // 清空栈，用于计算右边界
  mono_stack = stack<int>();
  // 找到每个柱子右边第一个比它矮的柱子的索引
  for (int i = n - 1; i >= 0; --i) {
    while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) {
      mono_stack.pop();
    }
    right[i] = mono_stack.empty() ? n : mono_stack.top();
    mono_stack.push(i);
  }

  // 计算最大面积
  int maxArea = 0;
  for (int i = 0; i < n; ++i) {
    maxArea = max(maxArea, heights[i] * (right[i] - left[i] - 1));
  }

  return maxArea;
}

int main() {
  vector<int> heights = {2, 1, 5, 6, 2, 3}; // 示例直方图
  cout << "The largest rectangle area is: " << largestRectangleArea(heights)
       << endl;
  return 0;
}
