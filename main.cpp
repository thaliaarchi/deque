#include <iostream>

#include "deque.h"

int main() {
  Deque<int> deque;
  deque.push_front(1);
  deque.push_back(2);
  deque.pop_front();
  deque.push_front(1);
  deque.push_back(4);
  deque.pop_back();
  deque.push_back(3);
  deque.front();
  for (int i = 4; i <= 100; i++) {
    deque.push_back(i);
  }
  std::cout << deque << std::endl;

  Deque<int> deque2{1, 2, 3, 4, 5};
  std::cout << deque2 << std::endl;

  return 0;
}
