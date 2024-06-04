#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

// �������ָ��һ�������У����ǰ������ִ��ں�������֣����������������һ�������

// �ؼ��㣺���һ�����������Կ���ʹ�ù鲢�����˼�룬�ڹ鲢�Ĺ�����ͳ������Եĸ���

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
      // ��arr[i] > arr[j]ʱ��arr[i]���������Ԫ�ض���arr[j]���������
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
