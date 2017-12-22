#include "day09_StreamProcessing.h"

#include <iostream>

std::ifstream StreamProcessing::puzzleInput("day09_input.txt",
                                            std::ifstream::in);

unsigned StreamProcessing::compute(std::istream &input) {
  bool insideGarbage = false;
  unsigned numberOfOpenGroups = 0;
  unsigned score = 0;
  bool ignoreNext = false;
  unsigned garbageCharactersCount = 0;

  while (!input.eof()) {
    auto c = input.get();
    if (ignoreNext)
      ignoreNext = false;
    else {
      if (c == '!')
        ignoreNext = true;
      else if (c == '>')
        insideGarbage = false;
      else if (insideGarbage)
        garbageCharactersCount++;
      else if (c == '<')
        insideGarbage = true;
      else {
        if (c == '{')
          numberOfOpenGroups++;
        else if (c == '}') {
          score += numberOfOpenGroups;
          numberOfOpenGroups--;
        }
      }
    }
  }

  std::cout << "day09.2: " << garbageCharactersCount << "\n";
  return score;
}