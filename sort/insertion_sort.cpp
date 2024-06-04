#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

void insertionSort(vector<int> &arr) {

  int n = arr.size();

  // 如果数组为空或只有一个元素，无需排序
  if (n <= 1) {
    return;
  }

  for (int i = 1; i < n; i++) {
    for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--) {
      swap(arr[j], arr[j - 1]);
    }
  }
}

void swap(int &a, int &b) {
  // int temp = a;
  // a = b;
  // b = temp;
  if (&a == &b) // 防止自我异或导致数据丢失
    return;
  // 不推荐这种使用方式，不直观
  a = a ^ b;
  b = a ^ b;
  a = a ^ b;
}

// 打印数组
void printArray(const vector<int> &arr) {
  for (int num : arr) {
    cout << num << " ";
  }
  cout << endl;
}

bool compareArrays(const vector<int> &arr1, const vector<int> &arr2) {
  if (arr1.size() != arr2.size()) {
    return false;
  }

  for (size_t i = 0; i < arr1.size(); i++) {
    if (arr1[i] != arr2[i]) {
      return false;
    }
  }

  return true;
}

// 生成随机数组
void generateRandomArray(vector<int> &arr, int n) {
  for (int i = 0; i < n; i++)
    arr.push_back((rand() % 200) - 100); // 生成-99到99的随机数
}

int main() {
  srand(time(nullptr));

  const int N = 100;
  vector<int> arr;
  vector<int> arrCopy;

  generateRandomArray(arr, N);

  cout << "随机生成的数组:" << endl;
  printArray(arr); // 打印随机生成的数组

  arrCopy = arr; // 创建一个副本用于对比

  // 使用自定义的排序算法
  insertionSort(arr);

  // 使用标准库中的排序算法
  sort(arrCopy.begin(), arrCopy.end());

  cout << "排序后的数组:" << endl;

  printArray(arr); // 打印排序后的数组

  // 比较两个排序结果是否一致
  if (compareArrays(arr, arrCopy)) {
    cout << "The sorting algorithm works correctly." << endl;
  } else {
    cout << "The sorting algorithm failed." << endl;
  }

  return 0;
}
