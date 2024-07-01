#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/*
  题目：
  给定一个二维数组 matrix，其中的值不是 0 就是 1，返回全部由 1
  组成的子矩形数量。

  思路：
  可以利用动态规划的思想来解决这个问题。我们可以通过维护一个高度数组来将每一行看作是基于直方图的底部，然后计算每个可能的以当前行为底的由
  1
  组成的子矩形的数量。虽然这个算法的实现看起来更像是数据结构（单调栈）的应用，其实在高度数组的维护过程中已经隐含了动态规划的思想。每一行的计算都是基于前一行的结果进行的更新，是一种“自底向上”的解决方案，典型地体现了动态规划的策略。

  关键点：
  1. 高度数组的维护： 我们为每列维护一个高度数组，表示当前列到当前行为止连续的 1
  的数量。如果当前元素是 0，对应的高度重置为 0；如果是 1，则在原有的基础上加 1。
  这种高度更新是动态规划的思想，将每一行视作基于前一行的直方图的底部，从而逐行更新和计算。
  2. 单调栈的使用：
  利用单调栈计算每个高度值在直方图中作为矩形高度时的最大可能宽度。栈中存储的是高度数组的索引，且保持栈内的高度值递增。
  分别从左到右和从右到左遍历高度数组，确定每个高度的左右边界。左边界是当前高度左侧第一个低于当前高度的位置，右边界是右侧第一个低于当前高度的位置。
  3.
  子矩形数量的计算：
  修改高度减少点的处理：
  当我们在计算右边界时遇到一个比当前高度小的点时，我们需要考虑这个变化点之前的所有较高点能够形成的矩形。这意味着我们需要在栈中保持一个连续的、高度递减的序列，当高度减少时，我们需要弹出栈并计算每个弹出高度能形成的矩形。

  计算矩形时考虑高度差：
  每当一个元素从栈中弹出时，计算以该元素为高的矩形，宽度为该元素到下一个栈中元素之间的距离（或到边界），高度为该元素与下一个栈中元素的高度差（或直到
  0）。

  时间复杂度：
  1. 高度数组的更新：对于每一行，更新高度数组的时间复杂度是 O(n)，其中 n
  是列数。
  2. 单调栈计算：单调栈的操作（包括左右边界的计算）对于每一行的时间复杂度也是
  O(n)，因为每个元素最多被推入和弹出栈一次。
  3. 整体时间复杂度：因为这些操作需要对每一行进行，所以总时间复杂度为
  O(mn)，其中 m 是行数。

  动态规划的应用：
  1. 高度数组的维护：
  动态规划的应用体现在每列高度的更新上。对于矩阵中的每一行，我们更新每列的高度值，这个高度值表示从当前行往上数，连续的
  1 的个数。具体来说：
      如果当前元素是 1，则当前列的高度值在上一行的基础上加 1。
      如果当前元素是 0，则当前列的高度重置为 0。

  这里的高度更新利用了之前行的高度信息来更新当前行的高度，这是典型的动态规划的思想：利用前一状态的解来构造当前状态的解。每个元素的高度是基于其上方元素的高度递推而来的。

  2. 利用递推信息优化计算：
  高度数组为计算每行可能的最大子矩形面积提供了基础，这一计算过程类似于处理一系列的直方图，每个直方图对应矩阵的一行。对每一行使用单调栈来确定每个高度的最大扩展宽度，再结合高度，即可计算出以当前行为底的所有矩形的面积。

  这种方法有效地将一个复杂的二维问题转化为多个一维问题（每一行视为一个独立的问题），通过逐行更新和计算解决，这与动态规划的分治思想和子问题的逐步求解方式非常吻合。

  bug:
  为什么结果不一样
  countRectangles可能在某些情况下过度计算了子矩形的数量，因为它没有削减重复的计数，特别是在较高的柱形之间。

  countRectangles1
  通过引入sum(width)，可能在某些配置下更准确地统计了独立的子矩形的数量，尤其是当存在多个较小宽度的矩形时。
*/

int countRectangles(vector<vector<int>> &matrix) {
  if (matrix.empty())
    return 0;
  int m = matrix.size(), n = matrix[0].size();

  vector<int> height(n, 0); // 维护每列的高度
  int totalCount = 0;

  for (int i = 0; i < m; ++i) {
    stack<int> stk; // 单调栈，用来计算每个高度对应的矩形数目
    vector<int> left(n), right(n);

    // 更新当前行的高度
    for (int j = 0; j < n; ++j) {
      height[j] = matrix[i][j] == 0 ? 0 : height[j] + 1;
    }

    // 计算左边界
    for (int j = 0; j < n; ++j) {
      while (!stk.empty() && height[stk.top()] >= height[j]) {
        stk.pop();
      }
      left[j] = stk.empty() ? -1 : stk.top();
      stk.push(j);
    }

    // 清空栈，计算右边界
    stk = stack<int>();
    for (int j = n - 1; j >= 0; --j) {
      while (!stk.empty() && height[stk.top()] >= height[j]) {
        stk.pop();
      }
      right[j] = stk.empty() ? n : stk.top();
      stk.push(j);
    }

    // 计算每列的子矩形数目
    // for (int j = 0; j < n; ++j) {
    //   if (height[j] > 0) { // 只对非零高度处理
    //     int width = right[j] - left[j] - 1;
    //     //
    //     高度数组更新时，如果左边的高度更低，我们计算高度差作为实际的高度来计算矩形
    //     int effectiveHeight =
    //         (left[j] == -1 ? height[j] : height[j] - height[left[j]]);
    //     totalCount += effectiveHeight * width;
    //   }
    // }
    for (int j = 0; j < n; ++j) {
      int width = right[j] - left[j] - 1; // 有效宽度
      totalCount += height[j] * width;    // 使用完整的高度乘以宽度
    }
  }

  return totalCount;
}

// 方法二
// 共同点：两种方法都利用单调栈来确定每个高度条左侧和右侧第一个较低的高度条，这对于确定每个高度为底的矩形的最大可能宽度至关重要。
// 区别：原先描述的算法主要用于计算以每个元素为底边的矩形的面积或数量。后来的代码片段则更关注于在弹出栈元素时计算特定配置下的矩形数量，通过计算高度差与可能的宽度的乘积。
// 目标计算的差异:
// 原算法：似乎更专注于计算每行转换成直方图后，所有可能的由 1
// 构成的子矩形的数量。
// 后来的代码：侧重于计算每个直方图元素在单调栈中的弹出时刻所代表的具体矩形的贡献。每当一个元素从栈中弹出时，它会计算这个元素能代表的最大矩形数量。
// int countFromBottom(vector<int> &height) {
//   if (height.empty())
//     return 0;
//   int nums = 0;
//   stack<int> stk;
//   // 对 height 数组的处理
//   for (size_t i = 0; i < height.size(); ++i) {
//     while (!stk.empty() && height[stk.top()] >= height[i]) {
//       int cur = stk.top();
//       stk.pop();
//       if (!stk.empty()) {
//         int left = stk.top();
//         int width = i - left - 1;
//         int down = height[left];
//         nums += (height[cur] - down) * width;
//       }
//     }
//     stk.push(i);
//   }

//   // 处理栈中剩余的元素
//   while (!stk.empty()) {
//     int cur = stk.top();
//     stk.pop();
//     int left = stk.empty() ? -1 : stk.top();
//     int width = height.size() - (stk.empty() ? 0 : (left + 1));
//     nums += height[cur] * width;
//   }
//   return nums;
// }

// sum 函数的使用是为了计算在给定的宽度范围内，可以形成的所有可能的子矩形的数量
// 例如，如果宽度为 3，那么可以有：

// 宽度为 1 的矩形 3 个
// 宽度为 2 的矩形 2 个
// 宽度为 3 的矩形 1 个
int sum(int n) { return (n * (n + 1)) / 2; }

int countFromBottom(std::vector<int> &height) {
  if (height.empty())
    return 0;
  int nums = 0;
  std::stack<int> stk;
  int n = height.size();

  for (int i = 0; i < n; ++i) {
    while (!stk.empty() && height[stk.top()] >= height[i]) {
      int cur = stk.top();
      stk.pop();
      if (!stk.empty()) {
        int left = stk.top();
        int width = i - left - 1;
        int down = max(left == -1 ? 0 : height[left], height[i]);
        nums += (height[cur] - down) * sum(width);
      }
    }
    stk.push(i);
  }

  // 处理栈中剩余的元素
  while (!stk.empty()) {
    int cur = stk.top();
    stk.pop();
    int left = stk.empty() ? -1 : stk.top();
    int width = height.size() - (stk.empty() ? 0 : (left + 1));
    int down = left == -1 ? 0 : height[left];
    nums += (height[cur] - down) * sum(width);
  }

  return nums;
}

int countRectangles1(vector<vector<int>> &matrix) {
  if (matrix.empty())
    return 0;
  int m = matrix.size(), n = matrix[0].size();

  vector<int> height(n, 0);
  int totalCount = 0;

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      height[j] = matrix[i][j] == 0 ? 0 : height[j] + 1;
    }
    totalCount += countFromBottom(height);
  }

  return totalCount;
}

int main() {
  vector<vector<int>> matrix = {{1, 0, 1}, {1, 1, 1}, {0, 1, 1}};

  cout << "Total count of rectangles composed of 1s: "
       << countRectangles(matrix) << endl;

  return 0;
}
