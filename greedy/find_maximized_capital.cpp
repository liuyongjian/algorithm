#include <iostream>
#include <queue>
#include <vector>

using std::cout;
using std::endl;
using std::priority_queue;
using std::vector;

/*
 题目：
  输入：正数组组costs、正数组组profits、正数K、正数M

  costs[i]表示i号项目的花费
  profits[i]表示i号项目在扣除花费之后还能挣到的钱（利润）
  K表示你只能串行做的最多K个项目
  M表示你初始的资金
  说明：每做完一个项目，马上获得的收益，可以支持你去做下一个项目。不能并行的做项目。

  输出：你最后获得的最大钱数。

 关键点：
  1.
 贪心策略表现为每次选择可行的项目中，利润最大的那个项目进行投资。这是因为选择最高利润的项目可以最大化每次投资的回报，理论上增加了后续项目选择的灵活性和可能性。
  2. 两个优先队列的运用
  最小堆（按成本排序）：管理所有项目，确保我们可以快速访问当前资本下能够承担的最低成本项目。
  最大堆（按利润排序）：从可行项目中选出预期利润最高的项目。每次从最小堆中移动到最大堆的项目都是当前资本能够支持的，然后从中选择利润最大的进行投资。
  3. 动态更新资本
  操作流程：每完成一个项目，就将该项目的利润加到当前资本中。这不仅增加了可用资本，也可能改变下一次可以选择的项目范围。即每做完一个项目，都要重新评估当前可投资的项目集合。
*/

struct Project {
  int cost;
  int profit;
  Project(int c, int p) : cost(c), profit(p) {}
};

struct CompareCost {
  bool operator()(const Project &p1, const Project &p2) {
    return p1.cost > p2.cost;
  }
};

struct CompareProfit {
  bool operator()(const Project &p1, const Project &p2) {
    return p1.profit < p2.profit;
  }
};

int findMaximizedCapital(int k, int W, vector<int> &Profits,
                         vector<int> &Capital) {
  priority_queue<Project, vector<Project>, CompareCost> minCostHeap;
  priority_queue<Project, vector<Project>, CompareProfit> maxProfitHeap;

  for (size_t i = 0; i < Profits.size(); ++i) {
    minCostHeap.emplace(Capital[i], Profits[i]);
  }

  for (int i = 0; i < k; ++i) {
    while (!minCostHeap.empty() && minCostHeap.top().cost <= W) {
      maxProfitHeap.push(minCostHeap.top());
      minCostHeap.pop();
    }

    if (maxProfitHeap.empty()) {
      break;
    }

    W += maxProfitHeap.top().profit;
    maxProfitHeap.pop();
  }

  return W;
}

// 对数器实现：简单模拟算法
int simpleSimulator(int k, int W, const vector<int> &Profits,
                    const vector<int> &Capital) {
  vector<bool> done(Profits.size(), false);
  int doneProjects = 0;

  while (doneProjects < k) {
    int bestIndex = -1;
    for (size_t i = 0; i < Profits.size(); ++i) {
      if (!done[i] && Capital[i] <= W) {
        if (bestIndex == -1 || Profits[i] > Profits[bestIndex]) {
          bestIndex = i;
        }
      }
    }

    if (bestIndex == -1) {
      break;
    }

    W += Profits[bestIndex];
    done[bestIndex] = true;
    doneProjects++;
  }

  return W;
}

int main() {
  vector<int> profits = {1, 2, 3};
  vector<int> costs = {0, 1, 1};
  int k = 2;
  int initialCapital = 0;

  int resultGreedy = findMaximizedCapital(k, initialCapital, profits, costs);
  int resultSimple = simpleSimulator(k, initialCapital, profits, costs);

  cout << "Greedy result: " << resultGreedy << endl;
  cout << "Simple simulator result: " << resultSimple << endl;

  if (resultGreedy == resultSimple) {
    cout << "Test passed: Both methods agree on the minimum cost." << endl;
  } else {
    cout << "Test failed: The methods produce different results." << endl;
  }

  return 0;
}
