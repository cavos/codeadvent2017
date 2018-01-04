#include "day10_KnotHash.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>
#include <functional>

std::stringstream
    KnotHash::puzzleInput("206,63,255,131,65,80,238,157,254,24,133,2,16,0,1,3");

void _day10_debugPrint(const std::vector<unsigned char> &buffer,
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

  std::vector<unsigned char> buffer(256);
  std::iota(buffer.begin(), buffer.end(), 0);

  unsigned rounds = 64;
  unsigned skip = 0;
  unsigned currentPosition = 0;
  while (rounds) {
    for (auto reverseLength : reverseLengths) {
      pinchAndTwist(buffer, reverseLength, currentPosition);
      currentPosition =
          (currentPosition + reverseLength + skip) % buffer.size();
      ++skip;
    }
    std::cout << "round " << rounds << " pos " << currentPosition << " skip " << skip << "\n";
    --rounds;
  }

  std::stringstream result;
  for (unsigned i = 0; i < 16; ++i) {
    std::cout << "accu (" << i*16 << " : " << (i + 1) * 16 << ")\n";
    result << std::hex
           << std::accumulate(buffer.begin() + i * 16,
                              buffer.begin() + (i + 1) * 16, 0,
                              std::bit_xor<unsigned char>());
  }

  return result.str();
}

std::vector<unsigned char>
KnotHash::getReverseLengths(std::stringstream &input) {
  std::vector<unsigned char> reverseLengths;
  while (!input.eof()) {
    reverseLengths.push_back(static_cast<unsigned char>(input.get()));
  }

  reverseLengths.insert(reverseLengths.end(), {17, 31, 73, 47, 23});
  return reverseLengths;
}

void KnotHash::pinchAndTwist(std::vector<unsigned char> &buffer, unsigned reverseLength,
                   unsigned offset) {
  unsigned reverseSteps = reverseLength / 2;

  //std::cout << "offset: " << offset << " reverse length:" << reverseLength << "\n";

  auto begin = buffer.begin() + offset;
  auto end = buffer.begin() + (offset + reverseLength - 1) % buffer.size();
  while (reverseSteps) {
    std::iter_swap(begin, end);

    begin = (begin + 1 != buffer.end()) ? ++begin : buffer.begin();
    end = (end != buffer.begin()) ? --end : buffer.end() - 1;
    --reverseSteps;
  }
}
