#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

// 逆序对是指在一个数组中，如果前面的数字大于后面的数字，则这两个数字组成一个逆序对

// 关键点：求解一个数组的逆序对可以使用归并排序的思想，在归并的过程中统计逆序对的个数

int merge(vector<int> &arr, int left, int mid, int right) {
  vector<int> temp(right - left + 1);

  int i = left, j = mid + 1;
  int count = 0;
  int k = 0;

  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j]) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
      // 当arr[i] > arr[j]时，arr[i]后面的所有元素都与arr[j]构成逆序对
      count += mid - i + 1;
    }
  }

  while (i <= mid) {
    temp[k++] = arr[i++];
  }

  while (j <= right) {
    temp[k++] = arr[j++];
  }

  for (int i = 0; i < k; i++) {
    arr[left + i] = temp[i];
  }

  return count;
}

int mergeSort(vector<int> &arr, int left, int right) {
  if (left >= right) {
    return 0;
  }

  int mid = left + (right - left) / 2;

  int leftCount = mergeSort(arr, left, mid);
  int rightCount = mergeSort(arr, mid + 1, right);
  int mergeCount = merge(arr, left, mid, right);

  return leftCount + rightCount + mergeCount;
}

int getInversions(vector<int> &arr) {
  return mergeSort(arr, 0, arr.size() - 1);
}

int main() {
  vector<int> arr = {1, 20, 6, 4, 5, 1};
  cout << "Array: ";
  for (int num : arr) {
    cout << num << " ";
  }
  cout << endl;

  int inversions = getInversions(arr);
  cout << "Number of inversions: " << inversions << endl;

  return 0;
}
