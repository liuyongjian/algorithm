#include <iostream>
#include <stack>
#include <stdexcept>

using std::cout;
using std::endl;
using std::out_of_range;
using std::stack;

// 关键点：通过组合两个栈的操作来模拟队列的行为以及数据转移机制与时机

class StacksSimulatedQueue {
private:
  stack<int> inputStack;
  stack<int> outputStack;

  void transferData() {
    // 只有当 outputStack 完全空时，才从 inputStack 转移数据到
    // outputStack。这才能确保所有已经在 outputStack
    // 中的元素都已正确出队，维持了先进先出的顺序。
    if (outputStack.empty()) {
      while (!inputStack.empty()) {
        outputStack.push(inputStack.top());
        inputStack.pop();
      }
    }
  }

public:
  void enqueue(int x) { inputStack.push(x); }

  int dequeue() {
    if (outputStack.empty()) {
      transferData();
    }

    if (outputStack.empty()) {
      throw out_of_range("dequeue on empty queue");
    }

    int result = outputStack.top();
    outputStack.pop();

    return result;
  }

  int peek() {
    if (outputStack.empty()) {
      transferData();
    }
    if (outputStack.empty()) {
      throw out_of_range("Attempt to peek from an empty queue");
    }
    return outputStack.top();
  }

  bool isEmpty() { return inputStack.empty() && outputStack.empty(); }
};

int main() {
  StacksSimulatedQueue queue;

  queue.enqueue(1);
  queue.enqueue(2);
  queue.enqueue(3);

  cout << "Dequeued: " << queue.dequeue() << endl; // 1
  cout << "Peeked: " << queue.peek() << endl;
  cout << "Dequeued: " << queue.dequeue() << endl; // 2
  queue.enqueue(4);
  cout << "Dequeued: " << queue.dequeue() << endl; // 3
  cout << "Peeked: " << queue.peek() << endl;
  cout << "Dequeued: " << queue.dequeue() << endl; // 4

  return 0;
}
