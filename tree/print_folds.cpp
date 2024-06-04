#include <iostream>

// 关键点：这个树的规则是确定的。即：左子树折痕方向都是向下的，右子树折痕方向都是向上的

// 递归函数：生成并打印折痕方向
void printFolds(int level, bool down) {
  if (level == 0)
    return;                              // 基本情况，结束递归
  printFolds(level - 1, true);           // 先处理左子树，打印 "down"
  std::cout << (down ? "down " : "up "); // 当前折痕
  printFolds(level - 1, false);          // 再处理右子树，打印 "up"
}

void generateFolds(int N) {
  printFolds(N, true);    // 从第N层开始递归生成折痕
  std::cout << std::endl; // 打印完成，换行
}

int main() {
  int N;
  std::cout << "请输入折叠次数N：";
  std::cin >> N;
  generateFolds(N); // 生成并打印折痕方向
  return 0;
}
