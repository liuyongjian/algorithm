#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::swap;
using std::vector;

// �����������⣺
// ͨ������չʾ���ͨ���򵥵��㷨��Ч�ؽ���ָ�Ԫ�ص����⡣��Դ���ڽ��졢�ס���������ɫ������ֿ���������������Դ�ں������������������ɫ�������������������зֿ�������Ҳ��ΪDutch
// National Flag Problem����Edsger W.
// Dijkstra���������������ַ��������ڵ��α������������

// �ؼ��㣺
// 1. ����ָ������ã�ʹ������ָ�룬low��mid��high��������Ԫ�صķָ
// 2. Ԫ�ؽ�����ͨ�����ض�ֵ�����м�ֵ���ıȽϺ�Ԫ�صĽ�������������Ԫ�ء�
// 3. ���α�������������ֻ��Ҫ����һ�Ρ�

// ���������������һ������:
// ����ѡ����������һ��Ԫ�� nums[R]
// ��Ϊ����ֵ��Ȼ������ nums[L...R]
// �ֳ�С�ڡ����ںʹ����������ֵ�������֡��������������ڿ��������еĻ��ֹ��̣��������ﴦ���������ζ���������
// ע��:
// �����е����ֲ���ȫ������ģ������������ֵ�����ġ������Ǻ�������������Ҫ��ɵ�Ŀ�ꡣ

void dutchNationalFlagPartition(vector<int> &nums, int L, int R) {
  int pivot = nums[R]; // ѡ�����һ��Ԫ����Ϊ����ֵ
  int low = L;
  int mid = L;
  int high = R - 1;

  while (mid <= high) {
    if (nums[mid] < pivot) {
      swap(nums[low++], nums[mid++]);
    } else if (nums[mid] > pivot) {
      swap(nums[mid], nums[high--]);
    } else {
      mid++;
    }
  }
  swap(nums[mid], nums[R]); // ������ֵ�������м�
}

int main() {
  vector<int> nums = {2, 0, 5, 2, 1, 4, 3};
  int L = 0;
  int R = nums.size() - 1;
  dutchNationalFlagPartition(nums, L, R);

  for (int num : nums) {
    cout << num << " ";
  }
  return 0;
}
