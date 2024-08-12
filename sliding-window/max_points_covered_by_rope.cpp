#include <iostream>
#include <vector>

using namespace std;

/*
题目：
给定一个有序数组 arr，其中每个元素代表在 X 轴上的一个点的坐标。再给定一个正整数
K，表示绳子的长度。要求返回绳子最多可以覆盖的点数，即使绳子的边缘处覆盖住点也算作覆盖。

思路：
维持一个窗口，确保窗口内的点的最大距离不超过绳子的长度 K。
每次窗口向右滑动时，尝试扩展窗口的右边界，直到窗口内的点的最大距离超过 K 为止，
然后记录当前窗口的大小，并尝试通过移动窗口的左边界来缩小窗口。最终，我们记录下窗口大小的最大值即可。

关键点：
1. 有序数组：输入数组 arr是有序的，这是算法能够有效工作的前提条件。
由于数组有序，可以保证任何连续子数组的最小和最大值的差即为该子数组的范围。
2. 滑动窗口维护：通过使用两个指针（left 和right）表示窗口的左右边界。
这两个指针初始都位于数组的开始位置，并根据条件逐步向右移动。
3. 窗口调整：当窗口的大小（即 arr[right] - arr[left]）超过绳子长度 K
时，左边界left 需要向右移动以缩小窗口，直到窗口大小再次符合要求。 右边界
right持续向右移动扩大窗口以探索可能的最大覆盖点数。
4.实时更新最大覆盖点数：每当右边界移动后，都会计算当前窗口内的点数，并更新最大覆盖点数
maxPoints。

时间复杂度：
这个算法的时间复杂度是线性的，即 O(n)，其中 n 是数组 arr的长度。
尽管算法中有一个嵌套的循环（在 while 内部），但每个元素在整个算法中只被访问两次
（一次被 right 指针访问，一次可能被
left指针访问），因此总的操作次数仍然是线性的。
*/

int maxPointsCoveredByRope(const vector<int> &arr, int K) {
  int maxPoints = 0;
  int left = 0; // 左边界指针

  for (int right = 0; right < static_cast<int>(arr.size()); ++right) {
    // 扩展右边界直到超出绳子长度 K
    while (arr[right] - arr[left] > K) {
      left++; // 移动左边界以尝试缩小区间
    }

    // 计算当前覆盖的点数
    maxPoints = max(maxPoints, right - left + 1);
  }

  return maxPoints;
}

int main() {
  vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int K = 4;

  cout << "Maximum points covered by a rope of length " << K << ": "
       << maxPointsCoveredByRope(arr, K) << endl;

  return 0;
}
