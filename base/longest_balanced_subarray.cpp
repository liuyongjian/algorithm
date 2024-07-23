#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std; // 引入整个标准命名空间

/*
题目：
给定一个整数数组 arr，数组中的元素可能是1、-1或者0。找到 arr
的所有子数组中，-1和1一样多并且长度最大的子数组，返回其长度。

算法思路：
要解决这个问题，我们可以将问题转化为maxSubArrayLength算法，使之变得更容易处理。具体来说，我们可以把所有的
-1 视为 -1，把所有的 1 视为 +1，这样问题就转化为找出数组中和为 0 的最长子数组。
*/

int longestBalancedSubarray(vector<int> &arr) {
  unordered_map<int, int>
      sumIndexMap; // 哈希表用于存储前缀和及其第一次出现的索引
  int sum = 0;     // 当前的前缀和
  int maxLength = 0; // 最大子数组长度

  sumIndexMap[0] = -1; // 初始化，考虑从数组开始累积和即等于0的情况

  for (int i = 0; i < static_cast<int>(arr.size()); ++i) {
    sum += arr[i]; // 更新当前前缀和

    // 检查当前前缀和是否之前已经出现
    if (sumIndexMap.find(sum) != sumIndexMap.end()) {
      // 如果找到一个之前的前缀和与当前的相同，计算子数组的长度
      int subarrayLength = i - sumIndexMap[sum];
      maxLength = max(maxLength, subarrayLength);
    } else {
      // 如果当前的前缀和是第一次出现，记录它的索引
      sumIndexMap[sum] = i;
    }
  }

  return maxLength;
}

int main() {
  vector<int> arr = {1, -1, -1, 1, 1, -1, 1, 1};
  int result = longestBalancedSubarray(arr);
  cout << "Maximum length of a balanced subarray is: " << result << endl;

  return 0;
}
