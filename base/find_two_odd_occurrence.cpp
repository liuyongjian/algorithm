#include <iostream>
#include <vector>

std::pair<int, int> findTwoOddOccurrences(const std::vector<int> &arr) {
  int xorResult = 0;

  for (int num : arr) {
    xorResult ^= num;
  }

  // ��ȡxorSum�е�����һ��Ϊ1��λ�������������������γ��ֵ�����
  int diffBit = xorResult & -xorResult;

  int x = 0, y = 0;
  for (int num : arr) {
    if (num & diffBit) { // ������һλ�Ƿ�Ϊ1������
      x ^= num;
    } else {
      y ^= num;
    }
  }

  return {x, y};
}

int main() {
  std::vector<int> arr = {1, 2, 3, 3, 1, 5, 7, 5, 9, 9, 7, 8, 8, 10, 10, 11};

  auto [num1, num2] = findTwoOddOccurrences(arr);

  std::cout << "The two numbers are: " << num1 << " and " << num2 << std::endl;
  return 0;
}
