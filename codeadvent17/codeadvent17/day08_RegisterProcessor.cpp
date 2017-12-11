#include "stdafx.h"

#include "day08_RegisterProcessor.h"
#include <string>
#include <map>
#include <regex>
#include <algorithm>
#include <iostream>
#include <limits>


const int TARGET_REGISTER = 1;
const int INSTRUCTION = 2;
const int VALUE = 3;
const int CMP_REGISTER = 4;
const int CMP_SIGN = 5;
const int CMP_VALUE = 6;

int RegisterProcessor::compute(std::istream& input) {
    std::map<std::string, int> registerMap;
    std::regex regex("(\\w+) (inc|dec) ([\\-0-9]+) if (\\w+) ([><=!]+) ([\\-0-9]+)");

	int largestElementEver = INT_MIN;

    std::string instructionLine;
    while (std::getline(input, instructionLine)) {
        std::smatch match;
		if (std::regex_search(instructionLine, match, regex)) {
            if (conditionIsTrue(registerMap, match[CMP_REGISTER], match[CMP_SIGN], match[CMP_VALUE])) {
                if (match[INSTRUCTION] == "inc")
                    registerMap[match[TARGET_REGISTER]] += std::stoi(match[VALUE]);
                else
                    registerMap[match[TARGET_REGISTER]] -= std::stoi(match[VALUE]);

				if (largestElementEver < registerMap[match[TARGET_REGISTER]])
					largestElementEver = registerMap[match[TARGET_REGISTER]];
            }
        }
    }

	std::cout << "day08.2: " << largestElementEver << "\n";

    return std::max_element(registerMap.begin(), registerMap.end(), 
                [](auto &l, auto &r) { 
                    return l.second < r.second;
                })->second;
}

bool RegisterProcessor::conditionIsTrue(std::map<std::string, int> &registerMap, 
                            const std::string& registerName, const std::string& sign,
                            const std::string& value) {
    int registerValue = registerMap[registerName];
    int compareValue = std::stoi(value);

    // std::cout << "evaluate; " << registerMap[registerName] << "(" << registerValue << ")"
    //                             << sign << " " << compareValue << "\n";

    if (sign == "==")
        return registerValue == compareValue;
    else if (sign == "!=")
        return registerValue != compareValue;
    else if (sign == ">")
        return registerValue > compareValue;
    else if (sign == "<")
        return registerValue < compareValue;
    else if (sign == ">=")
        return registerValue >= compareValue;
    else //if (sign == "<=")
        return registerValue <= compareValue;
}

std::stringstream RegisterProcessor::input1(R"input(b inc 5 if a > 1
a inc 1 if b < 5
c dec -10 if a >= 1
c inc -20 if c == 10)input");

std::ifstream RegisterProcessor::inputtest("day08_input.txt", std::ifstream::in);