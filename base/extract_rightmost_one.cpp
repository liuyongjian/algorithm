#include <iostream>

int extractRightmostOne(int num) { return num & (-num); }

int main() {
  int num = 10;

  int rightmostOne = extractRightmostOne(num);

  std::cout << "The rightmost 1 in the binary representation of " << num
            << " is at position: " << rightmostOne << std::endl;
  return 0;
}
