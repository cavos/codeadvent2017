#include "day10_KnotHash.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

std::stringstream KnotHash::puzzleInput("206,63,255,131,65,80,238,157,254,24,133,2,16,0,1,3");

void _day10_debugPrint(const std::vector<unsigned> &buffer,
                       unsigned currentPos) {
  for (unsigned i = 0; i < buffer.size(); ++i) {
    if (i == currentPos)
      std::cout << "(";
    std::cout << buffer[i];
    if (i == currentPos)
      std::cout << ")";
    std::cout << " ";
  }
  std::cout << "\n";
}

unsigned KnotHash::compute(const unsigned bufferSize,
                           std::istream &inputStream) {
  std::vector<unsigned char> buffer(bufferSize);
  std::iota(buffer.begin(), buffer.end(), 0);

  unsigned skip = 0;
  unsigned currentPosition = 0;
  std::string input;  
  while (std::getline(inputStream, input, ',')) {
    int reverseLength = std::stoi(input);
    pinchAndTwist(buffer, reverseLength, currentPosition);

    currentPosition = (currentPosition + reverseLength + skip) % buffer.size();
    skip++;
  }

  return buffer.at(0) * buffer.at(1);
}

std::string KnotHash::compute_pt2(std::stringstream &input) {
  std::vector<unsigned char> reverseLengths = getReverseLengths(input);

  std::vector<unsigned char> buffer(bufferSize);
  std::iota(buffer.begin(), buffer.end(), 0);
  
  unsgined rounds = 64;
  unsigned skip = 0;
  unsigned currentPosition = 0;
  while (rounds) {
    for (auto reverseLength : reverseLengths) {
      pinchAndTwist(buffer, reverseLength, currentPosition);
      currentPosition = (currentPosition + reverseLength + skip) % buffer.size();
      ++skip;
    }
    --rounds;
  }
  
  std::stringstream result;
  for (unsigned i = 0; i < 16; ++i) {
    result << std::hex << std::accumulate(buffer.begin() + i*16, buffer.end() +(i+1)*16,
                                          0, [](auto a, auto b) { return a ^ b; });
  }
  
  return result.str();
}

std::vector<unsigned char> KnotHash::getReverseLengths(std::stringstream &input) {
  std::vector<unsigned char> reverseLengths;
  while (!input.eof()) {
    reverseLengths.push_back(static_cast<unsigned char>(input.get()));
  }

  reverseLengths.insert(reverseLengths.end(), {17, 31, 73, 47, 23});
return reverseLengths;
}

void pinchAndTwist(std::vector<unsigned char> &buffer, unsigned reverseLength, unsigned offset) {
    unsigned reverseSteps = reverseLength / 2;

    auto begin = buffer.begin() + offset;
    auto end = buffer.begin() +
               (offset + reverseLength /* + skip */) % buffer.size() -
               1;
    while (reverseSteps) {
      std::iter_swap(begin, end);

      begin = (begin + 1 != buffer.end()) ? ++begin : buffer.begin();
      end = (end != buffer.begin()) ? --end : buffer.end() - 1;
      --reverseSteps;
    }
}
