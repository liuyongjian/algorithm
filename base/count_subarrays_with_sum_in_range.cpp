#include <iostream>
#include <map>
#include <vector>

using namespace std;

/*
题目：
给定一个数组 arr，和两个整数 a 和 b（a <= b），求 arr
中有多少个子数组，其累加和在 [a, b] 这个范围上，返回达标的子数组数量。

算法原理：
利用前缀和数组，我们可以在常数时间内计算出任意子数组的和。
关键在于，如果我们知道了从索引 i 到 j 的子数组的和，我们可以用 prefixSum[j] -
prefixSum[i-1] 来表示，其中 prefixSum是前缀和数组。

为了找出所有满足条件的子数组（即和在给定范围 [a,
b]内），我们在遍历数组的同时，使用一个有序表（如std::map）来存储各个前缀和出现的次数。

使用 std::map
存储前缀和及其计数可以优化查找性能，因为它保证了元素的有序性和快速访问性。
这样我们可以避免重复的完整数组扫描，而是通过哈希查找来快速计算结果

关键点：
利用 map 的 lower_bound 和 upper_bound
函数，可以快速找到所有符合条件的前缀和的开始和结束位置，从而计算符合条件的子数组数量。

时间复杂度：
插入操作：对于每一个元素，我们都可能更新 std::map。由于 std::map
基于红黑树，每次插入和查找操作的时间复杂度为 O(log n)。
查找操作：每次我们需要查找的范围为 [prefixSum - b, prefixSum - a]，这涉及到一次
lower_bound 和一次 upper_bound 查找，每次查找的时间复杂度也是 O(log n)。
总体时间复杂度：因为每个元素都执行了插入和查找操作，总时间复杂度为 O(n log
n)，其中 n 是数组的长度。

运行结果：
单个元素子数组：
1 (不满足)
2 (不满足)
3 (不满足)
4 (不满足)
5 (满足)

两个元素子数组：
1+2=3 (不满足)
2+3=5 (满足)
3+4=7 (满足)
4+5=9 (不满足)

三个元素子数组：
1+2+3=6 (满足)
2+3+4=9 (不满足)
3+4+5=12 (不满足)

四个元素子数组：
1+2+3+4=10 (不满足)
2+3+4+5=14 (不满足)

五个元素子数组：
1+2+3+4+5=15 (不满足)

满足条件的子数组有：{5}, {2, 3}, {3, 4}, {1, 2, 3}，共4个。
*/

int countSubarraysWithSumInRange(const vector<int> &arr, int a, int b) {
  map<int, int> prefixSumCount;
  int prefixSum = 0;
  int count = 0;

  // 初始化前缀和表，以处理从起始元素开始的子数组
  prefixSumCount[0] = 1;

  for (int num : arr) {
    // 更新当前前缀和
    prefixSum += num;

    // 计算当前前缀和与目标区间的关系
    // 查找所有前缀和在 [prefixSum - b, prefixSum - a]
    // 范围内的前缀和的数量，即有多少个前缀和在[prefixSum - b, prefixSum -
    // a]之间
    auto lower = prefixSumCount.lower_bound(prefixSum - b);
    auto upper = prefixSumCount.upper_bound(prefixSum - a);

    // 遍历这个范围内的所有前缀和，累加符合条件的子数组的数量
    for (auto it = lower; it != upper; ++it) {
      // 通过累加所有符合条件的前缀和的出现次数（count +=
      // it->second），我们可以计算出有多少种方式使得从数组的起始到当前元素的某个子数组的和符合给定的条件
      // [a, b]。
      count += it->second;
    }

    // 记录当前前缀和出现的次数
    prefixSumCount[prefixSum]++;
  }

  return count;
}

int main() {
  vector<int> arr = {1, 2, 3, 4, 5};
  int a = 5, b = 8;

  cout << "Count of subarrays with sum in range: "
       << countSubarraysWithSumInRange(arr, a, b) << endl;

  return 0;
}
