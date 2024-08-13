#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/*
题目:
给定一个数组 arr，你可以在每个数字之前决定加 (+) 或者减
(-)，但是必须所有数字都参与。 再给定一个数 target，请问最后算出 target
的方法数是多少？

思路：
「目标和」问题，它转化为了一个「子集和」问题，具体来讲是找到数组的一个子集，其和等于特定值
P。 这里 P 是通过整个数组的和与目标和相加再除以二得到的。
这种转换是基于将数组中的数分为加和减两组，并利用组合数学关系得出的。

具体操作是将数组分为两部分：一部分所有数字前面都是正号，另一部分所有数字前面都是负号。设这两部分的和分别为
P 和 N，则有： P−N=target

同时我们知道所有元素的和为 sum：P+N=sum

由此可以得到：
P= (target+sum)/2
​
因此问题转化为找出数组中元素之和为 P 的方式有多少种。如果
(target+sum)/2不是整数或小于 0，则解不存在。

1. 计算和与转换问题:
首先计算数组所有元素的和 sum。
检查 (sum + target) 是否为偶数，因为只有当这个值为偶数时，(sum + target)/2
才是一个整数，表示可以从数组中选取元素的一个组合，其和为这个值。如果不是偶数，或者这个值小于
target，则没有可能的方法。
2. 使用动态规划求解:
创建一个动态规划数组 dp，其中 dp[j] 表示从数组中选取元素，使得这些元素的和为 j
的方法数量。 初始化 dp[0] = 1，表示和为0（即不选取任何元素）有一种方法。
对于数组中的每个元素 num，以及从 P 到 num 的每个和
j（逆序保证每个元素只用一次），更新 dp[j] 的值，加上 dp[j-num] 的值。

关键点：
1.
问题转换：将原问题转化为子集和问题是解题的关键，依赖于数学上的等式变换。
2.
动态规划的使用：动态规划适用于此类问题，因为它可以避免重复计算，并通过建立小规模问题的解来解决大规模问题。
3.
逆序更新：在动态规划中逆序更新dp数组是必须的，以确保每个元素在迭代中只被使用一次。

时间复杂度：
O(n*P)，其中 n 是数组 nums 的长度，P 是转换后需要达到的目标和。
这个时间复杂度来源于对每个元素执行一次循环，并在每次循环中可能执行多达 P
次更新操作。
*/

// 方式1：子集和
// int findTargetSumWays(vector<int> &nums, int target) {
//   int sum = 0;
//   for (int num : nums)
//     sum += num;

//   // 如果(sum + target)不是偶数或者sum < target，则不存在这样的组合
//   if ((sum + target) % 2 != 0 || sum < target)
//     return 0;

//   int P = (sum + target) / 2;
//   // dp[j] 表示从数组中选取若干元素，组成和为 j 的方法数
//   vector<int> dp(P + 1, 0);
//   dp[0] = 1; // 和为0只有一种方法，即不选任何元素

//   for (int num : nums) {
//     for (int j = P; j >= num; j--) {
//       dp[j] += dp[j - num];
//     }
//   }

//   return dp[P];
// }

// 计算达到目标和的方法数
int calculateWays(vector<int> &arr, int index, int rest,
                  unordered_map<int, unordered_map<int, int>> &dp) {
  // 检查记忆化表中是否已经有这个状态的结果
  // dp: {index, {rest, sum}}
  if (dp.count(index) && dp[index].count(rest)) {
    return dp[index][rest];
  }

  int ans = 0;

  // 如果已经遍历到数组的最后一个元素
  if (index == static_cast<int>(arr.size())) {
    ans = (rest == 0) ? 1 : 0;
  } else {
    // 递归调用：尝试加上当前元素或者减去当前元素
    ans = calculateWays(arr, index + 1, rest - arr[index], dp) +
          calculateWays(arr, index + 1, rest + arr[index], dp);
  }

  // 记录到记忆化表中
  dp[index][rest] = ans;
  return ans;
}

// 方式2：使用递归和记忆化技术来计算达到目标和的方法数
int findTargetSumWays(vector<int> &arr, int s) {
  unordered_map<int, unordered_map<int, int>> dp;
  return calculateWays(arr, 0, s, dp);
}

int main() {
  vector<int> nums = {2, 3, 5, 8, 13, 21};
  int target = 10;

  cout << "Number of ways to reach target sum: "
       << findTargetSumWays(nums, target) << endl;

  return 0;
}
