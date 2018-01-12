#pragma once

#include <istream>
#include <utility>

class HexEd {
public:
    static std::pair<unsigned, unsigned> compute(std::istream& input);

    static std::string testInput;

private:
    struct CubeCoord;
    static CubeCoord getMove(const std::string& direction);
};
