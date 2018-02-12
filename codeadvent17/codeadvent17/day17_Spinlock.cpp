#include <algorithm>
#include <iostream>
#include <vector>
#include "day17_Spinlock.h"

unsigned Spinlock::compute(unsigned stepSize) {
  std::vector<short> buffer;
  buffer.push_back(0);

  size_t currentPos = 0;
  for (unsigned step = 1; step <= 2017; ++step) {
    currentPos = (currentPos + stepSize) % buffer.size() + 1;
    buffer.insert(buffer.begin() + currentPos, step);
  }

  return buffer[(currentPos + 1) % buffer.size()];
}

size_t Spinlock::compute_pt2(unsigned stepSize) {
  size_t currentPos = 0;
  size_t bufferSize = 1;
  size_t valueAfterZero = 0;

  for (size_t step = 1; step <= 50000000; ++step) {
    currentPos = (currentPos + stepSize) % bufferSize + 1;
    if (currentPos == 1)
      valueAfterZero = step;
    ++bufferSize;
  }

  return valueAfterZero;
}
