#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

// �����С����ָ������ÿ��Ԫ����߱���С��Ԫ�صĺ�

// �ؼ��㣺��һ�������С�Ϳ���ͨ���鲢�����˼����ʵ�֡�
// ��ÿһ������߱���С�������ۼӺͿ���ת���� =>
// iλ�õ���a���ұ���x������a��ֱ�Ӳ���x��a��С�ͣ�x*a����ʣ�µ����Դ����ơ�

long long merge(vector<int> &arr, int left, int mid, int right) {
  vector<int> temp(right - left + 1);

  int i = left, j = mid + 1;

  long long sum = 0;
  int k = 0;

  while (i <= mid && j <= right) {
    if (arr[i] <
        arr[j]) { // ���ܵ��ڣ�Ӧ��������������е�Ԫ�ر��ұ��������е�Ԫ��Сʱ���Ż����С�͡�����j���ܱ���ȷ���㣨����֤right
                  // - j +
                  // 1�ĸ�������ȷ�ģ����Ӷ��õ��ұ���������������������ĸ���
      sum += arr[i] * (right - j +
                       1); // ����С�� ��ǰ����������е�Ԫ�� arr[i]
                           // ���ұ��������б������Ԫ�صĸ����ĳ˻��� (right -
                           // j + 1) ��ʾ�ұ��������б� arr[i] ���Ԫ�صĸ�����
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

// ��ӡ����
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
