#include <algorithm> // For std::max
#include <iostream>
#include <vector>

using std::max;
using std::vector;

// 定义 Employee 结构体，包含快乐值和下级员工列表
struct Employee {
  int happiness;
  vector<Employee *> subordinates;

  Employee(int happiness) : happiness(happiness) {}
};

// 定义 Info 结构体来封装递归结果
struct Info {
  int come;    // 员工来派对的最大快乐值
  int notCome; // 员工不来派对的最大快乐值

  Info(int come = 0, int notCome = 0) : come(come), notCome(notCome) {}
};

// calculateMaxHappiness 函数递归计算每个员工来或不来的最大快乐值
Info calculateMaxHappiness(Employee *emp) {
  if (!emp)
    return Info();

  int come = emp->happiness; // 如果当前员工来派对，初始快乐值为员工本身的快乐值
  int notCome = 0; // 如果当前员工不来派对

  for (Employee *sub : emp->subordinates) {
    Info subResult = calculateMaxHappiness(sub);
    come += subResult.notCome; // 如果当前员工来，则其下级不能来
    notCome +=
        max(subResult.come, subResult.notCome); // 下级可来可不来，选择最优解
  }

  return Info(come, notCome);
}

// 计算并返回老板开始的公司派对的最大快乐值
int maxHappy(Employee *boss) {
  Info result = calculateMaxHappiness(boss);
  return max(result.come, result.notCome);
}

int main() {
  Employee *boss = new Employee(10);
  boss->subordinates.push_back(new Employee(5));
  boss->subordinates.push_back(new Employee(6));

  boss->subordinates[0]->subordinates.push_back(new Employee(1));
  boss->subordinates[1]->subordinates.push_back(new Employee(2));
  boss->subordinates[1]->subordinates.push_back(new Employee(3));

  int result = maxHappy(boss);
  std::cout << "Maximum happiness: " << result << std::endl;

  return 0;
}
