#include "stdafx.h"
#include "day05_TwistyTrampolines.h"

#include <vector>
#include <string>

std::ifstream TwistyTrampolines::testinput("day05_input.txt", std::ifstream::in);

TwistyTrampolines::TwistyTrampolines()
{
}


TwistyTrampolines::~TwistyTrampolines()
{
}

unsigned TwistyTrampolines::compute(std::istream & input)
{
	std::vector<int> trampoline;
	std::string line;
	std::getline(input, line);
	while (!line.empty())
	{
		trampoline.emplace_back(std::stoi(line));		
		line.clear();
		std::getline(input, line);
	}

	unsigned index = 0;
	unsigned jumpCount = 0;
	while (0 <= index && index < trampoline.size())
	{
		index += trampoline[index]++;
		++jumpCount;
	}

	return jumpCount;
}
