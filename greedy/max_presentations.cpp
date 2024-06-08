#include <algorithm>
#include <iostream>
#include <vector>

// 一些项目要占用一个会议室宣讲，会议室不能同时容纳两个项目的宣讲。
// 给你每一个项目开始的时间和结束的时间，
// 你来安排宣讲的日程，要求会议室进行的宣讲的场次最多。
// 返回最多的宣讲场次。

// 关键点:
// 排序策略：算法首先按照项目的结束时间对所有项目进行排序。这是因为选择结束最早的项目，可以尽快释放会议室，为后续的项目留出更多时间。这种排序是实现贪心策略的基础。
// 局部最优选择：在每一步选择中，算法都会选择当前可以开始的、且结束时间最早的项目。这种方法保证了每次选择都能在不冲突的前提下，尽可能多地进行宣讲。
// 更新条件：在选择了一个项目后，算法会更新最后一个被选项目的结束时间，这个时间点作为新的阈值，来判断后续项目是否与已选项目发生时间上的冲突。

using std::cout;
using std::endl;
using std::max;
using std::sort;
using std::vector;

struct Project {
  int start;
  int end;

  // 定义了一个重载的 < 操作符用于 Project 结构，它使得 Project
  // 实例可以根据结束时间进行比较。它允许sort函数以结束时间为基准对项目列表进行排序。
  // 如果当前项目 (this) 的结束时间早于另一个项目 (p) 的结束时间，则返回
  // true，表示当前项目在排序后应该位于另一个项目之前
  bool operator<(const Project &p) const { return end < p.end; }
};

// 计算可以进行的最多宣讲场次
int maxPresentationsGreedy(vector<Project> &projects) {
  if (projects.empty())
    return 0;

  // 按项目结束时间排序
  // 用来将给定范围内的元素排序成升序。
  // Project结构体重载了<操作符，定义了一个自定义的比较逻辑，即根据项目的结束时间进行排序。
  // 因此，当sort调用时，它将按照项目的结束时间从早到晚进行排序。
  sort(projects.begin(), projects.end());

  // 初始化
  int count = 0;
  int lastEndTime = 0;

  // 遍历所有项目，贪心选择
  for (const auto &p : projects) {
    if (p.start >= lastEndTime) {
      lastEndTime = p.end;
      count++;
    }
  }

  return count;
}

// 使用穷举法尝试所有可能的项目组合
// Brute Force: 穷举法、暴力匹配算法
int bruteForceMaxPresentations(vector<Project> &projects, size_t index,
                               int lastEndTime) {
  if (index == projects.size())
    return 0; // 没有更多项目可选择
  int taken = 0, notTaken = 0;
  // 尝试选择当前项目，前提是它不与已选择的项目重叠
  if (projects[index].start >= lastEndTime) {
    taken = 1 + bruteForceMaxPresentations(projects, index + 1,
                                           projects[index].end);
  }
  // 不选择当前项目
  notTaken = bruteForceMaxPresentations(projects, index + 1, lastEndTime);
  return max(taken, notTaken);
}

// 需要初始化这个函数
int maxPresentationsBruteForce(vector<Project> &projects) {
  // 为了确保所有可能的开始，首先按开始时间排序
  sort(projects.begin(), projects.end(),
       [](const Project &a, const Project &b) { return a.start < b.start; });
  return bruteForceMaxPresentations(projects, 0, 0);
}

// 生成随机项目
vector<Project> generateRandomProjects(int num) {
  vector<Project> projects;
  for (int i = 0; i < num; ++i) {
    int start = rand() % 100;       // Start time between 0 and 99
    int duration = 1 + rand() % 20; // Duration between 1 and 20
    projects.push_back({start, start + duration});
  }
  return projects;
}

// 对数器
void testMaxPresentations() {
  srand(time(NULL)); // Seed random number generator
  int tests = 1000;  // Number of tests

  for (int i = 0; i < tests; ++i) {
    vector<Project> projects =
        generateRandomProjects(10); // Generate 10 random projects
    int result1 = maxPresentationsGreedy(projects);
    int result2 = maxPresentationsBruteForce(projects);
    if (result1 != result2) {
      cout << "Mismatch found!" << endl;
      cout << "Greedy Result: " << result1
           << ", Brute Force Result: " << result2 << endl;
      return;
    }
  }
  cout << "All tests passed!" << endl;
}

int main() {
  testMaxPresentations();
  return 0;
}
