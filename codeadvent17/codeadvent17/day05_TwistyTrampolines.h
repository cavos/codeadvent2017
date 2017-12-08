#pragma once
#include <istream>
#include <fstream>

class TwistyTrampolines
{
public:
	TwistyTrampolines();
	~TwistyTrampolines();

	static unsigned compute(std::istream& input);

	static std::ifstream testinput;
};

