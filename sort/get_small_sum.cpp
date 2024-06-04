#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

// 数组的小和是指数组中每个元素左边比它小的元素的和

// 关键点：求一个数组的小和可以通过归并排序的思想来实现。
// 求每一个数左边比它小的数的累加和可以转换成 =>
// i位置的数a，右边有x个数比a大，直接产生x个a的小和（x*a），剩下的数以此类推。

long long merge(vector<int> &arr, int left, int mid, int right) {
  vector<int> temp(right - left + 1);

  int i = left, j = mid + 1;

  long long sum = 0;
  int k = 0;

  while (i <= mid && j <= right) {
    if (arr[i] <
        arr[j]) { // 不能等于，应该是左边子数组中的元素比右边子数组中的元素小时，才会产生小和。这样j才能被正确计算（即保证right
                  // - j +
                  // 1的个数是正确的），从而得到右边子数组的满足条件的数的个数
      sum += arr[i] * (right - j +
                       1); // 计算小和 当前左边子数组中的元素 arr[i]
                           // 与右边子数组中比它大的元素的个数的乘积。 (right -
                           // j + 1) 表示右边子数组中比 arr[i] 大的元素的个数。
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
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

  return sum;
}

long long mergeSort(vector<int> &arr, int left, int right) {
  if (left >= right) {
    return 0;
  }

  int mid = left + (right - left) / 2;

  long long leftSum = mergeSort(arr, left, mid);
  long long rightSum = mergeSort(arr, mid + 1, right);
  long long mergeSum = merge(arr, left, mid, right);

  return leftSum + rightSum + mergeSum;
}

long long getSmallSum(vector<int> &arr) {
  return mergeSort(arr, 0, arr.size() - 1);
}

// 打印数组
void printArray(vector<int> &arr) {
  int arr_size = static_cast<size_t>(arr.size());
  for (int i = 0; i < arr_size; i++)
    cout << arr[i] << " ";
  cout << endl;
}

int main() {
  vector<int> arr = {6, 3, 2, 1, 6, 7};
  cout << "Array: ";
  printArray(arr);

  long long smallSum = getSmallSum(arr);
  cout << "Small Sum: " << smallSum << endl;

  return 0;
}
