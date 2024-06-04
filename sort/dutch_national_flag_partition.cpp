#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::swap;
using std::vector;

// 荷兰国旗问题：
// 通常用来展示如何通过简单的算法有效地解决分割元素的问题。它源自于将红、白、蓝三种颜色的物体分开的需求，其名称来源于荷兰国旗包含这三种颜色。这个问题可以用三向切分快速排序（也称为Dutch
// National Flag Problem，由Edsger W.
// Dijkstra提出）来解决，这种方法可以在单次遍历中完成排序。

// 关键点：
// 1. 三个指针的运用：使用三个指针，low、mid和high，来进行元素的分割。
// 2. 元素交换：通过与特定值（如中间值）的比较和元素的交换来重新排列元素。
// 3. 单次遍历：整个数组只需要遍历一次。

// 荷兰国旗问题的另一个变种:
// 可以选择数组的最后一个元素 nums[R]
// 作为划分值，然后将数组 nums[L...R]
// 分成小于、等于和大于这个划分值的三部分。这种做法类似于快速排序中的划分过程，但是这里处理三个区段而非两个。
// 注意:
// 数组中的数字不是全局排序的，是相对于枢轴值分区的。这正是荷兰国旗问题所要达成的目标。

void dutchNationalFlagPartition(vector<int> &nums, int L, int R) {
  int pivot = nums[R]; // 选择最后一个元素作为划分值
  int low = L;
  int mid = L;
  int high = R - 1;

  while (mid <= high) {
    if (nums[mid] < pivot) {
      swap(nums[low++], nums[mid++]);
    } else if (nums[mid] > pivot) {
      swap(nums[mid], nums[high--]);
    } else {
      mid++;
    }
  }
  swap(nums[mid], nums[R]); // 将划分值交换到中间
}

int main() {
  vector<int> nums = {2, 0, 5, 2, 1, 4, 3};
  int L = 0;
  int R = nums.size() - 1;
  dutchNationalFlagPartition(nums, L, R);

  for (int num : nums) {
    cout << num << " ";
  }
  return 0;
}
