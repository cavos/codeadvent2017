#pragma once
#include <istream>
#include <fstream>

class TwistyTrampolines
{
public:
	TwistyTrampolines();
	~TwistyTrampolines();

	static unsigned compute(std::istream& input, bool part2);

	static std::ifstream testinput;
};

