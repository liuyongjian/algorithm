#include <iostream>

using namespace std;

// 关键点：count，通过count判断是否可以入栈，而不用去管front和rear的位置关系。相当于用count解耦了front和rear

class Queue {
private:
  int *arr;
  int front;
  int rear;
  int capacity;
  int count;

public:
  Queue(int size) {
    arr = new int[size];
    capacity = size;
    front = 0;
    rear = -1;
    count = 0;
  }

  ~Queue() { delete[] arr; }

  // 入队操作
  void enqueue(int element) {
    if (isFull()) {
      cout << "Overflow: Queue is full\n";
      return;
    }

    // 更新队列的 rear
    // 指针，即队尾的位置。队列使用的是一个循环数组的实现方式，意味着数组的末尾会连接到数组的开头，形成一个圆形结构。
    rear = (rear + 1) % capacity;
    // 将新的元素存放到由上一行代码更新后的 rear 位置。因为 rear
    // 已经被正确地更新和限制在数组的范围内，所以这个操作将新元素放置在队列的末尾，或者说是队列中下一个可用的空位
    arr[rear] = element;
    count++;
  }

  // 出队操作
  void dequeue() {
    if (isEmpty()) {
      cout << "Underflow: Queue is empty\n";
      return;
    }

    // 确保当 front 指针到达数组的末尾时，它会自动回绕到数组的开始。这里的 %
    // 是模运算符，它帮助保持 front 指针的值始终在数组的有效索引范围内（即从 0
    // 到 capacity-1）。
    front = (front + 1) % capacity;
    count--;
  }

  // 获取队列头部元素
  int peek() {
    if (isEmpty()) {
      cout << "Queue is empty\n";
      return -1; // 返回-1作为错误码
    }

    return arr[front];
  }

  // 获取队列的当前元素数量
  int size() { return count; }

  // 检查队列是否为空
  bool isEmpty() { return (size() == 0); }

  // 检查队列是否已满
  bool isFull() { return (size() == capacity); }
};

int main() {
  Queue q(5);

  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);

  cout << "Front element is: " << q.peek() << endl;
  q.dequeue();
  cout << "Front element is: " << q.peek() << endl;

  q.enqueue(4);
  q.enqueue(5);
  q.enqueue(6);
  q.enqueue(7);

  cout << "Queue size is: " << q.size() << endl;

  while (!q.isEmpty()) {
    cout << q.peek() << " ";
    q.dequeue();
  }

  return 0;
}
