#include <deque>
#include <iostream>
#include <vector>

using std::cout;
using std::deque;
using std::endl;
using std::vector;

/*
题目：
假设一个固定大小为 W 的窗口，依次划过
arr，返回每次滑出状况的最大值。例如，给定数组 arr = [4, 3, 5, 4, 3, 3, 6, 7]
和窗口大小 W = 3，返回：[5, 5, 5, 4, 6, 7]。

关键点：
1.
双端队列（deque）是整个算法的核心，允许从队列的两端进行元素的高效添加和删除。这使得算法能够在O(1)
时间内对队列的最大值进行访问和更新。
2.
队列从头到尾的顺序是元素值从大到小的顺序。这样可以确保队列的头部始终是当前窗口的最大值。

时间复杂度：虽然看起来有多个循环操作，每个元素都会被处理多次（比如添加和可能的移除），但每个元素实际上只被添加和移除一次。因此，整个算法的时间复杂度保持在
O(n)，其中 n 是数组的长度。
*/

vector<int> maxSlidingWindow(vector<int> &nums, int k) {
  deque<int>
      dq; // 存储元素的索引。存储索引允许算法通过简单地比较索引与当前窗口的边界来快速地移除过期的元素
  vector<int> max_values; // 结果数组

  for (size_t i = 0; i < nums.size(); ++i) {
    // 移除不在窗口内的索引
    if (!dq.empty() && dq.front() == static_cast<int>(i) - k) {
      dq.pop_front();
    }

    // 移除所有小于当前元素的索引
    while (!dq.empty() && nums[dq.back()] < nums[i]) {
      dq.pop_back();
    }

    // 添加当前元素索引
    dq.push_back(static_cast<int>(i));

    // 从窗口开始满足大小为 k 时，记录结果
    if (i >= static_cast<size_t>(k - 1)) {
      max_values.push_back(nums[dq.front()]);
    }
  }

  return max_values;
}

int main() {
  vector<int> nums = {4, 3, 5, 4, 3, 3, 6, 7};

  int k = 3; // 更简洁的处理方式是使用 size_t 而不是 int，在整个函数中统一使用
             // size_t 类型。这样可以避免混用 int 和
             // size_t，从而消除需要显式类型转换的需求。

  vector<int> result = maxSlidingWindow(nums, k);

  for (int num : result) {
    cout << num << " ";
  }

  cout << endl;

  return 0;
}
