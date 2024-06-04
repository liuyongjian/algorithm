#include <iostream>
using namespace std;

void selectionSort(int arr[], int n) {
  int i, j, min_index;

  // 移动未排序序列的边界
  for (i = 0; i < n - 1; i++) {
    // 找到未排序序列中的最小元素的索引
    min_index = i;
    for (j = i + 1; j < n; j++) {
      if (arr[j] < arr[min_index]) {
        min_index = j;
      }
    }

    // 将找到的最小元素与未排序序列的第一个元素交换
    swap(arr[min_index], arr[i]);
  }
}

// 用于打印数组的函数
void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;
}

// 测试上述函数
int main() {
  int arr[] = {64, 25, 12, 22, 11};
  int n = sizeof(arr) / sizeof(arr[0]);
  selectionSort(arr, n);
  cout << "Sorted array: \n";
  printArray(arr, n);
  return 0;
}
