#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

/*
题目:加油站的良好出发点问题（Gas Station Problem）

在一个环形的道路上，有 n 个加油站，每个加油站 i 有汽油
gas[i]，在相邻的加油站之间，有一定的距离需要消耗汽油
cost[i]。假设你有一辆车，车的油箱可以无限大。请问，是否存在一个加油站可以作为出发点，使得车辆可以绕一圈回到这个加油站，并且油箱中的汽油不会为空？如果存在，返回这个出发点的索引；如果不存在，返回
-1。

关键点：
1. 总净汽油量判断：计算整个行程的总净汽油量 total_tank。如果 total_tank 小于
0，说明无论从哪个加油站出发，汽油总量都不足以完成环形路程。因此直接返回 -1。

2. 局部净汽油量判断：使用 current_tank
记录当前路径上的净汽油量。如果在某个加油站 i，current_tank 小于 0，说明从起点到
i 之间的任意一个加油站都不能作为起点，因为在这段路径上任何地方都会缺油。因此，从
i+1 开始重新尝试，并重置 current_tank。

3. 贪心策略：
1.
总净汽油量判断：通过计算所有加油站的总净汽油量来快速判断是否存在可能的起点。如果总净汽油量小于消耗量，则直接返回
-1。
2.
局部净汽油量判断：在遍历过程中，如果发现当前路径的净汽油量小于0，则重新选择起点为下一个加油站，并重置当前净汽油量。这个过程确保了每个选择都是当前情况下的最优选择，不需要回溯。

贪心算法适用于具有“最优子结构”和“无后效性”的问题
最优子结构：问题的最优解包含其子问题的最优解。
无后效性：当前决策不影响之后的决策，即当前决策的最优性不会因为后续决策的改变而改变。

时间复杂度:
O(n)：整个算法只需遍历一次 gas 和 cost 数组，因此时间复杂度为 O(n)，其中 n
是加油站的数量。每个加油站仅访问一次，所以时间复杂度是线性的。
*/

int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
  int total_tank = 0;       // 总的净汽油量
  int current_tank = 0;     // 当前的净汽油量
  int starting_station = 0; // 起始加油站

  // 遍历所有加油站
  for (size_t i = 0; i < gas.size(); ++i) {
    total_tank += gas[i] - cost[i];   // 更新总净汽油量
    current_tank += gas[i] - cost[i]; // 更新当前净汽油量

    // 如果当前净汽油量小于0，不能从当前起始点到达i
    if (current_tank < 0) {
      starting_station = i + 1; // 下一个加油站作为起点
      current_tank = 0;         // 重置当前净汽油量
    }
  }

  // 检查总净汽油量是否大于等于0
  return total_tank >= 0 ? starting_station : -1;
}

int main() {
  vector<int> gas = {1, 2, 3, 4, 5};
  vector<int> cost = {3, 4, 5, 1, 2};

  int start = canCompleteCircuit(gas, cost);

  if (start != -1) {
    cout << "可以从加油站 " << start << " 作为起点完成一圈。\n";
  } else {
    cout << "没有加油站可以作为起点完成一圈。\n";
  }

  return 0;
}
