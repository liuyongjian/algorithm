#include <iostream>
#include <vector>

// 局部最小值
int findLocalMin(const std::vector<int> &arr) {
  int n = arr.size();

  if (n == 0)
    return -1;

  if (n == 1 || arr[0] <= arr[1])
    return 0;

  if (arr[n - 1] < arr[n - 2])
    return n - 1;

  int low = 1, high = n - 2; // 忽略首尾元素
  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (arr[mid] <= arr[mid - 1] && arr[mid] <= arr[mid + 1]) {
      return mid;
    }

    if (arr[mid] > arr[mid - 1]) {
      high = mid - 1; // 左边的元素较小，可能在左边找到局部最小值
    } else {
      low =
          mid +
          1; // 右边的元素较小，或者当前元素等于右边的元素但大于左边的，继续在右边搜索
    }
  }

  return -1; // 没有找到局部最小值
}

int main() {
  std::vector<int> arr = {10, 5, 3, 6, 13, 16, 17};
  int index = findLocalMin(arr);

  if (index != -1) {
    std::cout << "Local minimum at index " << index << ": " << arr[index]
              << std::endl;
  } else {
    std::cout << "No local minimum found." << std::endl;
  }

  return 0;
}
