#include <iostream>
#include <stack>
#include <vector>

using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::rand;
using std::stack;
using std::vector;

void swap(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

// 快排1.0
// 基于荷兰国旗问题的分区算法，我们可以实现一个三向切分的快速排序算法。这种快速排序变体利用了荷兰国旗算法的思想来处理数组中有大量重复元素的情况，能够提高排序效率。在这种情况下，数组被分为小于、等于和大于枢轴值（pivot）的三部分。
void quickSortDutchFlag1(std::vector<int> &nums, int L, int R) {
  if (L >= R) {
    return;
  }

  int pivot = nums[R]; // 选择最后一个元素作为划分值
  int low = L;
  int mid = L;
  int high = R - 1;

  // 三向切分
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

  // 递归对不含划分值的部分进行快速排序
  quickSortDutchFlag1(nums, L, low - 1); // 对小于划分值的部分排序
  quickSortDutchFlag1(nums, mid, R);     // 对大于划分值的部分排序
}

// 快排2.0
// 荷兰国旗分区的快速排序算法返回等于区域（pivot区域）的下标，即函数返回一个包含等于区域起始和结束索引的值。
// 这样的修改可以更准确地控制递归调用，避免对已经是等于pivot的元素再次进行排序，从而提高效率。
// 适合在包含大量重复元素的数据集上执行快速排序，可以显著减少不必要的操作，从而提高整体的排序效率。
// 如果数组是去重的，2.0代码和1.0代码没有区别
pair<int, int> partition(vector<int> &nums, int L, int R) {
  int pivot = nums[R]; // 使用最后一个元素作为划分值
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

  return make_pair(low, mid); // 返回等于区域的起始和结束下标
}

void quickSortDutchFlag2(vector<int> &nums, int L, int R) {
  if (L >= R) {
    return;
  }

  pair<int, int> eq = partition(nums, L, R);
  quickSortDutchFlag2(nums, L, eq.first - 1); // 对小于划分值的部分排序
  quickSortDutchFlag2(nums, eq.second, R); // 对大于划分值的部分排序
}

// 快排3.0
// 要将上面2.0的快速排序升级为随机快速排序，我们可以引入随机元素选择作为枢轴值（pivot）。
// 在随机快速排序中，我们通常在每次递归调用前，随机选择一个元素与最后一个元素交换，然后使用这个随机选定的元素作为枢轴进行分区。
// 这种方法有助于提高快速排序算法的效率，特别是在面对有序或近乎有序的数组时，可以防止算法的性能退化到最坏情况（O(n²)）。

// 最佳情况时间复杂度：
// 选择的元素靠近中间的位置，即每次分区都将数组分为两个几乎等大小的部分。这意味着每次递归的层级可以最大限度地减少,
// 即O(logn) 层，每层做一次全数组的遍历，因此最佳情况的时间复杂度是 O(nlogn)。
void quickSortDutchFlag3(std::vector<int> &nums, int L, int R) {
  if (L >= R) {
    return;
  }

  // 随机选择一个枢轴:
  // 在排序前，随机选择一个元素作为枢轴，这有助于平衡分区，减少对特定数据分布的敏感性。
  int pivotIndex = L + rand() % (R - L + 1);
  swap(nums[pivotIndex],
       nums[R]); // 将选中的枢轴移到最后，后面的代码和2.0的一样

  pair<int, int> eq = partition(nums, L, R);
  quickSortDutchFlag3(nums, L, eq.first - 1); // 对小于划分值的部分排序
  quickSortDutchFlag3(nums, eq.second, R); // 对大于划分值的部分排序
}

// 快排3.0（非递归实现）
// 将递归版本的快速排序转换为非递归版本主要依赖于栈来模拟递归调用。在非递归的快速排序中，需要手动管理一个栈来保存下一步需要排序的子数组的边界。
// 这样可以避免递归带来的调用栈开销，尤其是在深度很大时。
// 非递归实现虽然逻辑上更复杂，但在实践中能有效避免递归带来的潜在栈溢出问题(不使用系统栈)，尤其适合处理大数据量的情况。
void quickSortNonRecursive(vector<int> &nums) {
  // 栈用于保存每个待排序子数组的边界。每次从栈中弹出一个边界对，对这个子数组进行分区，然后将非空的子区间推回栈中。
  stack<pair<int, int>> stack;
  stack.push({0, static_cast<int>(nums.size()) - 1});

  while (!stack.empty()) {
    auto bounds = stack.top();
    stack.pop();
    int L = bounds.first, R = bounds.second;

    if (L < R) {
      // 随机选择一个枢轴
      int pivotIndex = L + rand() % (R - L + 1);
      swap(nums[pivotIndex], nums[R]); // 将选中的枢轴移到最后

      pair<int, int> eq = partition(nums, L, R);
      if (eq.first - 1 > L) {
        stack.push({L, eq.first - 1}); // 推入小于划分的部分
      }
      if (eq.second < R) {
        stack.push({eq.second, R}); // 推入大于划分的部分
      }
    }
  }
}

int main() {
  vector<int> nums = {2, 0, 5, 2, 1, 4, 3, 3, 2};
  // quickSortDutchFlag3(nums, 0, nums.size() - 1);
  quickSortNonRecursive(nums);

  for (int num : nums) {
    cout << num << " ";
  }
  return 0;
}
