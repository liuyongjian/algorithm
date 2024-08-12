#include <filesystem>
#include <iostream>
#include <stack>
#include <string>

using namespace std;
using namespace std::filesystem;

/*
题目：
输入一个文件目录的路径，统计该目录下所有文件的数量，隐藏文件也要统计，但文件夹不算

思路：
深度优先搜索（DFS）。使用了栈来避免递归调用
*/

int countFiles(const string &folderPath) {
  path root(folderPath);
  if (!exists(root) || !is_directory(root)) {
    return 0; // 检查路径是否存在且是目录
  }

  stack<path> dirStack;
  dirStack.push(root);
  int filesCount = 0;

  while (!dirStack.empty()) {
    path currentDir = dirStack.top();
    dirStack.pop();

    for (const auto &entry : directory_iterator(currentDir)) {
      if (is_regular_file(entry.status())) {
        filesCount++; // 如果是文件，计数增加
      }
      if (is_directory(entry.status())) {
        dirStack.push(entry); // 如果是目录，将目录路径推入栈
      }
    }
  }

  return filesCount;
}

int main() {
  string directoryPath;
  cout << "请输入目录路径: ";
  cin >> directoryPath;

  int totalFiles = countFiles(directoryPath);
  cout << "文件总数: " << totalFiles << endl;

  return 0;
}
