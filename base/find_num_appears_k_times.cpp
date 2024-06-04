#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <unordered_map>
#include <vector>

// 关键点：M×constant+K

// 生成测试用例，确保一个数字出现K次，其他数出现M次
std::vector<int> generateTestCase(int k, int m, int numSize) {
  std::vector<int> nums;
  size_t specialSize = static_cast<size_t>(k);
  int special = rand() % 1000; // 随机生成特殊数字
  for (size_t i = 0; i < specialSize; ++i) {
    nums.push_back(special); // 特殊数字出现K次
  }

  size_t totalSize = static_cast<size_t>(numSize);
  // 填充其他数字，每个出现M次，确保不与特殊数字冲突
  while (nums.size() < totalSize) {
    int num = rand() % 1000;
    // 避免特殊数字
    if (num != special) {
      size_t mSize = static_cast<size_t>(m);
      for (size_t j = 0; j < mSize; ++j) {
        nums.push_back(num);
        if (nums.size() == totalSize)
          break;
      }
    }
  }

  std::random_shuffle(nums.begin(), nums.end()); // 打乱顺序
  return nums;
}

// 使用哈希表的简单方法找到出现K次的数字
int findNumberByMap(const std::vector<int> &nums, int k, int m) {
  std::unordered_map<int, int> counts;
  for (int num : nums) {
    counts[num]++;
  }

  for (const auto &pair : counts) {
    if (pair.second == k)
      return pair.first;
  }

  return -1; // Not found
}

int findNumberAppearsKTimes(const std::vector<int> &nums, int k, int m) {
  std::vector<int> bitCounts(32, 0);

  for (int num : nums) {
    for (int i = 0; i < 32; i++) {
      if (num & (1 << i)) {
        bitCounts[i]++;
      }
    }
  }

  int result = 0;
  for (int i = 0; i < 32; i++) {
    if ((bitCounts[i] % m) == (k % m)) {
      result |= (1 << i); // 将 result 变量中的当前值与 1 << i
                          // 的结果进行按位或操作，并将结果存回 result。
    }
  }

  return result;
}

// 对数器
void test(int tests, int numSize, int k, int m) {
  srand(time(nullptr));
  bool success = true;

  for (int i = 0; i < tests; ++i) {
    auto nums = generateTestCase(k, m, numSize);
    int expected = findNumberByMap(nums, k, m);
    int result = findNumberAppearsKTimes(nums, k, m);

    if (expected != result) {
      success = false;
      std::cout << "Test failed" << std::endl;
      break;
    }
  }

  if (success) {
    std::cout << "All tests passed!" << std::endl;
  }
}

int main() {
  test(100, 1000, 10, 3); // 运行100次测试，数组大小1000，K=10，M=3
  return 0;
}
