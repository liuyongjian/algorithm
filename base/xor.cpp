#include <iostream>

int main() {
  int x = 10;
  int y = 5;

  // ����x��y
  x ^= y;
  y ^= x;
  x ^= y;

  std::cout << "x = " << x << ", y = " << y << std::endl;

  return 0;
}
