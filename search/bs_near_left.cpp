#include <iostream>
#include <vector>

// 下界查找
int lowerBound(const std::vector<int> &data, int target) {
  int low = 0, high = data.size();

  while (low < high) {
    int mid = low + (high - low) / 2;
    if (data[mid] < target) {
      low = mid + 1;
    } else {
      high = mid;
    }
  }

  return low; // low 是不小于target的最小索引
}

int main() {
  std::vector<int> sortedArray = {1, 2, 2, 3, 4, 4, 5, 6};

  int target = 2;

  int index = lowerBound(sortedArray, target);

  // 使用 static_cast<size_t> 来确保类型匹配,
  // 避免在比较时有符号和无符号类型的警告 warning: comparison of integer
  // expressions of different signedness: 'int' and
  // 'std::vector<int>::size_type'
  if (static_cast<size_t>(index) < sortedArray.size() &&
      sortedArray[index] == target) {
    std::cout << "The first position of " << target << " is at index " << index
              << std::endl;
  } else {
    std::cout << "No element no less than " << target
              << " found. Position should be " << index << std::endl;
  }

  return 0;
}
