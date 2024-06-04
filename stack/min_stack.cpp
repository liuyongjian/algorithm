#include <cassert>
#include <iostream>
#include <stack>

using std::cout;
using std::endl;
using std::stack;

// 关键点：主栈和辅助栈

class MinStack {
private:
  stack<int> s;
  stack<int> min_s;

public:
  // 将元素x推入栈中
  void push(int x) {
    s.push(x);

    if (min_s.empty() || x <= min_s.top()) {
      min_s.push(x); // 只有当当前元素x小于等于辅助栈顶元素时，才将x压入辅助栈
    }
  }

  void pop() {
    assert(!s.empty() && "Cannot pop from an empty stack");

    if (s.top() == min_s.top()) {
      min_s.pop(); // 如果主栈顶元素等于辅助栈顶元素，辅助栈也需要弹出
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
  cout << "Minimum: " << minStack.getMin() << endl; // 返回 -3
  minStack.pop();
  cout << "Top element: " << minStack.top() << endl; // 返回 0
  cout << "Minimum: " << minStack.getMin() << endl;  // 返回 -2

  return 0;
}
