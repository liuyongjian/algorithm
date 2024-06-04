#include <iostream>

using namespace std;

// �ؼ��㣺count��ͨ��count�ж��Ƿ������ջ��������ȥ��front��rear��λ�ù�ϵ���൱����count������front��rear

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

  // ��Ӳ���
  void enqueue(int element) {
    if (isFull()) {
      cout << "Overflow: Queue is full\n";
      return;
    }

    // ���¶��е� rear
    // ָ�룬����β��λ�á�����ʹ�õ���һ��ѭ�������ʵ�ַ�ʽ����ζ�������ĩβ�����ӵ�����Ŀ�ͷ���γ�һ��Բ�νṹ��
    rear = (rear + 1) % capacity;
    // ���µ�Ԫ�ش�ŵ�����һ�д�����º�� rear λ�á���Ϊ rear
    // �Ѿ�����ȷ�ظ��º�����������ķ�Χ�ڣ����������������Ԫ�ط����ڶ��е�ĩβ������˵�Ƕ�������һ�����õĿ�λ
    arr[rear] = element;
    count++;
  }

  // ���Ӳ���
  void dequeue() {
    if (isEmpty()) {
      cout << "Underflow: Queue is empty\n";
      return;
    }

    // ȷ���� front ָ�뵽�������ĩβʱ�������Զ����Ƶ�����Ŀ�ʼ������� %
    // ��ģ����������������� front ָ���ֵʼ�����������Ч������Χ�ڣ����� 0
    // �� capacity-1����
    front = (front + 1) % capacity;
    count--;
  }

  // ��ȡ����ͷ��Ԫ��
  int peek() {
    if (isEmpty()) {
      cout << "Queue is empty\n";
      return -1; // ����-1��Ϊ������
    }

    return arr[front];
  }

  // ��ȡ���еĵ�ǰԪ������
  int size() { return count; }

  // �������Ƿ�Ϊ��
  bool isEmpty() { return (size() == 0); }

  // �������Ƿ�����
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
