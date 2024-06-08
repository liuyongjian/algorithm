#include <cstdlib>
#include <ctime>
#include <iostream>
#include <queue>
#include <vector>

using std::cout;
using std::endl;
using std::greater;
using std::priority_queue;
using std::vector;

// 问题描述
// 给定一根金条，需要将其切割成几个特定长度的小段，每次切割有一定的成本，等于被切割金条的当前长度。目标是最小化切割的总成本。
// 假设你有一根金条，要分给几个人，每个人需要特定长度的金条。例如，如果一根金条长20，需要分成长度为4、6和10的三段。每次切割的成本等于金条当前的长度，例如，首先将20的金条切割为10和10，成本为20。接下来，将一根10的金条切成6和4，成本为10。总成本将是20+10=30。

// 关键点：
// 策略是使用最小代价（或最小化未来潜在代价）的方法，即每次都尝试合并最小的两块。这可以通过使用优先队列（通常是最小堆）来实现，从而每次都能快速获取最小的两段进行合并。

int minCostToCutGoldBar(const vector<int> &lengths) {
  priority_queue<int, vector<int>, greater<int>> minHeap(lengths.begin(),
                                                         lengths.end());

  int totalCost = 0;
  while (minHeap.size() > 1) {
    int first = minHeap.top();
    minHeap.pop();
    int second = minHeap.top();
    minHeap.pop();

    int cost = first + second;
    totalCost += cost;
    minHeap.push(cost);
  }

  return totalCost;
}

// 暴力解法实现
int bruteForceMinCost(const vector<int> &parts, int start, int end) {
  if (start + 1 == end) {
    return 0; // 如果没有更多的部分需要切割，成本为0
  }
  int minCost = INT_MAX;
  for (int i = start + 1; i < end; i++) {
    int totalLength = parts[end] - parts[start];
    int costLeft = bruteForceMinCost(parts, start, i);
    int costRight = bruteForceMinCost(parts, i, end);
    minCost = std::min(minCost, totalLength + costLeft + costRight);
  }
  return minCost;
}

int calculateMinCutCost(const vector<int> &requests, int totalLength) {
  vector<int> parts = {0};
  for (int length : requests) {
    parts.push_back(parts.back() + length);
  }
  return bruteForceMinCost(parts, 0, parts.size() - 1);
}

int main() {
  vector<int> requests = {4, 6, 10}; // 请求的金条长度
  int totalLength = 20;              // 总金条长度
  int greedyCost = minCostToCutGoldBar(requests);
  int bruteForceCost = calculateMinCutCost(requests, totalLength);

  cout << "Greedy cost: " << greedyCost << endl;
  cout << "Brute Force cost: " << bruteForceCost << endl;

  if (greedyCost == bruteForceCost) {
    cout << "Test passed: Both methods agree on the minimum cost." << endl;
  } else {
    cout << "Test failed: The methods produce different costs." << endl;
  }
  return 0;
}
