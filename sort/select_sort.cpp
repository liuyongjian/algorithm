#include <iostream>
using namespace std;

void selectionSort(int arr[], int n) {
  int i, j, min_index;

  // �ƶ�δ�������еı߽�
  for (i = 0; i < n - 1; i++) {
    // �ҵ�δ���������е���СԪ�ص�����
    min_index = i;
    for (j = i + 1; j < n; j++) {
      if (arr[j] < arr[min_index]) {
        min_index = j;
      }
    }

    // ���ҵ�����СԪ����δ�������еĵ�һ��Ԫ�ؽ���
    swap(arr[min_index], arr[i]);
  }
}

// ���ڴ�ӡ����ĺ���
void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;
}

// ������������
int main() {
  int arr[] = {64, 25, 12, 22, 11};
  int n = sizeof(arr) / sizeof(arr[0]);
  selectionSort(arr, n);
  cout << "Sorted array: \n";
  printArray(arr, n);
  return 0;
}
