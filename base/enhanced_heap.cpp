#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using std::cout;
using std::endl;
using std::less;
using std::logic_error;
using std::ostream;
using std::string;
using std::swap;
using std::unordered_map;
using std::vector;

class Person {
public:
  string name;
  int age;

  Person(string n, int a) : name(n), age(a) {}

  // 定义相等运算符
  bool operator==(const Person &other) const {
    return name == other.name && age == other.age; // 可以根据需要调整比较逻辑
  }

  friend ostream &operator<<(ostream &os, const Person &p) {
    os << p.name << " (" << p.age << " years)";
    return os;
  }
};

// 比较器，用于比较 Person 对象的年龄
struct ComparePersons {
  bool operator()(const Person &a, const Person &b) const {
    cout << "Comparing: " << a.name << " (" << a.age << ") with " << b.name
         << " (" << b.age << ")" << endl;
    return a.age < b.age;
  }
};

// 定义哈希函数，以便 Person 对象可以用作 unordered_map 的键
namespace std {
template <> struct hash<Person> {
  size_t operator()(const Person &p) const {
    return hash<string>()(p.name) ^ hash<int>()(p.age);
  }
};
} // namespace std

template <typename T, typename Comparator = less<T>> class EnhancedHeap {
private:
  vector<T> heap;
  int heapSize =
      0; // 内置类型如 int
         // 在类构造时不会自动初始化为零，它们通常保留垃圾值，除非显式设置一个初始值。这可能会导致非预期的行为
  unordered_map<T, vector<int>> indexMap; // 反向索引表
  Comparator compare;

  int parent(int i) { return (i - 1) / 2; }
  int left(int i) { return 2 * i + 1; }
  int right(int i) { return 2 * i + 2; }

  void swapElement(int i, int j) {
    // 交换堆中的两个元素
    swap(heap[i], heap[j]);
    // 更新反向索引表
    indexMap[heap[i]] = i;
    indexMap[heap[j]] = j;
  }

  void updateIndexMap() {
    indexMap.clear();
    for (std::size_t i = 0; i < heap.size(); i++) {
      indexMap[heap[i]].push_back(i);
    }
  }

  void siftUp(int i) {
    while (i != 0 && compare(heap[i], heap[parent(i)])) {
      swap(heap[i], heap[parent(i)]);
      updateIndexMap();
      i = parent(i);
    }
  }

  void siftDown(int i) {
    int size = heap.size();

    while (true) {
      int l = left(i);  // 计算左子节点的索引
      int r = right(i); // 计算右子节点的索引

      int optimal = i; // 最优节点

      if (l < size && compare(heap[l], heap[optimal])) {
        optimal = l;
      }
      if (r < size && compare(heap[r], heap[optimal])) {
        optimal = r;
      }

      if (optimal != i) {
        swap(heap[i], heap[optimal]);
        updateIndexMap();

        i = optimal;
      } else {
        break;
      }
    }
  }

public:
  bool isEmpty() { return heapSize == 0; }

  int size() { return heapSize; }

  T &peek() {
    if (isEmpty()) {
      throw logic_error("Heap is empty");
    }
    return heap.front(); // heap[0]
  }

  bool contain(T value) {
    return indexMap.find(value) !=
           indexMap.end(); // 或者 indexMap.count(value) > 0;
  }

  void insert(T value) {
    heap.push_back(value);

    // 将新元素的索引添加到索引映射中。键是堆中的元素值（value），值是一个包含所有该元素在堆数组中位置的索引列表（vector<int>）
    // 使用 push_back(heapSize) 将新元素的索引添加到这个向量的末尾。这里的
    // heapSize 是新元素添加到堆 vector 之前的大小，也就是新元素的索引位置。
    indexMap[value].push_back(heapSize);

    siftUp(heapSize++);
  }

  void rebalance(T value) {
    // indexMap.end() 返回一个指向 unordered_map
    // 末尾的迭代器，用于表示一个非法的位置，即不存在任何元素的位置。 如果 find
    // 方法返回的迭代器与 end() 相等，这意味着 value
    // 没有找到，即不存在于哈希表中。
    if (indexMap.find(value) == indexMap.end())
      logic_error("Element not found in heap");

    int index = indexMap[value].back(); // 使用 back() 获取最后一个索引;

    // 先尝试向上调整
    siftUp(index);
    // 如果向上没有调整，则尝试向下调整
    siftDown(index);
  }

  // 删除任意元素
  void removeElement(T value) {
    if (indexMap.find(value) == indexMap.end()) {
      logic_error("Element not found in heap");
    }

    // 获取所要移除元素的索引
    int indexToRemove = indexMap[value].back();
    indexMap[value].pop_back();

    // if (indexMap[value].empty()) {
    //   indexMap.erase(value);
    // }

    // 用堆中的最后一个元素替换这个要删除的元素
    T lastElement = heap.back();
    // heap[indexToRemove] = lastElement;

    // // 更新indexMap
    // indexMap[lastElement].push_back(indexToRemove);
    // indexMap[lastElement].erase(std::remove(indexMap[lastElement].begin(),
    //                                         indexMap[lastElement].end(),
    //                                         heapSize),
    //                             indexMap[lastElement].end());

    if (indexToRemove < heapSize - 1) { // 如果不是删除的最后一个元素
      // 用堆中的最后一个元素替换这个要删除的元素
      heap[indexToRemove] = lastElement;

      heap.pop_back();
      heapSize--;

      // 更新 indexMap，删除最后一个元素的旧索引
      // indexMap[lastElement].pop_back();
      if (indexMap[value].empty()) {
        indexMap.erase(lastElement);
      }

      // 为替换的元素添加新的索引
      indexMap[lastElement].push_back(indexToRemove);

      // 重新平衡被替换的位置
      rebalance(lastElement);
    } else {
      heap.pop_back();
    }
  }

  // 弹出堆顶元素
  void extractTop() {
    if (heap.empty())
      throw logic_error("Heap is empty");

    // 删除堆顶元素的索引映射
    if (indexMap[heap[0]].size() == 1) {
      indexMap.erase(heap[0]);
    } else {
      // 这种组合的结果是 indexMap[heap[0]] 向量中所有值为 0
      // 的元素都被高效地删除了。这是因为 remove
      // 本身不实际删除元素，而只是将需要删除的元素移到向量的末端，erase
      // 然后真正从向量中移除这些元素。

      // 了解 remove
      // 只是重排元素，并不真正从容器中删除元素的行为特点是理解这个惯用法的关键
      indexMap[heap[0]].erase(
          // 将所有等于 0
          // 的元素移到向量的末尾，并返回一个迭代器，指向重新排列后的第一个被移动的元素（即第一个等于
          // 0 的元素的新位置）
          std::remove(indexMap[heap[0]].begin(), indexMap[heap[0]].end(), 0),
          indexMap[heap[0]].end());
    }

    // 把最后一个元素移动到堆顶
    T lastElement = heap.back();
    heap[0] = lastElement;
    heap.pop_back();
    heapSize--;

    indexMap[lastElement].pop_back(); // 删除旧的最后元素索引
    if (!heap.empty()) {
      indexMap[lastElement].push_back(0); // 添加新的索引位置
      siftDown(0);
    } else {
      indexMap.erase(lastElement);
    }
  }
};

int main() {
  // EnhancedHeap<int> minHeap;
  // minHeap.insert(5);  // heapSize = 0
  // minHeap.insert(10); // heapSize = 1
  // // minHeap.insert(5);  // heapSize = 2
  // minHeap.insert(2);

  // // 在这种情况下，indexMap 的内容将是：
  // // indexMap[5] 包含 [0, 2]（值 5 出现在索引 0 和 2 的位置）
  // // indexMap[10] 包含 [1]（值 10 出现在索引 1 的位置）

  // std::cout << "Top element in minHeap: " << minHeap.peek() << std::endl;
  // std::cout << "Contains: " << minHeap.contain(2) << std::endl;
  // minHeap.extractTop();
  // // minHeap.removeElement(5);
  // // minHeap.removeElement(5);
  // std::cout << "Top element after removal: " << minHeap.peek() << std::endl;
  // std::cout << "Contains: " << minHeap.contain(2) << std::endl;

  EnhancedHeap<Person, ComparePersons> heap;

  Person p1 = Person("Alice", 30);
  heap.insert(p1);
  Person p2 = Person("Bob", 25);
  cout << "person:" << p1 << endl;
  heap.insert(p2);
  cout << "peek: " << heap.peek() << endl;
  heap.insert(p1); // 插入相同的对象
  cout << "peek after inserting again: " << heap.peek() << endl;

  // 更多操作
  return 0;
}
