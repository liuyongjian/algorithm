#include <iostream>
#include <vector>

bool binarySearch(const std::vector<int> &data, int target) {
  int low = 0;
  int high = data.size() - 1;

  while (low <= high) {
    int mid =
        low +
        (high - low) /
            2; // ���������(low + high) / 2 ���ּ���mid�ķ�ʽ���ܻᵼ�����

    if (data[mid] == target) {
      return true;
    } else if (data[mid] < target) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  return false; // û���ҵ�Ŀ��ֵ
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
