#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

void insertionSort(vector<int> &arr) {

  int n = arr.size();

  // �������Ϊ�ջ�ֻ��һ��Ԫ�أ���������
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
  if (&a == &b) // ��ֹ������������ݶ�ʧ
    return;
  // ���Ƽ�����ʹ�÷�ʽ����ֱ��
  a = a ^ b;
  b = a ^ b;
  a = a ^ b;
}

// ��ӡ����
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

// �����������
void generateRandomArray(vector<int> &arr, int n) {
  for (int i = 0; i < n; i++)
    arr.push_back((rand() % 200) - 100); // ����-99��99�������
}

int main() {
  srand(time(nullptr));

  const int N = 100;
  vector<int> arr;
  vector<int> arrCopy;

  generateRandomArray(arr, N);

  cout << "������ɵ�����:" << endl;
  printArray(arr); // ��ӡ������ɵ�����

  arrCopy = arr; // ����һ���������ڶԱ�

  // ʹ���Զ���������㷨
  insertionSort(arr);

  // ʹ�ñ�׼���е������㷨
  sort(arrCopy.begin(), arrCopy.end());

  cout << "����������:" << endl;

  printArray(arr); // ��ӡ����������

  // �Ƚ������������Ƿ�һ��
  if (compareArrays(arr, arrCopy)) {
    cout << "The sorting algorithm works correctly." << endl;
  } else {
    cout << "The sorting algorithm failed." << endl;
  }

  return 0;
}
