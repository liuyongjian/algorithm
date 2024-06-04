#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

// �ؼ��㣺�ݹ�ض��������������ͺϲ�
// ʱ�临�Ӷȣ�O(N*logN)
// mergeSort�ѱȽ���Ϣ���������Ķ������㷨���ԭ�򣩣��������Ķ����������ܶ�����(getsmallsum��getinversions�㷨)��

// �ϲ�������������
void merge(vector<int> &arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  // ������ʱ����洢��������������
  vector<int> L(n1), R(n2);

  // �������ݵ���ʱ���� L[]��R[]
  for (int i = 0; i < n1; i++)
    L[i] = arr[left + i];
  for (int j = 0; j < n2; j++)
    R[j] = arr[mid + 1 + j];

  // �ϲ���ʱ���鵽arr[left...right]
  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (L[i] < R[j]) {
      arr[k++] = L[i++];
    } else {
      arr[k++] = R[j++];
    }
  }

  // ��ʣ���Ԫ�ؿ����� arr[]
  while (i < n1) {
    arr[k++] = L[i++];
  }

  while (j < n2) {
    arr[k++] = R[j++];
  }
}

// �鲢����
void mergeSort(vector<int> &arr, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;

    // �ݹ��������������飬ֱ��ÿ��������ֻ����һ��Ԫ��
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    // �ϲ�����������
    merge(arr, left, mid, right);
  }
}

// ��ӡ����
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
