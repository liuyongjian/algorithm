#include <iostream>
#include <vector>

int findOddOccurrence(const std::vector<int> &arr) {
  int result = 0;

  for (int num : arr) {
    result ^= num;
  }

  return result;
}

int main() {
  std::vector<int> arr = {1, 2, 3, 2, 3, 1, 3};
  int oddOccurrenceNumber = findOddOccurrence(arr);

  std::cout << "The number is: " << oddOccurrenceNumber << std::endl;

  return 0;
}
