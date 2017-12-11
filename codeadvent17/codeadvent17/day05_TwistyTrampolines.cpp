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

unsigned TwistyTrampolines::compute(std::istream & input, bool part2)
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
		auto jumpIndex = index;
		index += trampoline[index];
		if (trampoline[jumpIndex] >= 3 && part2)
			trampoline[jumpIndex]--;
		else
			trampoline[jumpIndex]++;
		++jumpCount;
	}

	input.clear();
	input.seekg(0, std::ios::beg);
	return jumpCount;
}
