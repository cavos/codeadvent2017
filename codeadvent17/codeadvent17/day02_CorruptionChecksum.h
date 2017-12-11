#pragma once

#include <istream>
#include <sstream>
#include <functional>

class CorruptionChecksum
{
public:
	CorruptionChecksum();
	~CorruptionChecksum();

	static unsigned compute(std::istream& input);
	static unsigned compute_pt2(std::istream& input);

	static std::stringstream testinput;

private:
	static unsigned processLoop(std::istream& input, std::function<unsigned(std::string&)> processFun);
};

