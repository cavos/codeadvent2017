#pragma once

#include <istream>
#include <fstream>
#include <map>
#include <sstream>

class RegisterProcessor {
public:
    static int compute(std::istream& input);

    static std::stringstream input1;
    static std::ifstream inputtest;
private:
    static bool conditionIsTrue(std::map<std::string, int> &registerMap, 
                            const std::string& registerName, const std::string& sign,
                            const std::string& value);
};
