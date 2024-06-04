#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using std::cout;
using std::endl;
using std::greater;
using std::max;
using std::pair;
using std::priority_queue;
using std::vector;

struct Segment {
  int start, end;
};

int findMaxOverlap(vector<Segment> &segments) {
  vector<pair<int, bool>> events;

  // �����¼��б�
  for (const auto &seg : segments) {
    events.emplace_back(seg.start, true); // true ����ʼ
    events.emplace_back(seg.end, false);  // false �������
  }

  // ��ʱ������ �����¼������ڿ�ʼ�¼�
  sort(events.begin(), events.end(),
       [](const pair<int, bool> &a, const pair<int, bool> &b) {
         if (a.first == b.first)
           return !a.second && b.second;
         return a.first < b.first;
       });

  int currentActive = 0, maxOverlap = 0;
  priority_queue<int, vector<int>, greater<int>>
      minHeap; // ��С�ѣ��洢����ʱ��

  for (const auto &event : events) {
    if (event.second) { // ����ǿ�ʼ�¼�
      while (!minHeap.empty() && minHeap.top() <= event.first) {
        minHeap.pop();
      }
      minHeap.push(segments[currentActive++].end); // ���µĽ���ʱ������
      maxOverlap = max(maxOverlap, (int)minHeap.size()); // ��������ص���
    } else {
      // ����ʱ����ڿ�ʼ�¼�ʱ������ ���ﲻ��Ҫ�������

      // ���ڽ����¼�������û�н����κβ�����������Ϊ�����¼��Ĵ������ڿ�ʼ�¼���ѭ����ͨ��
      // minHeap.top() <= event.first
      // ������ɡ�ֻ�е�����򳬹�����ʱ��ʱ������߶βŴӶ����Ƴ���
    }
  }

  return maxOverlap;
}

int main() {
  vector<Segment> segments = {{1, 3}, {2, 5}, {4, 6}};

  cout << "Maximum overlap of segments: " << findMaxOverlap(segments) << endl;
  return 0;
}
