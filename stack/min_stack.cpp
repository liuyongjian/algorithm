#include <cassert>
#include <iostream>
#include <stack>

using std::cout;
using std::endl;
using std::stack;

// �ؼ��㣺��ջ�͸���ջ

class MinStack {
private:
  stack<int> s;
  stack<int> min_s;

public:
  // ��Ԫ��x����ջ��
  void push(int x) {
    s.push(x);

    if (min_s.empty() || x <= min_s.top()) {
      min_s.push(x); // ֻ�е���ǰԪ��xС�ڵ��ڸ���ջ��Ԫ��ʱ���Ž�xѹ�븨��ջ
    }
  }

  void pop() {
    assert(!s.empty() && "Cannot pop from an empty stack");

    if (s.top() == min_s.top()) {
      min_s.pop(); // �����ջ��Ԫ�ص��ڸ���ջ��Ԫ�أ�����ջҲ��Ҫ����
    }

    s.pop();
  }

  int top() {
    assert(!s.empty() && "Stack is empty");
    return s.top();
  }

  int getMin() {
    assert(!min_s.empty() && "Stack is empty");
    return min_s.top();
  }
};

int main() {
  MinStack minStack;
  minStack.push(-2);
  minStack.push(0);
  minStack.push(-3);
  cout << "Minimum: " << minStack.getMin() << endl; // ���� -3
  minStack.pop();
  cout << "Top element: " << minStack.top() << endl; // ���� 0
  cout << "Minimum: " << minStack.getMin() << endl;  // ���� -2

  return 0;
}
