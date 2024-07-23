#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/*
题目：
给定一个数组 arr，以及一个值 v，求子数组平均值小于等于 v 的最长子数组长度。

算法思路：
可以通过计算前缀和来有效地计算任意子数组的平均值。这个方法依赖于一个观察，即对于任意子数组，其平均值小于等于
v 可以转化为所有元素减去 v 后的和小于等于
0。因此，我们可以转换数组中的每个元素，然后使用一个类似于找最长子数组和为非正数的技巧。

实现细节：
1. 修改原始数组，使每个元素减去 v，这样我们只需要找和小于或等于0的最长子数组。
2. 使用
unordered_map记录每个不同的前缀和首次出现的位置，这可以帮助我们在之后的遍历中快速找到满足条件的最长子数组。
3.遍历修改后的数组，并更新当前的前缀和。如果当前前缀和小于或等于0，我们直接更新最长长度。
如果不是，我们查找哈希表中是否有前缀和大于当前和的记录，这表示我们找到了一个满足条件的子数组。
4. 如果找到合适的子数组，我们计算其长度，并更新最大长度。
 */

int longestSubarrayWithAvgLessEqualV(vector<int> &arr, double v) {
  vector<long long> modifiedArr(arr.size(), 0);
  for (size_t i = 0; i < arr.size(); i++) {
    // 修改数组，每个元素减去v，并计算累积差值
    modifiedArr[i] = arr[i] - v;
  }

  unordered_map<long long, int> sumIndexMap;
  long long sum = 0;
  int maxLength = 0;
  sumIndexMap[0] = -1; // 初始化，考虑累积和为0的情况

  for (int i = 0; i < static_cast<int>(modifiedArr.size()); i++) {
    sum += modifiedArr[i];

    // 如果sum小于或等于0，更新最大长度
    if (sum <= 0) {
      maxLength = i + 1; // +1 因为索引从0开始
    } else {
      // 如果之前的前缀和已经大于当前的sum，我们可以找到一个子区间
      if (sumIndexMap.find(sum) != sumIndexMap.end()) {
        int prevIndex = sumIndexMap[sum];
        maxLength = max(maxLength, i - prevIndex);
      }
    }

    // 只有当sum值首次出现时才记录索引
    if (sumIndexMap.find(sum) == sumIndexMap.end()) {
      sumIndexMap[sum] = i;
    }
  }

  return maxLength;
}

int main() {
  vector<int> arr = {1, 2, 3, 4, 2, 1, 1}; // 示例数组
  double v = 2.5;                          // 目标平均值

  int result = longestSubarrayWithAvgLessEqualV(arr, v);
  cout << "Maximum length of subarray with average less or equal to " << v
       << " is: " << result << endl;

  return 0;
}
