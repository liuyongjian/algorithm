#include <iostream>
#include <queue>

using std::cout;
using std::endl;
using std::out_of_range;
using std::queue;

class QueuesSimulatedStack {
private:
  queue<int> primaryQueue;   // 用作栈的主队列
  queue<int> auxiliaryQueue; // 辅助队列，用于临时存储元素

public:
  // 将元素压入栈顶
  // 当新元素压入栈时，首先将这个新元素放入辅助队列 auxiliaryQueue。然后，从
  // primaryQueue（原本保存栈元素的队列）中将所有元素依次取出并压入到
  // auxiliaryQueue。这个操作将旧的元素放在新元素之后，但仍在 auxiliaryQueue
  // 中。
  void push(int value) {
    auxiliaryQueue.push(value);

    // 将 primaryQueue 中的所有元素移动到 auxiliaryQueue
    while (!primaryQueue.empty()) {
      auxiliaryQueue.push(primaryQueue.front());
      primaryQueue.pop();
    }

    // 交换两个队列的角色，使得新元素位于 primaryQueue 的前端
    // 当你交换 primaryQueue 和 auxiliaryQueue 的角色之后，原来的
    // auxiliaryQueue（现在含有新元素在最前面，后跟其他所有旧元素）变成了新的
    // primaryQueue。因此，最新加入的元素现在位于 primaryQueue
    // 的前端，即栈顶位置。这样的操作保证了栈的后进先出（LIFO）特性，即最后压入的元素总是第一个被取出。
    swap(primaryQueue, auxiliaryQueue);
  }

  // 移除栈顶元素
  int pop() {
    if (primaryQueue.empty()) {
      throw out_of_range("Attempt to pop from an empty stack");
    }

    int topElement = primaryQueue.front();
    primaryQueue.pop();

    return topElement;
  }

  // 获取栈顶元素
  int top() {
    if (primaryQueue.empty()) {
      throw out_of_range("Attempt to access the top of an empty stack");
    }

    return primaryQueue.front();
  }

  // 检查栈是否为空
  bool isEmpty() { return primaryQueue.empty(); }
};

int main() {
  QueuesSimulatedStack stack;

  stack.push(1);
  stack.push(2);
  stack.push(3);
  cout << "Top element: " << stack.top() << endl;    // 输出 3
  cout << "Popped element: " << stack.pop() << endl; // 输出 3
  cout << "Is empty: " << stack.isEmpty() << endl;   // 输出 false

  return 0;
}
