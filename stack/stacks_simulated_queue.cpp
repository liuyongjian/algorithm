#include <iostream>
#include <stack>
#include <stdexcept>

using std::cout;
using std::endl;
using std::out_of_range;
using std::stack;

// �ؼ��㣺ͨ���������ջ�Ĳ�����ģ����е���Ϊ�Լ�����ת�ƻ�����ʱ��

class StacksSimulatedQueue {
private:
  stack<int> inputStack;
  stack<int> outputStack;

  void transferData() {
    // ֻ�е� outputStack ��ȫ��ʱ���Ŵ� inputStack ת�����ݵ�
    // outputStack�������ȷ�������Ѿ��� outputStack
    // �е�Ԫ�ض�����ȷ���ӣ�ά�����Ƚ��ȳ���˳��
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
