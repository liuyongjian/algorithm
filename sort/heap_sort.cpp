#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::swap;
using std::vector;

// heapify通常指的是向下调整（Heapify Down）的过程，而向上调整通常称为“Heapify
// Up”。
void heapify(vector<int> &nums, int n, int i) {
  int largest = i;       // 初始化最大为根
  int left = 2 * i + 1;  // 左子节点
  int right = 2 * i + 2; // 右子节点

  // 如果左子节点大于根节点
  if (left < n && nums[left] > nums[largest]) {
    largest = left;
  }

  // 如果右子节点比最大的还大
  if (right < n && nums[right] > nums[largest]) {
    largest = right;
  }

  // 如果最大不是根
  if (largest != i) {
    swap(nums[i], nums[largest]);

    // 递归地堆化受影响的子树
    heapify(nums, n, largest);
  }
}

// 函数：堆排序
void heapSort(vector<int> &nums) {
  int n = nums.size();

  // 构建堆（重新排列数组）: 从下往上建堆 时间复杂度是O(N)
  // 从上往下建 时间复杂度是O(N*logN)
  for (int i = n / 2 - 1; i >= 0; i--) {
    heapify(nums, n, i);
  }

  // 一个接一个地从堆中提取元素
  for (int i = n - 1; i > 0; i--) {
    // 移动当前根到数组的末尾
    swap(nums[0], nums[i]);

    // 调用 max heapify on the reduced heap
    heapify(nums, i, 0);
  }
}

// 通过一个称为“向上调整”（或“上浮”）的过程来保证维护堆的性质。这种调整过程确保了新插入的元素移动到堆中适当的位置，从而维持最大堆或最小堆的性质
void heapifyUp(vector<int> &heap, int idx) {
  while (idx > 0) {
    int parentIdx = (idx - 1) / 2; // 计算父节点的索引
    if (heap[idx] > heap[parentIdx]) { // 如果当前节点大于其父节点，则需要交换
      swap(heap[idx], heap[parentIdx]);
      idx = parentIdx; // 更新当前节点的索引为父节点的索引，继续向上比较
    } else {
      break; // 如果不需要交换，终止循环
    }
  }
}

// 添加新元素到堆
void insertToHeap(vector<int> &heap, int value) {
  heap.push_back(value);            // 将新元素添加到数组的末尾
  heapifyUp(heap, heap.size() - 1); // 从新元素的位置向上调整
}

int main() {
  vector<int> nums = {12, 11, 13, 5, 6, 7};
  heapSort(nums);

  cout << "Sorted array is \n";
  for (int num : nums) {
    cout << num << " ";
  }
  cout << endl;

  // 重新构建最大堆测试插入数据
  for (int i = nums.size() / 2 - 1; i >= 0; i--) {
    heapify(nums, nums.size(), i);
  }

  int newValue = 8;
  insertToHeap(nums, newValue); // 向最大堆中插入新值

  cout << "After insertion: ";
  for (int v : nums) {
    cout << v << " ";
  }
  cout << endl;

  return 0;
}
