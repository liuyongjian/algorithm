#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/*
  题目：
  给定一个二维数组 matrix，其中的值不是 0 就是 1，返回全部由 1
  组成的最大子矩形，其内部有多少个 1。

  思路：
  为了找到一个二维矩阵中全部由 1
  组成的最大子矩形的面积，我们可以借鉴“直方图中最大矩形面积”的算法。核心思想是将每一行视为一个基于直方图的底部，并计算以该行为底的矩形的最大面积。我们可以逐行构建直方图，并用一个栈帮助我们在
  O(n) 时间内找到每个柱形图中最大的矩形面积

  关键点：
  1. 直方图转换：每一行的直方图是由当前行的 1
  的个数加上之前行（如果之前行在相应位置是
  1）的高度得到的。这样，如果某个位置的元素是 '0'，则直方图的高度在该位置重置为
  0；如果是 '1'，则增加该位置的高度。
  2.
  单调栈应用：为了计算每一行形成的直方图的最大矩形面积，我们使用单调栈。单调栈帮助我们快速找到每个柱子左右两边第一个低于它的柱子的索引，这是计算矩形面积所必需的。
  3. 面积计算：
  对于直方图中的每一个柱形，根据其高度和通过单调栈找到的宽度（即右边界和左边界之差减一）计算面积，并持续更新最大面积。
  4. 迭代更新： 遍历每一行时更新直方图，并计算每次更新后的最大矩形面积。

  时间复杂度：
  1. 构建直方图：对于每一行的每一个元素，更新直方图的高度需要 O(1)
  时间，因此对于 m 行 n 列的矩阵，整个直方图的构建需要 O(mn) 时间。
  2.
  单调栈计算面积：每行直方图计算最大矩形面积时，每个柱子在单调栈中被处理（即入栈和出栈）的总次数不超过
  2 次，所以每行的处理时间是 O(n)。对于 m 行，这部分的总时间也是 O(mn)。
*/

// 计算直方图中最大矩形的面积
int largestRectangleArea(vector<int> &heights) {
  int n = heights.size();
  vector<int> left(n), right(n, n);
  stack<int> mono_stack;

  for (int i = 0; i < n; ++i) {
    while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) {
      mono_stack.pop();
    }
    left[i] = mono_stack.empty() ? -1 : mono_stack.top();
    mono_stack.push(i);
  }

  mono_stack = stack<int>();

  for (int i = n - 1; i >= 0; --i) {
    while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) {
      mono_stack.pop();
    }
    right[i] = mono_stack.empty() ? n : mono_stack.top();
    mono_stack.push(i);
  }

  int maxArea = 0;
  for (int i = 0; i < n; ++i) {
    maxArea = max(maxArea, heights[i] * (right[i] - left[i] - 1));
  }

  return maxArea;
}

// 主函数，用来求二维矩阵中由1组成的最大矩形的面积
int maximalRectangle(vector<vector<char>> &matrix) {
  if (matrix.empty() || matrix[0].empty())
    return 0;

  int maxArea = 0;
  vector<int> heights(matrix[0].size(), 0); // 初始化直方图高度数组

  for (auto &row : matrix) {
    for (size_t j = 0; j < matrix[0].size(); ++j) {
      // 更新每列的高度，如果是1则增加，否则重置为0
      heights[j] = row[j] == '1' ? heights[j] + 1 : 0;
    }

    // 使用直方图中最大矩形的面积算法
    maxArea = max(maxArea, largestRectangleArea(heights));
  }

  return maxArea;
}

int main() {
  vector<vector<char>> matrix = {{'1', '0', '1', '0', '0'},
                                 {'1', '0', '1', '1', '1'},
                                 {'1', '1', '1', '1', '1'},
                                 {'1', '0', '0', '1', '0'}};

  cout << "Maximum area of a rectangle composed of 1s: "
       << maximalRectangle(matrix) << endl;

  return 0;
}
