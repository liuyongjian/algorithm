#include <deque>
#include <iostream>
#include <vector>

using std::cout;
using std::deque;
using std::endl;
using std::max;
using std::vector;

/*
题目：
给定一个整型数组 arr，和一个整型数 num。某个 arr 中的子数组 sub
如果想达标，必须满足：sub 中最大值 - sub 中最小值 <= num。返回 arr
中达标子数组的数量。

关键点：数据结构（双端队列）和算法（滑动窗口技术）
1. 双端队列的使用：使用两个双端队列（maxDeque 和
minDeque）来分别维护当前子数组内的最大值和最小值的索引。这使得我们可以在 O(1)
时间内访问当前子数组的最大值和最小值。
2. 动态窗口调整：通过两个指针（left 和 right）定义当前子数组的范围。right
指针负责扩展窗口，而 left
指针根据需要动态调整以保证子数组满足条件（最大值与最小值之差不超过 num）。

时间复杂度：
O(n)：虽然算法涉及嵌套的循环，每个元素都会被考虑添加到 maxDeque 和 minDeque
中，但每个元素仅在其首次到达时被添加，并在其不再有效时被移除。因此，每个元素最多被各个队列操作一次（添加和移除各一次）。
*/

int countSubarrays(const vector<int> &arr, int num) {
  int n = arr.size();
  int count = 0;
  deque<int> maxDeque, minDeque;
  int left = 0;

  for (int right = 0; right < n; ++right) {
    // 维护最大值队列
    while (!maxDeque.empty() && arr[maxDeque.back()] < arr[right]) {
      maxDeque.pop_back();
    }
    maxDeque.push_back(right);

    // 维护最小值队列
    while (!minDeque.empty() && arr[minDeque.back()] > arr[right]) {
      minDeque.pop_back();
    }
    minDeque.push_back(right);

    // 检查当前子数组是否满足条件，持续执行直到当前窗口（子数组）的最大值与最小值之差不超过
    // num
    while (arr[maxDeque.front()] - arr[minDeque.front()] > num) {
      // 选择两者中的较大索引，即是选择了最新（最右侧）影响窗口差值条件的元素。
      // 因为索引较大意味着较新，这反映了在动态窗口中后进的元素对当前问题的直接影响。
      // 由于窗口是动态移动的，最新（最右侧）的元素是最后进入窗口的，因此它们对当前窗口是否满足条件具有直接的影响。
      // 选择移除最旧的最大值或最小值还有一个理由，那就是保持窗口的灵活性和尽可能大的覆盖范围。
      // 新加入的元素可能会在未来的窗口移动中成为关键因素，因此在不影响条件的前提下尽量保留新元素。
      left = max(maxDeque.front(), minDeque.front()) + 1;

      // 如果 maxDeque 的队首元素（即当前最大值的索引）已不再窗口内（即小于新的
      // left），则从队首移除。
      if (maxDeque.front() < left)
        maxDeque.pop_front();

      // 如果 minDeque
      // 的队首元素（即当前最小值的索引）已不再窗口内，则从队首移除。
      if (minDeque.front() < left)
        minDeque.pop_front();
    }

    // 计算达标的子数组数量
    count += right - left + 1;
  }

  return count;
}

int main() {
  vector<int> arr = {1, 3, 6, 4, 1, 2};

  int num = 3;

  cout << "Count of subarrays: " << countSubarrays(arr, num) << endl;

  return 0;
}
