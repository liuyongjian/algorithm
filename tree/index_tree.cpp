#include <iostream>
#include <vector>

class IndexTree {
private:
  int n;
  std::vector<int> tree;

public:
  // 构造函数，初始化树状数组的大小
  // 数组 tree 的大小被初始化为 size + 1。这样做是为了使得索引从1到 size
  // 可用，而 tree[0] 通常不使用
  IndexTree(int size) : n(size), tree(size + 1, 0) {}

  // 单点更新：在index处加上value
  void update(int index, int value) {
    while (index <= n) {
      tree[index] += value;
      index += index & (-index); // 移动到下一个需要更新的位置
    }
  }

  // 查询前缀和，即从1到index的和
  int query(int index) {
    int sum = 0;
    // index > 0 查询基于从 tree[1] 开始的数据组织进行操作
    while (index > 0) {
      sum += tree[index];
      // 在查询过程中，我们通过每次剥离当前索引最右侧的二进制1来回溯，这样可以逐步累加覆盖的区间和，直到达到数组的开头
      index -= index & (-index); // 移动到下一个区间的位置
    }
    return sum;
  }
};

int main() {
  IndexTree it(10); // 假设我们需要处理长度为10的数组

  // 进行一些单点增加操作
  it.update(3, 7); // 在索引3处加7
  it.update(5, 2); // 在索引5处加2
  it.update(7, 5); // 在索引7处加5

  // 查询前缀和
  std::cout << "Sum of first 7 elements: " << it.query(7)
            << std::endl; // 查询前7个元素的和
  std::cout << "Sum of first 5 elements: " << it.query(5)
            << std::endl; // 查询前5个元素的和

  return 0;
}
