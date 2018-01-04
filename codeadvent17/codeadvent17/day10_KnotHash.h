#pragma once
#include <istream>
#include <sstream>
#include <vector>

class KnotHash {
public:
    static unsigned compute(const unsigned bufferSize, std::istream& input);
    static std::string compute_pt2(std::stringstream &input);

    static std::stringstream puzzleInput;

private:
    static std::vector<unsigned char> getReverseLengths(std::stringstream &input);
    static void pinchAndTwist(std::vector<unsigned char> &buffer, unsigned reverseLength,
                   unsigned offset);
};
