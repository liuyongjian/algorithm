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

  // 创建事件列表
  for (const auto &seg : segments) {
    events.emplace_back(seg.start, true); // true 代表开始
    events.emplace_back(seg.end, false);  // false 代表结束
  }

  // 按时间排序， 结束事件优先于开始事件
  sort(events.begin(), events.end(),
       [](const pair<int, bool> &a, const pair<int, bool> &b) {
         if (a.first == b.first)
           return !a.second && b.second;
         return a.first < b.first;
       });

  int currentActive = 0, maxOverlap = 0;
  priority_queue<int, vector<int>, greater<int>>
      minHeap; // 最小堆，存储结束时间

  for (const auto &event : events) {
    if (event.second) { // 如果是开始事件
      while (!minHeap.empty() && minHeap.top() <= event.first) {
        minHeap.pop();
      }
      minHeap.push(segments[currentActive++].end); // 将新的结束时间加入堆
      maxOverlap = max(maxOverlap, (int)minHeap.size()); // 更新最大重叠数
    } else {
      // 结束时间会在开始事件时被处理， 这里不需要额外操作

      // 对于结束事件，这里没有进行任何操作。这是因为结束事件的处理已在开始事件的循环中通过
      // minHeap.top() <= event.first
      // 条件完成。只有当到达或超过结束时间时，相关线段才从堆中移除。
    }
  }

  return maxOverlap;
}

int main() {
  vector<Segment> segments = {{1, 3}, {2, 5}, {4, 6}};

  cout << "Maximum overlap of segments: " << findMaxOverlap(segments) << endl;
  return 0;
}
