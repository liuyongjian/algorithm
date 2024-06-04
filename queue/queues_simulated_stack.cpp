#include <iostream>
#include <queue>

using std::cout;
using std::endl;
using std::out_of_range;
using std::queue;

class QueuesSimulatedStack {
private:
  queue<int> primaryQueue;   // ����ջ��������
  queue<int> auxiliaryQueue; // �������У�������ʱ�洢Ԫ��

public:
  // ��Ԫ��ѹ��ջ��
  // ����Ԫ��ѹ��ջʱ�����Ƚ������Ԫ�ط��븨������ auxiliaryQueue��Ȼ�󣬴�
  // primaryQueue��ԭ������ջԪ�صĶ��У��н�����Ԫ������ȡ����ѹ�뵽
  // auxiliaryQueue������������ɵ�Ԫ�ط�����Ԫ��֮�󣬵����� auxiliaryQueue
  // �С�
  void push(int value) {
    auxiliaryQueue.push(value);

    // �� primaryQueue �е�����Ԫ���ƶ��� auxiliaryQueue
    while (!primaryQueue.empty()) {
      auxiliaryQueue.push(primaryQueue.front());
      primaryQueue.pop();
    }

    // �����������еĽ�ɫ��ʹ����Ԫ��λ�� primaryQueue ��ǰ��
    // ���㽻�� primaryQueue �� auxiliaryQueue �Ľ�ɫ֮��ԭ����
    // auxiliaryQueue�����ں�����Ԫ������ǰ�棬����������о�Ԫ�أ�������µ�
    // primaryQueue����ˣ����¼����Ԫ������λ�� primaryQueue
    // ��ǰ�ˣ���ջ��λ�á������Ĳ�����֤��ջ�ĺ���ȳ���LIFO�����ԣ������ѹ���Ԫ�����ǵ�һ����ȡ����
    swap(primaryQueue, auxiliaryQueue);
  }

  // �Ƴ�ջ��Ԫ��
  int pop() {
    if (primaryQueue.empty()) {
      throw out_of_range("Attempt to pop from an empty stack");
    }

    int topElement = primaryQueue.front();
    primaryQueue.pop();

    return topElement;
  }

  // ��ȡջ��Ԫ��
  int top() {
    if (primaryQueue.empty()) {
      throw out_of_range("Attempt to access the top of an empty stack");
    }

    return primaryQueue.front();
  }

  // ���ջ�Ƿ�Ϊ��
  bool isEmpty() { return primaryQueue.empty(); }
};

int main() {
  QueuesSimulatedStack stack;

  stack.push(1);
  stack.push(2);
  stack.push(3);
  cout << "Top element: " << stack.top() << endl;    // ��� 3
  cout << "Popped element: " << stack.pop() << endl; // ��� 3
  cout << "Is empty: " << stack.isEmpty() << endl;   // ��� false

  return 0;
}
