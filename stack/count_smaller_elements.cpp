#include <iostream>
#include <stack>
#include <vector>

using std::cout;
using std::endl;
using std::pair;
using std::stack;
using std::to_string;
using std::vector;

vector<pair<int, int>> nearestSmallerElements(const vector<int> &arr) {
  int n = arr.size();
  vector<int> left_nearest_smaller(n, -1);  // 默认值为-1表示没有找到
  vector<int> right_nearest_smaller(n, -1); // 默认值为-1表示没有找到
  stack<int> s;

  // 从左到右遍历，计算左边最近的比当前元素小的元素
  for (int i = 0; i < n; ++i) {
    while (!s.empty() && arr[s.top()] >= arr[i]) {
      s.pop();
    }
    left_nearest_smaller[i] = s.empty() ? -1 : arr[s.top()];
    s.push(i);
  }

  // 清空栈
  while (!s.empty()) {
    s.pop();
  }

  // 从右到左遍历，计算右边最近的比当前元素小的元素
  for (int i = n - 1; i >= 0; --i) {
    while (!s.empty() && arr[s.top()] >= arr[i]) {
      s.pop();
    }
    right_nearest_smaller[i] = s.empty() ? -1 : arr[s.top()];
    s.push(i);
  }

  vector<pair<int, int>> result(n);
  for (int i = 0; i < n; ++i) {
    result[i] = {left_nearest_smaller[i], right_nearest_smaller[i]};
  }
  return result;
}

pair<vector<int>, vector<int>> nearestSmallerElements1(const vector<int> &arr) {
  int n = arr.size();
  vector<int> leftNearestSmaller(n, -1);  // 初始化为-1，表示没有找到
  vector<int> rightNearestSmaller(n, -1); // 初始化为-1，表示没有找到
  stack<int> s;

  // 从左到右遍历，计算左边最近的比当前元素小的元素
  for (int i = 0; i < n; ++i) {
    while (!s.empty() && arr[s.top()] >= arr[i]) {
      rightNearestSmaller[s.top()] = arr[i]; // 当前元素是右侧第一个更小的元素
      s.pop();
    }
    if (!s.empty()) {
      leftNearestSmaller[i] = arr[s.top()];
    }
    s.push(i);
  }

  return {leftNearestSmaller, rightNearestSmaller};
}

pair<vector<int>, vector<int>> nearestSmallerElements2(const vector<int> &arr) {
  int n = arr.size();
  vector<int> leftNearestSmaller(n, -1);
  vector<int> rightNearestSmaller(n, -1);
  stack<int> s;

  // 从左到右遍历，计算左侧最近比它小的元素
  for (int i = 0; i < n; ++i) {
    while (!s.empty() && arr[s.top()] >= arr[i]) {
      rightNearestSmaller[s.top()] = i; // 存储索引而非值
      s.pop();
    }
    if (!s.empty()) {
      leftNearestSmaller[i] = s.top(); // 存储索引而非值
    }
    s.push(i);
  }

  // 重新设置为-1如果没有找到更小的值
  for (int i = 0; i < n; ++i) {
    if (leftNearestSmaller[i] != -1) {
      leftNearestSmaller[i] = arr[leftNearestSmaller[i]];
    }
    if (rightNearestSmaller[i] != -1) {
      rightNearestSmaller[i] = arr[rightNearestSmaller[i]];
    }
  }

  return {leftNearestSmaller, rightNearestSmaller};
}

int main() {
  vector<int> arr = {4, 5, 2, 10, 8};
  vector<pair<int, int>> result = nearestSmallerElements(arr);

  for (size_t i = 0; i < arr.size(); ++i) {
    cout << "Element: " << arr[i] << " -> Left nearest smaller: "
         << (result[i].first == -1 ? "None" : std::to_string(result[i].first))
         << ", Right nearest smaller: "
         << (result[i].second == -1 ? "None" : std::to_string(result[i].second))
         << endl;
  }

  auto result1 = nearestSmallerElements1(arr);

  cout << "Index -> Left Nearest Smaller, Right Nearest Smaller" << endl;
  for (size_t i = 0; i < arr.size(); ++i) {
    cout << i << " -> "
         << (result1.first[i] == -1 ? "None" : to_string(result1.first[i]))
         << ", "
         << (result1.second[i] == -1 ? "None" : to_string(result1.second[i]))
         << endl;
  }

  vector<int> arr_repeat = {4, 5, 5, 2, 10, 8, 5};
  auto result2 = nearestSmallerElements2(arr_repeat);

  cout << "Index -> Left Nearest Smaller, Right Nearest Smaller" << endl;
  for (size_t i = 0; i < arr_repeat.size(); ++i) {
    cout << i << " -> "
         << (result2.first[i] == -1 ? "None" : to_string(result2.first[i]))
         << ", "
         << (result2.second[i] == -1 ? "None" : to_string(result2.second[i]))
         << endl;
  }

  return 0;
}
