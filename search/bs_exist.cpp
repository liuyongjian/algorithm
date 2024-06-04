#include <iostream>
#include <vector>

bool binarySearch(const std::vector<int> &data, int target) {
  int low = 0;
  int high = data.size() - 1;

  while (low <= high) {
    int mid =
        low +
        (high - low) /
            2; // 避免溢出，(low + high) / 2 这种计算mid的方式可能会导致溢出

    if (data[mid] == target) {
      return true;
    } else if (data[mid] < target) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  return false; // 没有找到目标值
}

int main() {
  std::vector<int> sortedArray = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int target = 7;

  if (binarySearch(sortedArray, target)) {
    std::cout << "Found " << target << " in the array." << std::endl;
  } else {
    std::cout << "Did not find " << target << " in the array." << std::endl;
  }

  return 0;
}
