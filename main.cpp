#include <iostream>

#include "deque.h"

int main() {
  Deque<int> deque;
  deque.push_back(2);
  deque.push_front(1);
  deque.push_back(4);
  deque.pop_back();
  deque.push_back(3);
  deque.front();

  std::cout << deque << std::endl;
  return 0;
}
