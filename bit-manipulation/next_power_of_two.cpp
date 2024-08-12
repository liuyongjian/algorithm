#include <cstdint> // for uint32_t
#include <iostream>

using namespace std;

/*
题目：
给定一个非负整数 num，如何在不使用循环语句的情况下，返回一个大于或等于
num，并且距离 num 最近的 2 的某次方。

思路：
通过扩展 num 的位来找到大于它的最小 2的幂。
位操作允许我们在几步内迅速修改和评估数字，而不需遍历所有的可能值。
由于每一步都将前一步结果的有效位扩展到更低的位，我们有效地用最少的步骤“填满”了数字，保证了最终的结果是正确的2
的幂。
*/

uint32_t nextPowerOfTwo(uint32_t num) {
  if (num == 0)
    return 1;

  num--; // 处理 num 本身就是 2 的幂的情况。例如，如果 num 是 4（即 2 的 2
         // 次方），减 1 后变成 3，这保证了下一步操作后的结果仍为 4
         // 而不是更大的数。

  // 将 num 的每个位与自己右移 1 位后的结果进行或操作，从而把最高的 1
  // 后面的一个低位变为 1。
  num |= num >> 1;
  // 这些操作依次扩大影响范围，确保从最高位 1 到最低位的所有位都被设置为 1。
  num |= num >> 2;
  num |= num >> 4;
  num |= num >> 8;
  num |= num >> 16;

  // 最后对处理过的 num 加 1，得到的结果就是大于原始 num 的最小 2
  // 的幂。因为经过上面的操作，num 已经是形如 000...000111...111 的数字，加 1
  // 后变为 000...001000...000，即一个更高位的 1 后面跟着全是 0，正好是 2 的幂。
  return num + 1;
}

int main() {
  uint32_t num;
  cout << "请输入一个非负整数: ";
  cin >> num;

  uint32_t result = nextPowerOfTwo(num);
  cout << "大于或等于 " << num << " 的最小2的幂是: " << result << endl;

  return 0;
}