#pragma once

#include <sstream>
#include <fstream>

class StreamProcessing {
public:
    static unsigned compute(std::istream& input);

    static std::ifstream puzzleInput;
};
