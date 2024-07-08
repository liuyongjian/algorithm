#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

// 函数原型声明
int select(vector<int> &nums, int left, int right, int k);
int partition(vector<int> &nums, int left, int right, int pivotIndex);
int findMedianOfMedians(vector<int> &nums, int left, int right);
int medianOfFive(vector<int> &nums, int left, int right);

// BFPRT选择函数，递归选择第k小的元素
int select(vector<int> &nums, int left, int right, int k) {
  if (left == right) {
    return nums[left];
  }

  int pivotIndex = findMedianOfMedians(nums, left, right);
  pivotIndex = partition(nums, left, right, pivotIndex);

  // 如果 k 正好等于 pivotIndex，找到了第k小的元素，直接返回。
  if (k == pivotIndex) {
    return nums[k];
  } else if (k < pivotIndex) {
    // 如果 k 小于 pivotIndex，递归地在左侧数组中查找第k小元素。
    return select(nums, left, pivotIndex - 1, k);
  } else {
    // 如果 k 大于 pivotIndex，递归地在右侧数组中查找第k小元素。
    return select(nums, pivotIndex + 1, right, k);
  }
}

// 数组划分函数，基于pivotIndex的值对数组进行划分
/*
例子：
nums = [9, 6, 3, 8, 5, 2, 7, 4, 1]
left = 0
right = 8
pivotIndex = 4  // 即选择 '5' 作为枢轴值

执行逻辑：
1. 交换枢轴和最右端元素
nums = [9, 6, 3, 8, 1, 2, 7, 4, 5] // 5 被交换到了末尾

2. 遍历和交换
i = 0: nums[i] = 9, 不小于5, 不移动。

i = 1: nums[i] = 6, 不小于5, 不移动。

i = 2: nums[i] = 3, 小于5, 交换nums[0]和nums[2],
数组变为 [3, 6, 9, 8, 1, 2, 7, 4, 5], storeIndex 变为 1。

i = 3: nums[i] = 8, 不小于5, 不移动。

i = 4: nums[i] = 1, 小于5, 交换nums[1]和nums[4],
数组变为 [3, 1, 9, 8, 6, 2, 7, 4, 5], storeIndex 变为 2。

i = 5: nums[i] = 2, 小于5, 交换nums[2]和nums[5],
数组变为 [3, 1, 2, 8, 6, 9, 7, 4, 5], storeIndex 变为 3。

i = 6: nums[i] = 7, 不小于5, 不移动。

i = 7: nums[i] = 4, 小于5, 交换nums[3]和nums[7],
数组变为 [3, 1, 2, 4, 6, 9, 7, 8, 5], storeIndex 变为 4。

3. 恢复枢轴位置
将枢轴元素（现在位于 right 即索引 8）与 storeIndex 指向的位置（索引 4）交换
nums = [3, 1, 2, 4, 5, 9, 7, 8, 6]
*/
int partition(vector<int> &nums, int left, int right, int pivotIndex) {
  int pivotValue = nums[pivotIndex];
  // 将枢轴元素与最右端元素交换，这样枢轴就移至数组末尾，方便后续操作。
  swap(nums[pivotIndex], nums[right]); // 把pivot移到末尾

  // 这个索引用来跟踪小于枢轴值的元素应该存放的位置。
  int storeIndex = left;

  // 遍历数组的其余部分，将所有小于枢轴值的元素移到数组的左侧。
  for (int i = left; i < right; i++) {
    if (nums[i] < pivotValue) {
      swap(nums[i], nums[storeIndex]);
      storeIndex++;
    }
  }

  // 遍历完成后，将枢轴元素放回到它正确的位置（所有左侧元素都比它小，右侧都不小于它），并返回枢轴的索引。
  swap(nums[storeIndex], nums[right]); // 把pivot移回正确的位置

  return storeIndex;
}

// 寻找中位数的中位数
int findMedianOfMedians(vector<int> &nums, int left, int right) {
  if (left == right) {
    return left; // 只有一个元素
  }

  int numElements = right - left + 1;
  int medianCount = (numElements + 4) / 5; // 计算中位数的数量

  for (int i = 0; i < medianCount; i++) {
    int subLeft = left + i * 5;
    int subRight = subLeft + 4;
    if (subRight > right)
      subRight = right;

    // 对每组使用 medianOfFive 函数找到中位数。
    int median = medianOfFive(nums, subLeft, subRight);
    swap(nums[left + i], nums[median]);
  }

  // 递归寻找中位数的中位数
  return select(nums, left, left + medianCount - 1, medianCount / 2);
}

// 找到五个元素的中位数
int medianOfFive(vector<int> &nums, int left, int right) {
  sort(nums.begin() + left, nums.begin() + right + 1); // 对五个元素排序
  return (left + right) / 2; // 返回中间元素的索引
}

// 主函数，用于触发选择算法并打印结果
int main() {
  vector<int> nums = {9, 6, 3, 8, 5, 2, 7, 4, 1};
  int k = 4; // 寻找第k小的元素，从1开始计数
  int result = select(nums, 0, nums.size() - 1, k - 1); // 调整k为基于0的索引

  cout << "The " << k << "th smallest element is " << result << endl;

  return 0;
}
