#include <iostream>
#include <vector>

// �½����
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

  return low; // low �ǲ�С��target����С����
}

int main() {
  std::vector<int> sortedArray = {1, 2, 2, 3, 4, 4, 5, 6};

  int target = 2;

  int index = lowerBound(sortedArray, target);

  // ʹ�� static_cast<size_t> ��ȷ������ƥ��,
  // �����ڱȽ�ʱ�з��ź��޷������͵ľ��� warning: comparison of integer
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
