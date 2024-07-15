#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/*
题目：
给定一个整数数组 arr 和一个整数 m，请你找到一个子集，使得这个子集的元素和模 m
的值尽可能大。返回这个最大值。

解决思路：
1. 计算数组的总和：首先计算数组所有元素的总和 sum。
2. 初始化 DP 数组：定义一个二维布尔数组 dp，其中 dp[i][j] 表示在前 i
个元素中是否存在和为 j 的子集。
3. 填充 DP 数组：通过动态规划的方法填充 dp 数组：
    对于每个元素 arr[i]，更新 dp 数组，考虑选择和不选择当前元素两种情况。
4.计算结果：在填充完成的 dp 数组中，找到所有 dp[N-1][j] 为 true 的 j，计算其模 m
的值，返回其中的最大值。

执行结果：
1. 计算数组的总和：
arr = {3, 1, 4, 2}
总和 sum = 3 + 1 + 4 + 2 = 10

2. 初始化动态规划数组：
dp[i][0] 初始化为 true 表示和为 0 的子集总是存在（即空集）。
dp[0][3] 初始化为 true，表示第一个元素自身可以构成和为 3 的子集。

3. 填充动态规划数组：
对于每个元素 arr[i]，更新 dp 数组以考虑选择和不选择当前元素。

第 1 行（第 2 个元素 1）：
j = 0: dp[1][0] = true （继承自 dp[0][0]）。
j = 1: dp[1][1] = true （可以用 1 构成和为 1 的子集）。
j = 3: dp[1][3] = true （继承自 dp[0][3]）。
j = 4: dp[1][4] = true （可以用 3 和 1 构成和为 4 的子集）。

第 2 行（第 3 个元素 4）：
j = 0: dp[2][0] = true （继承自 dp[1][0]）。
j = 1: dp[2][1] = true （继承自 dp[1][1]）。
j = 3: dp[2][3] = true （继承自 dp[1][3]）。
j = 4: dp[2][4] = true （继承自 dp[1][4]）。
j = 5: dp[2][5] = true （可以用 1 和 4 构成和为 5 的子集）。
j = 7: dp[2][7] = true （可以用 3 和 4 构成和为 7 的子集）。
j = 8: dp[2][8] = true （可以用 3、1 和 4 构成和为 8 的子集）。

第 3 行（第 4 个元素 2）：
j = 0: dp[3][0] = true （继承自 dp[2][0]）。
j = 1: dp[3][1] = true （继承自 dp[2][1]）。
j = 2: dp[3][2] = true （可以用 2 构成和为 2 的子集）。
j = 3: dp[3][3] = true （继承自 dp[2][3]）。
j = 4: dp[3][4] = true （继承自 dp[2][4]）。
j = 5: dp[3][5] = true （继承自 dp[2][5]）。
j = 6: dp[3][6] = true （可以用 4 和 2 构成和为 6 的子集）。
j = 7: dp[3][7] = true （继承自 dp[2][7]）。
j = 8: dp[3][8] = true （继承自 dp[2][8]）。
j = 9: dp[3][9] = true （可以用 3、4 和 2 构成和为 9 的子集）。
j = 10: dp[3][10] = true （可以用 3、1、4 和 2 构成和为 10 的子集）。

4. 计算结果：
遍历 dp[N-1][j]，即 dp[3][j]。
找到所有 dp[3][j] 为 true 的 j 并计算 j % m 的值。
最大的 j % m 的值就是答案。


具体计算过程

从 dp[3][j]（即在所有 4 个元素中，能构成的子集和）中，我们可以得到以下和：
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10

计算这些和对 5 取模的值：
0 % 5 = 0
1 % 5 = 1
2 % 5 = 2
3 % 5 = 3
4 % 5 = 4
5 % 5 = 0
6 % 5 = 1
7 % 5 = 2
8 % 5 = 3
10 % 5 = 0

最大值是 4，所以代码输出为：
The maximum value of subset sum modulo 5 is: 4
*/

int maxSubsetSumModulo(const vector<int> &arr, int m) {
  int sum = accumulate(arr.begin(), arr.end(), 0);
  int N = arr.size();

  // 初始化 DP 数组
  vector<vector<bool>> dp(N, vector<bool>(sum + 1, false));
  for (int i = 0; i < N; ++i) {
    // dp[i][0] 应该全部是 true，因为和为 0 的子集总是存在的（即空集）
    dp[i][0] = true;
  }

  // dp[0][arr[0]] 初始化为 true，表示第一个元素自身可以构成和为 arr[0] 的子集
  dp[0][arr[0]] = true;

  // 填充 DP 数组
  for (int i = 1; i < N; ++i) {
    for (int j = 1; j <= sum; ++j) {
      // 下面的逻辑分为选择i和不选择i两种操作
      // 这两个操作共同构成了状态转移的完整逻辑，确保在前 i 个元素中是否存在和为
      // j 的子集。 这两个操作一起写，是因为它们互补且顺序合理

      // 不选择第 i 个元素，那么 dp[i][j] 的值就等于 dp[i-1][j] 的值。
      dp[i][j] = dp[i - 1][j];
      // 如果 j < arr[i]，则 j-arr[i] 会是一个负数，这会导致数组访问越界。
      if (j - arr[i] >= 0) {
        // 选择第 i 个元素，那么我们需要看 dp[i-1][j-arr[i]] 的值。如果 j
        // 大于等于
        // arr[i] 且 dp[i-1][j-arr[i]] 是 true，则 dp[i][j] 也应该是 true。
        dp[i][j] = dp[i][j] || dp[i - 1][j - arr[i]];
      }
    }
  }

  // 计算结果
  int ans = 0;
  for (int j = 0; j <= sum; ++j) {
    if (dp[N - 1][j]) {
      ans = max(ans, j % m);
    }
  }
  return ans;
}

int main() {
  vector<int> arr = {3, 1, 4, 2};
  int m = 5;
  cout << "The maximum value of subset sum modulo " << m
       << " is: " << maxSubsetSumModulo(arr, m) << endl;
  return 0;
}
