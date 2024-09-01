#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
题目：
给定两个数组 hard 和 money，它们的长度都为 N：
hard[i] 表示第 i 号工作的难度。
money[i] 表示第 i 号工作的收入。

还给定一个数组 ability，长度为 M：
ability[j] 表示第 j 号人的能力。

每一份工作可以提供无限的岗位，其难度和收入都相同，但人的能力必须大于等于这份工作的难度，才能胜任这份工作。

要求返回一个长度为 M 的数组 ans，其中 ans[j] 表示第 j 号人能够获得的最高收入。

算法思路：
贪心策略：
涉及到了一种简单的贪心策略，特别是在处理“最大收入”问题时。具体来说：

1.
预处理工作收入：首先对工作按难度进行排序，同时在相同难度的工作中选择收入最高的。
这一步中涉及到的贪心策略是：只保留每个难度等级最高收入的工作，因为如果某人的能力可以胜任某个难度的工作，他自然会选择收入最高的那个。
在这里，我们已经做了最优选择，确保了每个难度级别只保留了最高收入的工作选项。

2.
为个人寻找最佳工作：对于每个人的能力值，我们使用二分查找在预处理的工作列表中寻找他们能胜任的最高收入工作。
这一步利用了贪心的思想，即每个人都尽可能选择他们能够胜任的收入最高的工作。

在这个算法中，我们没有追求全局最优解，而是在每个决策点选择局部最优解（例如，每个人根据自己的能力选择最大可能的收入），这是贪心算法的典型特点。
贪心算法的核心思想是通过做出局部最优的选择，希望这种方式能导致全局最优的解决方案。
在这个特定问题中，这种策略是有效的，因为每个人选择最高收入的工作是独立的，并且不会相互影响。

具体步骤：
首先，将所有工作按难度排序，并筛选出每个难度下最高的工资。
然后，针对每个人的能力，使用二分查找确定他们可以胜任的工作中的最高工资。
最后输出每个人可以得到的最高收入。

执行步骤:
一、工作信息
hard = [2, 4, 6, 8, 4]
money = [10, 20, 30, 40, 25]
二、个人能力
ability = [1, 3, 5, 7, 9]

步骤 1: 结构化并排序
首先，将工作的难度和收入结合成 jobs 列表，然后按照上述规则排序。

jobs 列表（未排序）:
[(2, 10), (4, 20), (6, 30), (8, 40), (4, 25)]

排序后的 jobs 列表：
[(2, 10), (4, 25), (4, 20), (6, 30), (8, 40)]

这里，对于难度为 4 的两份工作，我们按照收入从大到小排序，所以 (4, 25) 排在
(4,20) 前面。

步骤 2: 筛选每个难度级别的最优工作
现在遍历排序后的jobs，更新每个难度的最高收入工作。

当我们遇到难度为 2 的工作时，maxMoney 更新为 10。
难度为 4 的第一个工作（收入 25）时，maxMoney 更新为 25。
接下来的难度为 4 的工作（收入 20）不会更新 maxMoney，因为 25 已是最高。
难度为 6 的工作（收入 30），maxMoney 更新为 30。
难度为 8 的工作（收入 40），maxMoney 更新为 40。

maxJobByAbility 列表构建如下：
[(2, 10), (4, 25), (6, 30), (8, 40)]

步骤 3: 为每个人匹配最优工作
现在，我们为 ability 中的每个能力值使用二分查找来匹配最优工作。

对于能力值 1，找不到满足条件的工作，收入为 0。
对于能力值 3，最大可以胜任难度为 2 的工作，收入为 10。
对于能力值 5，最大可以胜任难度为 4 的工作，收入为 25。
对于能力值 7，最大可以胜任难度为 6 的工作，收入为 30。
对于能力值 9，最大可以胜任难度为 8 的工作，收入为 40。
最终的 ans 数组为：

[0, 10, 25, 30, 40]
*/

vector<int> findMaxEarnings(const vector<int> &hard, const vector<int> &money,
                            const vector<int> &ability) {
  int N = hard.size();
  int M = ability.size();
  vector<int> ans(M, 0);

  // 将工作按难度和收入排序
  vector<pair<int, int>> jobs;
  for (int i = 0; i < N; ++i) {
    jobs.emplace_back(hard[i], money[i]);
  }

  // 按难度从小到大排序，若难度相同，则按收入从大到小排序
  sort(jobs.begin(), jobs.end(),
       [](const pair<int, int> &a, const pair<int, int> &b) {
         return a.first < b.first ||
                (a.first == b.first && a.second > b.second);
       });

  // 对每个能力值，找到他能胜任的最高收入的工作
  vector<pair<int, int>> maxJobByAbility; // (ability, max_money)
  int maxMoney = 0;
  for (auto &job : jobs) {
    if (job.second > maxMoney) {
      maxMoney = job.second;
      maxJobByAbility.emplace_back(job.first, maxMoney);
    }
  }

  // 对于每个人的能力，找到他们可以得到的最高收入
  for (int j = 0; j < M; ++j) {
    int cap = ability[j];
    int low = 0, high = maxJobByAbility.size() - 1, best = 0;
    while (low <= high) {
      int mid = low + (high - low) / 2;
      if (maxJobByAbility[mid].first <= cap) {
        best = maxJobByAbility[mid].second;
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }
    ans[j] = best;
  }

  return ans;
}

int main() {
  vector<int> hard = {2, 4, 6, 8};
  vector<int> money = {10, 20, 30, 40};
  vector<int> ability = {1, 3, 5, 7, 9};

  vector<int> ans = findMaxEarnings(hard, money, ability);
  for (int i : ans) {
    cout << i << " ";
  }
  cout << endl;

  return 0;
}
