#pragma once

#include <istream>
#include <sstream>
#include <vector>
#include <string>

struct Instruction {
    std::string id;
    std::string X;
    std::string Y;
};

class Duet {
public:
    static int compute(std::istream& in);
    static int compute_pt2(std::istream& in);

    static std::stringstream test_input;

private:
    static std::vector<Instruction> readInstructions(std::istream& input);
};
