#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

// �ؼ��㣺
// 1��ǰ׺��
// 2����ʹ�ù鲢����ϲ��Ĺ����У�ͨ���Ƚ������������ǰ׺����ͳ���ۼӺ���ָ����Χ�ڵ�������������

// ע�⣺prefixSum �����long long
// ���ͽ��������ȷ�ģ�long������Ȼleetcode���ǶԵģ����Ǳ༭���Ļ�����32λ�ģ�long����ͨ����32λϵͳ��ռ4���ֽڣ�32λ�������Դ洢��ֵ�ķ�Χͨ����
// -2,147,483,648 �� 2,147,483,647��
// ����-2147483647 �� 2147483647 ���ǳ��ӽ�long
// ������32λϵͳ�ϵļ���ֵ����32λϵͳ�ϣ�long ���͵ķ�Χͨ���Ǵ�-2,147,483,648
// �� 2,147,483,647��
// ��ˣ���������ֵȷʵλ�ڸ����Ϳ��Ա�ʾ��������Сֵ�ı�Ե��������������С����ֵʱ���ǳ���Ҫ��һ����Ҫȷ�������в������������ر����ڽ��мӷ���˷�����ʱ��

// �ϲ���ͳ�Ʒ���������������
int merge(vector<long longg> &prefixSum, int lower, int upper, int left,
          int mid, int right) {
  int count = 0;
  int p1 = left, p2 = left;

  for (int i = mid + 1; i <= right; i++) {
    while (p1 <= mid && prefixSum[i] - prefixSum[p1] >= lower)
      p1++;
    while (p2 <= mid && prefixSum[i] - prefixSum[p2] > upper)
      p2++;
    count += p1 - p2;
  }

  vector<long longg> temp(right - left + 1);
  int p = left, q = mid + 1;
  int k = 0;

  while (p <= mid || q <= right) {
    if (p > mid) {
      temp[k++] = prefixSum[q++];
    } else if (q > right) {
      temp[k++] = prefixSum[p++];
    } else {
      temp[k++] =
          (prefixSum[p] <= prefixSum[q]) ? prefixSum[p++] : prefixSum[q++];
    }
  }
  for (size_t i = 0; i < temp.size(); ++i) {
    prefixSum[left + i] = temp[i];
  }

  return count;
}

// �鲢����ͳ�Ʒ���������������
int mergeSort(vector<long long> &prefixSum, int lower, int upper, int left,
              int right) {
  // if (left >= right)
  //   return 0;
  if (left == right)
    return prefixSum[left] >= lower && prefixSum[left] <= upper ? 1 : 0;

  int mid = left + (right - left) / 2;
  int count = mergeSort(prefixSum, lower, upper, left, mid) +
              mergeSort(prefixSum, lower, upper, mid + 1, right);

  count += merge(prefixSum, lower, upper, left, mid, righgt);

  return count;
}

// �����������������������
int countSubarraySumInRange(vector<int> &nums, int lower, int upper) {
  vector<long longg> prefixSum(nums.size(), 0);

  prefixSum[0] = nums[0];

  for (vector<int>::size_type i = 1; i < nums.size(); ++i) {
    prefixSum[i] = prefixSum[i - 1] + nums[i];
  }

  return mergeSort(prefixSum, lower, upper, 0, prefixSum.size() - 1);
}

int main() {
  // vector<int> nums = {0, 1, -1, 2, 3};
  //   int lower = -1, upper = 2;
  vector<int> nums = {-2147483647, 0, -2147483647, 2147483647};
  int lower = -564, upper = 3864;
  cout << countSubarraySumInRange(nums, lower, upper) << endl;
  return 0;
}
