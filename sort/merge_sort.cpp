#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

// 关键点：递归地对子数组进行排序和合并
// 时间复杂度：O(N*logN)
// mergeSort把比较信息变成了有序的东西（算法快的原因），这个有序的东西可以做很多事情(getsmallsum、getinversions算法)！

// 合并两个有序数组
void merge(vector<int> &arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  // 创建临时数组存储左右两个子数组
  vector<int> L(n1), R(n2);

  // 拷贝数据到临时数组 L[]和R[]
  for (int i = 0; i < n1; i++)
    L[i] = arr[left + i];
  for (int j = 0; j < n2; j++)
    R[j] = arr[mid + 1 + j];

  // 合并临时数组到arr[left...right]
  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (L[i] < R[j]) {
      arr[k++] = L[i++];
    } else {
      arr[k++] = R[j++];
    }
  }

  // 将剩余的元素拷贝到 arr[]
  while (i < n1) {
    arr[k++] = L[i++];
  }

  while (j < n2) {
    arr[k++] = R[j++];
  }
}

// 归并排序
void mergeSort(vector<int> &arr, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;

    // 递归排序两个子数组，直到每个子数组只包含一个元素
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    // 合并两个子数组
    merge(arr, left, mid, right);
  }
}

// 打印数组
void printArray(vector<int> &arr) {
  int arr_size = static_cast<size_t>(arr.size());

  for (int i = 0; i < arr_size; i++)
    cout << arr[i] << " ";
  cout << endl;
}

int main() {
  vector<int> arr = {12, 11, 13, 5, 6, 7};
  int arr_size = arr.size();

  cout << "Given array is \n";
  printArray(arr);

  mergeSort(arr, 0, arr_size - 1);

  cout << "\nSorted array is \n";
  printArray(arr);
  return 0;
}
