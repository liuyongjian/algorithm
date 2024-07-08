#include <cstdlib> // 用于生成随机数
#include <ctime>   // 用于设置随机数种子
#include <iostream>
#include <vector>

using namespace std;

/*
题目：
假设有一个源源不断吐出不同球的机器，
只有一个可以装下10个球的袋子，每一个吐出的球，要么放入袋子，要么永远扔掉。
如何做到在机器吐出每一个球之后，所有吐出的球都等概率被放进袋子里。

关键点：
1. 初始化阶段：
将前 k 个元素直接放入蓄水池，这一步是初始化阶段。

2. 维护阶段：
对于数据流中的第 i 个元素（i >= k），生成一个 [0, i] 范围内的随机索引 j。
如果 j 小于 k，则用当前元素替换蓄水池中的第 j 个元素。
这个步骤确保在任何时候，每个元素被选入蓄水池的概率都是相等的。

时间复杂度:
蓄水池算法的时间复杂度分析如下：
1. 初始化阶段：
将前 k 个元素放入蓄水池，需要 O(k) 的时间。

2. 维护阶段：
- 对于每个后续元素，生成一个随机数，并根据条件决定是否替换蓄水池中的某个元素。
- 生成随机数和替换操作都在常数时间内完成，因此处理每个元素的时间复杂度为 O(1)。

综合来看，假设数据流的总长度为 n，则：

- 初始化阶段的时间复杂度为 O(k)。
- 维护阶段的时间复杂度为 O(n - k)，即 O(n)。

因此，总体的时间复杂度为：
O(k) + O(n - k) = O(n)
*/

// 蓄水池采样算法
vector<int> reservoirSampling(vector<int> &stream, int k) {
  vector<int> reservoir(k);

  // 将前k个元素直接放入蓄水池
  for (int i = 0; i < k; ++i) {
    reservoir[i] = stream[i];
  }

  // 从第k+1个元素开始处理
  for (size_t i = k; i < stream.size(); ++i) {
    // 生成一个[0, i]范围内的随机索引
    int j = rand() % (i + 1);

    // 如果随机索引小于k，则替换蓄水池中的第j个元素
    if (j < k) {
      reservoir[j] = stream[i];
    }
  }

  return reservoir;
}

int main() {
  srand(time(0)); // 设置随机数种子

  // 假设机器吐出的球的序列
  vector<int> stream = {1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
                        11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  int k = 10; // 蓄水池大小

  vector<int> reservoir = reservoirSampling(stream, k);

  // 每次执行时，蓄水池中的球会有所不同，但每个球被选中的概率是相等的。
  cout << "蓄水池中的球为: ";
  for (int num : reservoir) {
    cout << num << " ";
  }
  cout << endl;

  return 0;
}
