#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::swap;
using std::vector;

// heapifyͨ��ָ�������µ�����Heapify Down���Ĺ��̣������ϵ���ͨ����Ϊ��Heapify
// Up����
void heapify(vector<int> &nums, int n, int i) {
  int largest = i;       // ��ʼ�����Ϊ��
  int left = 2 * i + 1;  // ���ӽڵ�
  int right = 2 * i + 2; // ���ӽڵ�

  // ������ӽڵ���ڸ��ڵ�
  if (left < n && nums[left] > nums[largest]) {
    largest = left;
  }

  // ������ӽڵ�����Ļ���
  if (right < n && nums[right] > nums[largest]) {
    largest = right;
  }

  // �������Ǹ�
  if (largest != i) {
    swap(nums[i], nums[largest]);

    // �ݹ�ضѻ���Ӱ�������
    heapify(nums, n, largest);
  }
}

// ������������
void heapSort(vector<int> &nums) {
  int n = nums.size();

  // �����ѣ������������飩: �������Ͻ��� ʱ�临�Ӷ���O(N)
  // �������½� ʱ�临�Ӷ���O(N*logN)
  for (int i = n / 2 - 1; i >= 0; i--) {
    heapify(nums, n, i);
  }

  // һ����һ���شӶ�����ȡԪ��
  for (int i = n - 1; i > 0; i--) {
    // �ƶ���ǰ���������ĩβ
    swap(nums[0], nums[i]);

    // ���� max heapify on the reduced heap
    heapify(nums, i, 0);
  }
}

// ͨ��һ����Ϊ�����ϵ����������ϸ������Ĺ�������֤ά���ѵ����ʡ����ֵ�������ȷ�����²����Ԫ���ƶ��������ʵ���λ�ã��Ӷ�ά�����ѻ���С�ѵ�����
void heapifyUp(vector<int> &heap, int idx) {
  while (idx > 0) {
    int parentIdx = (idx - 1) / 2; // ���㸸�ڵ������
    if (heap[idx] > heap[parentIdx]) { // �����ǰ�ڵ�����丸�ڵ㣬����Ҫ����
      swap(heap[idx], heap[parentIdx]);
      idx = parentIdx; // ���µ�ǰ�ڵ������Ϊ���ڵ���������������ϱȽ�
    } else {
      break; // �������Ҫ��������ֹѭ��
    }
  }
}

// �����Ԫ�ص���
void insertToHeap(vector<int> &heap, int value) {
  heap.push_back(value);            // ����Ԫ����ӵ������ĩβ
  heapifyUp(heap, heap.size() - 1); // ����Ԫ�ص�λ�����ϵ���
}

int main() {
  vector<int> nums = {12, 11, 13, 5, 6, 7};
  heapSort(nums);

  cout << "Sorted array is \n";
  for (int num : nums) {
    cout << num << " ";
  }
  cout << endl;

  // ���¹������Ѳ��Բ�������
  for (int i = nums.size() / 2 - 1; i >= 0; i--) {
    heapify(nums, nums.size(), i);
  }

  int newValue = 8;
  insertToHeap(nums, newValue); // �������в�����ֵ

  cout << "After insertion: ";
  for (int v : nums) {
    cout << v << " ";
  }
  cout << endl;

  return 0;
}
