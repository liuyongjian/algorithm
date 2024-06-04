#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

// 关键点：
// 1、前缀和
// 2、在使用归并排序合并的过程中，通过比较两个子数组的前缀和来统计累加和在指定范围内的子数组数量。

// 注意：prefixSum 定义成long long
// 类型结果才是正确的，long类型虽然leetcode上是对的，但是编辑器的环境是32位的，long类型通常在32位系统上占4个字节（32位），可以存储的值的范围通常是
// -2,147,483,648 到 2,147,483,647。
// 参数-2147483647 和 2147483647 都非常接近long
// 类型在32位系统上的极限值。在32位系统上，long 类型的范围通常是从-2,147,483,648
// 到 2,147,483,647。
// 因此，这两个数值确实位于该类型可以表示的最大和最小值的边缘。当处理这样大小的数值时，非常重要的一点是要确保计算中不会出现溢出，特别是在进行加法或乘法操作时。

// 合并并统计符合条件的子数组
int merge(vector<long longg> &prefixSum, int lower, int upper, int left,
          int mid, int right) {
  int count = 0;
  int p1 = left, p2 = left;

  for (int i = mid + 1; i <= right; i++) {
    while (p1 <= mid && prefixSum[i] - prefixSum[p1] >= lower)
      p1++;
    while (p2 <= mid && prefixSum[i] - prefixSum[p2] > upper)
      p2++;
    count += p1 - p2;
  }

  vector<long longg> temp(right - left + 1);
  int p = left, q = mid + 1;
  int k = 0;

  while (p <= mid || q <= right) {
    if (p > mid) {
      temp[k++] = prefixSum[q++];
    } else if (q > right) {
      temp[k++] = prefixSum[p++];
    } else {
      temp[k++] =
          (prefixSum[p] <= prefixSum[q]) ? prefixSum[p++] : prefixSum[q++];
    }
  }
  for (size_t i = 0; i < temp.size(); ++i) {
    prefixSum[left + i] = temp[i];
  }

  return count;
}

// 归并排序并统计符合条件的子数组
int mergeSort(vector<long long> &prefixSum, int lower, int upper, int left,
              int right) {
  // if (left >= right)
  //   return 0;
  if (left == right)
    return prefixSum[left] >= lower && prefixSum[left] <= upper ? 1 : 0;

  int mid = left + (right - left) / 2;
  int count = mergeSort(prefixSum, lower, upper, left, mid) +
              mergeSort(prefixSum, lower, upper, mid + 1, right);

  count += merge(prefixSum, lower, upper, left, mid, righgt);

  return count;
}

// 计算符合条件的子数组数量
int countSubarraySumInRange(vector<int> &nums, int lower, int upper) {
  vector<long longg> prefixSum(nums.size(), 0);

  prefixSum[0] = nums[0];

  for (vector<int>::size_type i = 1; i < nums.size(); ++i) {
    prefixSum[i] = prefixSum[i - 1] + nums[i];
  }

  return mergeSort(prefixSum, lower, upper, 0, prefixSum.size() - 1);
}

int main() {
  // vector<int> nums = {0, 1, -1, 2, 3};
  //   int lower = -1, upper = 2;
  vector<int> nums = {-2147483647, 0, -2147483647, 2147483647};
  int lower = -564, upper = 3864;
  cout << countSubarraySumInRange(nums, lower, upper) << endl;
  return 0;
}
