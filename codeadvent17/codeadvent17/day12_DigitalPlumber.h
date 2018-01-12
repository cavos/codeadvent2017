#pragma once

#include <istream>
#include <string>
#include <utility>

class DigitalPlumber {
public:
    static std::pair<unsigned, size_t> compute(std::istream& input);

    static std::string testInput;
};
