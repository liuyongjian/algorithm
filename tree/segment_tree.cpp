#include <iostream>
#include <vector>

using namespace std;

class SegmentTree {
private:
  vector<int> tree; // 线段树数组(节点)，存储每个区间的和或其他统计信息
  vector<int> data; // 原始数据数组，用于构建线段树
  vector<int> lazy; // 延迟更新数组，用于存储还未传播到子节点的更新操作
  int n; // 原始数据的大小

  // 递归构建线段树
  // node表示当前节点的索引；start和end定义当前节点表示的区间范围
  void build(int node, int start, int end) {
    // 递归地将数组分为更小的段，直到每段只包含一个元素，然后用这些元素值来填充叶节点
    if (start == end) {
      tree[node] = data[start]; // 叶节点直接赋值为对应的数据
    } else {
      int mid = (start + end) / 2;
      int left_child = 2 * node + 1;
      int right_child = 2 * node + 2;

      build(left_child, start, mid);    // 递归构建左子树
      build(right_child, mid + 1, end); // 递归构建右子树

      tree[node] =
          tree[left_child] + tree[right_child]; // 内部节点的值是左右子节点的和
    }
  }

  // 区间更新，使用延迟传播
  // start, end: 当前节点所代表的数组区间。
  // L, R: 需要更新的目标区间。L是目标区间的开始索引，R是结束索引。
  // val: 更新操作中每个元素需要增加的值。
  void updateRange(int node, int start, int end, int L, int R, int val) {
    // 如果当前节点有未处理的延迟更新值（lazy[node]不为0），则首先应用这些更新到当前节点。
    if (lazy[node] != 0) {
      // 更新当前节点的值
      tree[node] += (end - start + 1) * lazy[node];

      // 如果当前节点不是叶节点（即它有子节点），则将延迟更新值传递给左右子节点，等待以后处理。
      if (start != end) {
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;
        lazy[left_child] += lazy[node];
        lazy[right_child] += lazy[node];
      }

      // 处理完毕后，将当前节点的延迟值重置为0
      lazy[node] = 0;
    }

    // 如果当前节点代表的区间与查询区间无交集，则直接返回，无需做任何更新
    if (start > R || end < L) {
      return;
    }

    // 如果当前节点的区间完全位于更新区间内（即完全覆盖），则直接更新当前节点
    if (start >= L && end <= R) {
      // 直接更新当前区间
      tree[node] += (end - start + 1) * val;

      // 设置延迟更新：如果当前节点不是叶节点，设置其子节点的延迟更新值，这样实际的节点值更新可以延后处理。
      if (start != end) {
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;
        lazy[left_child] += val;
        lazy[right_child] += val;
      }

      return;
    }

    // 部分覆盖的递归更新
    // 计算中点和子节点索引：用于确定如何递归地更新子区间。
    int mid = (start + end) / 2;
    int left_child = 2 * node + 1;
    int right_child = 2 * node + 2;

    // 如果更新区间只部分覆盖当前节点，需要递归地对左右子区间进行更新。
    updateRange(left_child, start, mid, L, R, val);
    updateRange(right_child, mid + 1, end, L, R, val);

    // 在递归更新完毕后，需要重新计算当前节点的值，以保证其正确反映其代表区间的聚合信息。
    tree[node] = tree[left_child] + tree[right_child];
  }

  // 查询区间和
  int query(int node, int start, int end, int L, int R) {
    if (start > R || end < L) {
      return 0;
    }

    // 在查询任何节点之前，先检查是否存在延迟更新（即 lazy[node] 是否不为 0）。
    // 如果有，应用这些更新到当前节点，并将更新传递到子节点（如果不是叶节点）。这确保了返回的区间和是最新的。
    if (lazy[node] != 0) {
      // 处理延迟更新
      tree[node] += (end - start + 1) * lazy[node];

      if (start != end) {
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;
        lazy[left_child] += lazy[node];
        lazy[right_child] += lazy[node];
      }

      lazy[node] = 0;
    }

    // 如果当前节点完全位于查询区间内，直接返回当前节点的值。
    if (start >= L && end <= R) {
      return tree[node];
    }

    // 如果当前节点的区间只是部分与查询区间重叠，递归地查询左右子树，并将结果相加返回。
    int mid = (start + end) / 2;
    int left_child = 2 * node + 1;
    int right_child = 2 * node + 2;
    int left_sum = query(left_child, start, mid, L, R);
    int right_sum = query(right_child, mid + 1, end, L, R);

    return left_sum + right_sum;
  }

  // 单点更新
  void updatePoint(int node, int start, int end, int idx, int val) {
    // 如果到达了代表单个元素的叶节点（即 start ==
    // end），直接更新该点的值，并更新对应的树节点。
    if (start == end) {
      data[idx] = val;
      tree[node] = val;
    } else {
      // 如果不是叶节点，根据索引 idx 的位置，决定是向左子树还是右子树递归更新。
      int mid = (start + end) / 2;
      int left_child = 2 * node + 1;
      int right_child = 2 * node + 2;

      if (idx <= mid) {
        updatePoint(left_child, start, mid, idx, val);
      } else {
        updatePoint(right_child, mid + 1, end, idx, val);
      }

      // 在更新完叶节点后，递归地更新所有影响的父节点的值，以确保整棵树的信息保持正确和最新。
      tree[node] = tree[left_child] + tree[right_child];
    }
  }

public:
  SegmentTree(const vector<int> &data) : data(data), n(data.size()) {
    // 大小设置为4 *
    // n是基于最坏情况的估计，确保即使在所有区间都不平衡的情况下，也有足够的空间存储所有树节点
    tree.resize(4 * n);    // 分配足够的空间
    lazy.resize(4 * n, 0); // 初始化延迟数组
    build(0, 0, n - 1);    // 开始构建线段树
  }

  // 对外提供的区间更新接口
  void updateRange(int L, int R, int val) {
    updateRange(0, 0, n - 1, L, R, val);
  }

  // 对外提供的单点更新接口
  void updatePoint(int idx, int val) { updatePoint(0, 0, n - 1, idx, val); }

  // 对外提供的查询接口
  int query(int L, int R) { return query(0, 0, n - 1, L, R); }
};

int main() {
  vector<int> data = {1, 3, 5, 7, 9, 11};
  SegmentTree st(data);

  cout << "初始化区间 [1, 4] 的和: " << st.query(1, 4) << endl;
  st.updateRange(1, 3, 5);
  cout << "将区间 [1, 3] 每个元素增加5后，区间 [1, 4] 的和: " << st.query(1, 4)
       << endl;
  st.updatePoint(2, 11);
  cout << "将索引 2 的元素设置为 10 后，区间 [1, 4] 的和: " << st.query(1, 4)
       << endl;

  return 0;
}
